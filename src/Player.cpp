#include "Player.h"
#include "Team.h"

#include <Graphics/MeshComponent.hpp>
#include <Physics/PhysicsBodyComponent.hpp>
#include <OgreProcedural.h>

Player::Player(QString name, float bounding_radius, float max_speed, Ogre::Vector3 heading, float max_force,
	float mass, float turn_rate, QString mesh_handle, QString material_handle, Team* team)
	: MovingEntity(name, bounding_radius, max_speed, heading, max_force, mass, turn_rate, mesh_handle, material_handle),
	  mTeam(team) {}

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

	mPhysicsBody->getRigidBody()->setFriction(2.f);
}


void Player::onUpdate(double time_diff)
{
	this->mIsUpdatingAfterChange = (time_diff == 0);

	//Update here

	dt::Node::onUpdate(time_diff);
}