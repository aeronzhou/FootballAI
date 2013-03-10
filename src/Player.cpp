#include "Player.h"
#include "Team.h"
#include "Ball.h"
#include "Region.h"
#include "SteeringAider.h"
#include "ParamLoader.h"
#include "Utils.h"

#include <Graphics/MeshComponent.hpp>
#include <Physics/PhysicsBodyComponent.hpp>

#include <OgreProcedural.h>

Player::Player(const QString name, float bounding_radius, float max_speed, float max_force,
	float mass, float turn_rate, QString mesh_handle, QString material_handle, Team* team, int home_region, PlayerRole role)
	: MovingEntity(name, bounding_radius, max_speed,  max_force, mass, turn_rate, mesh_handle, material_handle),
	mTeam(team), mHomeRegion(home_region), mPlayerRole(role) {}

// Add a flag to distinguish RED and BLUE
dt::Node* CreatePlayerFlag(dt::Node* parent, const QString& material)
{
	dt::Node* player_flag = parent->addChildNode(new dt::Node("Flag")).get();
	player_flag->addComponent(new dt::MeshComponent("PlayerFlag", material, parent->getName() + "MESH_COMPONENT"));
	player_flag->setPosition(0.f, 1.f, 0.f);

	return player_flag;
}

dt::TextComponent* AddTextComponent(dt::Node* parent)
{
	dt::Node* player_text = parent->addChildNode(new dt::Node("player_text")).get();
	player_text->setPosition(0.f, 1.f, 0.f);
	dt::TextComponent* pDebugText = (player_text->addComponent(new dt::TextComponent("Hello", 
		parent->getName() + "TextComponent"))).get();
	pDebugText->setColor(Ogre::ColourValue::White);
	pDebugText->setFont("DejaVuSans");
	pDebugText->setFontSize(24);

	return pDebugText;
}

void Player::onInitialize()
{
	MovingEntity::onInitialize();

	mSteering = new SteeringAider(this, getBall());

	if (getTeam()->getTeamColor() == Team::RED)
		CreatePlayerFlag(this, "PlayerFlagRed");
	else 
		CreatePlayerFlag(this, "PlayerFlagBlue");

	mDebugText = AddTextComponent(this);
	if (!Prm.ShowDebugText)
		mDebugText->disable();

	mPhysicsBody->getRigidBody()->setFriction(2.f);
}

void Player::onDeinitialize() 
{
	delete mSteering;
}

void Player::onUpdate(double time_diff)
{
	this->mIsUpdatingAfterChange = (time_diff == 0);

	// Set heading through rotation
	mHeading = GetHeadingThroughRotation(getRotation());

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

int Player::getHomeRegion() const 
{
	return mHomeRegion;
}

void Player::setHomeRegion(int home_region)
{
	mHomeRegion = home_region;
}

Ogre::Vector3 Player::getPositionWithRegion(bool random /* = false */)
{
	Pitch* pitch = getTeam()->getPitch();

	Region* region = pitch->getRegionFromIndex(getHomeRegion());

	if (random)
	{
		// Return a random position
		return Ogre::Vector3::ZERO;
	}
	else 
	{
		float x = (region->getLeft() + region->getRight()) / 2;
		float z = (region->getTop() + region->getBottom()) / 2;

		return Ogre::Vector3(x, 2.5f, z);
	}
}

SteeringAider* Player::getSteering() const 
{
	return mSteering;
}


void Player::setDebugText(QString debugText)
{
	this->mDebugText->setText(debugText);
}