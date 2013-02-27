#include "Ball.h"
#include "ParamLoader.h"
#include "Utils.h"

#include <Graphics/MeshComponent.hpp>
#include <Physics/PhysicsBodyComponent.hpp>

#include <math.h>

Ball::Ball(QString name, QString mesh_handle, QString material_handle)
	: MovingEntity(name, 1.0f, 12.f, 12.f, 5.0f, 10.f, mesh_handle, material_handle) {}

void Ball::onInitialize() 
{
	MovingEntity::onInitialize();

	mPhysicsBody->getRigidBody()->setFriction(2.f);
}

void Ball::onUpdate(double time_diff)
{
	this->mIsUpdatingAfterChange = (time_diff == 0);

	// Update every frame

	MovingEntity::onUpdate(time_diff);
}

void Ball::ballOutOfPitch()
{
	// 临时处理球出界的问题

}

void Ball::kick(Ogre::Vector3 direction, float force)
{
	direction = Vector3To2Normalise(direction) * force;
	
	// Give it a momentary force
	mPhysicsBody->applyCentralImpulse(BtOgre::Convert::toBullet(direction));
}

double Ball::timeToCoverDistance(Ogre::Vector3 from, Ogre::Vector3 to, float force) const
{
	//////////////////////////////////////////////////////////////////////////
	float s = Vector3To2(to - from).length();

	// s = at^2 / 2
	float a = force / this->getMass();

	return sqrt(s * 2.f / a);
}

Ogre::Vector3 Ball::futurePosition(double time) const
{
	//////////////////////////////////////////////////////////////////////////
	return getPosition();
	return getPosition();
}

void Ball::playAtPosition(Ogre::Vector3 pos)
{
	mPhysicsBody->getRigidBody()->setLinearVelocity(btVector3(0.f, 0.f, 0.f));
	this->setPosition(pos);
	this->mOldPos = pos;
	this->resetPhysicsBody();
}