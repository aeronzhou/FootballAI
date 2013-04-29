#include "Player.h"
#include "Pitch.h"
#include "Team.h"
#include "Ball.h"
#include "Region.h"
#include "Goal.h"
#include "SteeringBehaviors.h"
#include "MessageDispatcher.h"
#include "ParamLoader.h"
#include "Utils.h"

#include <Graphics/MeshComponent.hpp>
#include <Physics/PhysicsBodyComponent.hpp>

#include <OgreProcedural.h>

Player::Player(const QString name, float control_range, float max_speed, float max_force,
	float mass, float turn_rate, QString mesh_handle, QString material_handle, Team* team, int assigned_region, PlayerRole role)
	: MovingEntity(name, max_speed,  max_force, mass, turn_rate, mesh_handle, material_handle),
	mTeam(team), mAssignedRegion(assigned_region), mPlayerRole(role), 
	mControlRange(control_range), mIsTurnningAroundAtTarget(0), mIsAskedToTurnAround(false) {}

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

void Player::onInitialize()
{
	MovingEntity::onInitialize();

	mMesh = addComponent(new dt::MeshComponent(mMeshHandle, mMaterialHandle, MESH_COMPONENT));
	mPhysicsBody = addComponent(new dt::PhysicsBodyComponent(MESH_COMPONENT, PHYSICS_BODY_COMPONENT, 
		dt::PhysicsBodyComponent::CONVEX, mMass));

	// Become KinematicBody to save the world
	mPhysicsBody->getRigidBody()->setCollisionFlags(mPhysicsBody->getRigidBody()->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	mPhysicsBody->getRigidBody()->setActivationState(DISABLE_DEACTIVATION);

	mSteeringBehaviors = new SteeringBehaviors(this, getBall());

	mDebugText = AddTextComponent(this);

	if (!Prm.ShowDebugText)
		mDebugText->disable();

	mPhysicsBody->getRigidBody()->setFriction(0.f);
}

void Player::onDeinitialize() 
{
	delete mSteeringBehaviors;
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
	return getPitch()->getRegionByIndex(mAssignedRegion);
}

bool Player::isBallWithinControlRange() const 
{
	return getDistToBall() < mControlRange;
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
		return region->getRandomPosition();
	}
	else 
	{
		float x = (region->getLeft() + region->getRight()) / 2;
		float z = (region->getTop() + region->getBottom()) / 2;
		
		return Ogre::Vector3(x, Prm.PlayerInitPositionY, z);
	}
}

SteeringBehaviors* Player::getSteering() const 
{
	return mSteeringBehaviors;
}

Player::PlayerRole Player::getPlayerRole() const 
{
	return mPlayerRole;
}


void Player::setDebugText(QString debug_text)
{
	this->mDebugText->setText(debug_text);
}

void Player::setTarget(Ogre::Vector3 target)
{
	mSteeringBehaviors->setTarget(target);
}

Ogre::Vector3 Player::getTarget() const 
{
	return mSteeringBehaviors->getTarget();
}

bool Player::isAtTarget() const
{
	return Vector3To2(getPosition() - getSteering()->getTarget()).length() < Prm.PlayerAtTargetRange;
}

bool Player::isWithinAssignedRegion() const 
{
	if (mPlayerRole == GOAL_KEEPER)
	{
		return getAssignedRegion()->inside(getPosition(), Region::NORMAL);
	}

	return getAssignedRegion()->inside(getPosition(), Region::HALF_SIZE);
}

bool Player::isWithinReceivingRange() const 
{
	return getDistToBall() < Prm.PlayerReceivingRange;
}

float Player::getDistToBall() const 
{
	return getPosition().distance(getBall()->getPosition());
}

FLOAT Player::getControlRange() const 
{
	return mControlRange;
}

void Player::_rotateToFaceTarget(const Ogre::Vector3& target)
{
	Ogre::Vector3 current_heading = getHeading();
	Ogre::Vector3 to_target = target - getPosition();
	Ogre::Radian angle = current_heading.getRotationTo(to_target).getYaw();

	if (angle > Ogre::Radian(mTurnRate))
		angle = Ogre::Radian(mTurnRate);

	if (angle < Ogre::Radian(-mTurnRate))
		angle = Ogre::Radian(-mTurnRate);

	// Avoid same line
	if (fabs(angle.valueRadians()) < EPS && current_heading.dotProduct(to_target) < 0)
		angle = mTurnRate;

	mIsTurnningAroundAtTarget = angle;
}

void Player::turnAroundToBall()
{
	_rotateToFaceTarget(getBall()->getPosition());
}

void Player::turnAroundToTarget(const Ogre::Vector3& target)
{
	_rotateToFaceTarget(target);
}

bool Player::isThreatened() const 
{
	std::vector<Player*>& opponents = getTeam()->getOpponent()->getPlayers();
	Ogre::Vector3 position = getPosition();

	for (auto it = opponents.begin(); it != opponents.end(); ++it)
	{
		if (position.distance((*it)->getPosition()) < Prm.PlayerThreatenedRange)
		{
			return true;
		}
	}
	return false;
}

bool Player::isClosestTeamMemberToBall() const 
{
	return mTeam->getPlayerClosestToBall() == this;
}

bool Player::isControllingPlayer() const 
{
	return mTeam->getControllingPlayer() == this;
}

bool Player::isAheadOfController() const 
{
	return fabs(getPosition().x - mTeam->getGoal()->getCenter().x) > 
		fabs(mTeam->getControllingPlayer()->getPosition().x - mTeam->getGoal()->getCenter().x);
}

bool Player::isClosestPlayerOnPitchToBall() const 
{
	return isClosestTeamMemberToBall() && (getDistToBall() < mTeam->getOpponent()->getClosestDistToBall());
}

void Player::findSupport() 
{
	if (getTeam()->getSupportingPlayer() == nullptr)
	{
		Player* supporting_player = getTeam()->determineBestSupportingPlayer();
		getTeam()->setSupportingPlayer(supporting_player);
		MessageDispatcher::get().dispatchMessage(
			0,
			this, 
			supporting_player, 
			MSG_SUPPORT_ATTACKER,
			nullptr
			);
	}

	Player* supporting_player = getTeam()->determineBestSupportingPlayer();

	if (supporting_player && supporting_player != getTeam()->getSupportingPlayer())
	{
		// Player start positioning
		MessageDispatcher::get().dispatchMessage(
			0, 
			this, 
			getTeam()->getSupportingPlayer(),
			MSG_POSITIONING,
			nullptr
			);

		getTeam()->setSupportingPlayer(supporting_player);

		MessageDispatcher::get().dispatchMessage(
			0,
			this, 
			getTeam()->getSupportingPlayer(),
			MSG_SUPPORT_ATTACKER,
			nullptr
			);
	}
}

void Player::slowDown()
{
	if (Vector3To2(getPosition() - getTarget()).length() < Prm.PlayerAtTargetRange * 0.5)
	{
		setVelocity(Ogre::Vector3::ZERO);
	}
}

bool Player::isInHotRegion() const 
{
	return Vector3To2(getPosition() - mTeam->getOpponent()->getGoal()->getCenter()).length() < 
		getPitch()->getPlayingArea()->getWidth() / 3;
}

bool Player::isOpponentWithinRange(float radius)
{
	std::vector<Player*>& opponents = mTeam->getOpponent()->getPlayers();

	for (auto it = opponents.begin(); it != opponents.end(); ++it)
	{
		if (Vector3To2((*it)->getPosition() - getPosition()).length() < radius)
		{
			return true;
		}
	}

	return false;
}

void Player::setIsAskedToTurnAround(bool flag)
{
	mIsAskedToTurnAround = flag;
}

bool Player::isAskedToTurnAround() const 
{
	return mIsAskedToTurnAround;
}

Ogre::Vector3 Player::getAskedTurnAroundTarget() const 
{
	return mAskedToTurnAroundTarget;
}

void Player::setAskedTurnAroundTarget(const Ogre::Vector3& target)
{
	mAskedToTurnAroundTarget = target;
}