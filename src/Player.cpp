#include "Player.h"
#include "Team.h"
#include "Ball.h"
#include "SteeringBehaviors.h"
#include "Utils.h"

#include <Graphics/MeshComponent.hpp>
#include <Physics/PhysicsBodyComponent.hpp>

#include <OgreProcedural.h>

Player::Player(const QString name, float bounding_radius, float max_speed, Ogre::Vector3 heading, float max_force,
	float mass, float turn_rate, QString mesh_handle, QString material_handle, Team* team, int home_region)
	: MovingEntity(name, bounding_radius, max_speed, heading, max_force, mass, turn_rate, mesh_handle, material_handle),
	  mTeam(team), mHomeRegion(home_region) {}

bool Player::isThreatened() const
{
	return false;
}

void Player::trackBall() 
{
	
}

void Player::onInitialize()
{
	MovingEntity::onInitialize();

	mSteering = std::shared_ptr<SteeringBehaviors>(new SteeringBehaviors(this, getBall()));

	mPhysicsBody->getRigidBody()->setFriction(2.f);
}

void Player::onUpdate(double time_diff)
{
	this->mIsUpdatingAfterChange = (time_diff == 0);

	// Set heading through rotation
	mHeading = GetHeadingThroughRotation(getRotation());

	dt::Node::onUpdate(time_diff);
}

Ogre::Vector3 Player::getHeading() const
{
	return mHeading;
}

void Player::setHeading(Ogre::Vector3 heading)
{
	//////////////////////////////////////////////////////////////////////////
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