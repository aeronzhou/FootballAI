#include "Player.h"
#include "Pitch.h"
#include "Team.h"
#include "Ball.h"
#include "Region.h"
#include "MotionAider.h"
#include "ParamLoader.h"
#include "Utils.h"

#include <Graphics/MeshComponent.hpp>
#include <Physics/PhysicsBodyComponent.hpp>

#include <OgreProcedural.h>

Player::Player(const QString name, float bounding_radius, float max_speed, float max_force,
	float mass, float turn_rate, QString mesh_handle, QString material_handle, Team* team, int assigned_region, PlayerRole role)
	: MovingEntity(name, max_speed,  max_force, mass, turn_rate, mesh_handle, material_handle),
	mTeam(team), mAssignedRegion(assigned_region), mPlayerRole(role), mDistSqAtTarget(Prm.DistAtTarget * Prm.DistAtTarget),
	mControlRange(bounding_radius) {}

// Add a flag to distinguish RED and BLUE
dt::Node* CreatePlayerFlag(dt::Node* parent, const QString& material)
{
	dt::Node* player_flag = parent->addChildNode(new dt::Node("Flag")).get();
	player_flag->addComponent(new dt::MeshComponent("PlayerFlag", material, parent->getName() + "MESH_COMPONENT"));
	player_flag->setPosition(0.f, 0.5f, 0.f);

	return player_flag;
}

dt::TextComponent* AddTextComponent(Player* parent)
{
	dt::Node* player_text = parent->addChildNode(new dt::Node("player_text")).get();
	player_text->setPosition(0.f, 1.f, 0.f);
	dt::TextComponent* pDebugText = (player_text->addComponent(new dt::TextComponent("Waiting", 
		parent->getName() + "TextComponent"))).get();

	if (parent->getTeam()->getTeamColor() == Team::RED)
		pDebugText->setColor(Ogre::ColourValue::Red);
	else 
		pDebugText->setColor(Ogre::ColourValue::Blue);

	pDebugText->setFont("DejaVuSans");
	pDebugText->setFontSize(14);

	return pDebugText;
}

//Ogre::Vector3 Player::getHeading() const 
//{
//	return getRotation() * Ogre::Vector3(0, 0, 1);
//}

void Player::onInitialize()
{
	MovingEntity::onInitialize();

	addComponent(new dt::MeshComponent(mMeshHandle, mMaterialHandle, MESH_COMPONENT));
	mPhysicsBody = addComponent(new dt::PhysicsBodyComponent(MESH_COMPONENT, PHYSICS_BODY_COMPONENT, 
		dt::PhysicsBodyComponent::BOX, mMass));

	// Become KinematicBody to save the world
	mPhysicsBody->getRigidBody()->setCollisionFlags(mPhysicsBody->getRigidBody()->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	mPhysicsBody->getRigidBody()->setActivationState(DISABLE_DEACTIVATION);

	mMotionAider = new MotionAider(this, getBall());

	mDebugText = AddTextComponent(this);

	if (!Prm.ShowDebugText)
		mDebugText->disable();

	mPhysicsBody->getRigidBody()->setFriction(0.f);
}

void Player::onDeinitialize() 
{
	delete mMotionAider;
}

void Player::onUpdate(double time_diff)
{
	this->mIsUpdatingAfterChange = (time_diff == 0);

	//setHeading(Ogre::Vector3(1.f, 0.f, 0.f));
	dt::Node::onUpdate(time_diff);
}

Team* Player::getTeam() const
{
	return mTeam;
}

Ball* Player::getBall() const 
{
	return mTeam->getBall();
}

Region* Player::getAssignedRegion() const 
{
	return getPitch()->getRegionFromIndex(mAssignedRegion);
}

Pitch* Player::getPitch() const 
{
	return mTeam->getPitch();
}

void Player::setAssignedRegion(int assigned_region)
{
	mAssignedRegion = assigned_region;
}

Ogre::Vector3 Player::getPositionWithRegion(bool random /* = false */)
{
	Region* region = getAssignedRegion();

	if (random)
	{
		// Return a random position
		return Ogre::Vector3::ZERO;
	}
	else 
	{
		float x = (region->getLeft() + region->getRight()) / 2;
		float z = (region->getTop() + region->getBottom()) / 2;
		
		return Ogre::Vector3(x, Prm.PlayerInitPositionY, z);
	}
}

MotionAider* Player::getMotionAider() const 
{
	return mMotionAider;
}


void Player::setDebugText(QString debug_text)
{
	this->mDebugText->setText(debug_text);
}

void Player::setTarget(Ogre::Vector3 target)
{
	mMotionAider->setTarget(target);
}

bool Player::atTarget() const
{
	return (getPosition()).normalisedCopy().squaredDistance(getMotionAider()->getTarget()) < mDistSqAtTarget;
}

bool Player::withinAssignedRegion() const 
{
	if (mPlayerRole == GOAL_KEEPER)
	{
		return getAssignedRegion()->inside(getPosition(), Region::NORMAL);
	}

	return getAssignedRegion()->inside(getPosition(), Region::HALF_SIZE);
}

float Player::getDistToBall() const 
{
	return getPosition().distance(getBall()->getPosition());
}

FLOAT Player::getControlRange() const 
{
	return mControlRange;
}