#include "MovingEntity.h"
#include "Utils.h"
#include "Constant.h"

#include <Graphics/MeshComponent.hpp>

MovingEntity::MovingEntity(const QString name,
	//float bounding_radius, 
	float max_speed, 
	float max_force, float mass, float turn_rate, 
	QString mesh_handle, QString material_handle)
	: Node(name),
	  //mControlRange(bounding_radius),
	  mMaxSpeed(max_speed),
	  mMaxForce(max_force),
	  mMass(mass),
	  mTurnRate(turn_rate),
	  mMeshHandle(mesh_handle),
	  mMaterialHandle(material_handle),
	  mHeading(0.f, 0.f, 1.f), 
	  mVelocity(Ogre::Vector3::ZERO) {}

void MovingEntity::onUpdate(double time_diff)
{
	this->mIsUpdatingAfterChange = (time_diff == 0);

	dt::Node::onUpdate(time_diff);
}

void MovingEntity::onInitialize()
{
}

void MovingEntity::onDeinitialize() {}

Ogre::Vector3 MovingEntity::getVelocity() const
{
	return mVelocity;
}

void MovingEntity::setVelocity(Ogre::Vector3 velocity) 
{
	mVelocity = velocity;
}

float MovingEntity::getMaxSpeed() const
{
	return mMaxSpeed;
}

float MovingEntity::getMaxForce() const
{
	return mMaxForce;
}

void MovingEntity::resetPhysicsBody()
{
	mPhysicsBody->disable();
	mPhysicsBody->enable();
}

float MovingEntity::getMass() const
{
	return mMass;
}

void MovingEntity::placeAtPosition(Ogre::Vector3 position, Ogre::Vector3 heading, float scale)
{
	setPosition(position);
	setScale(scale);
	setRotation(GetRotationThroughHeading(heading));

	resetPhysicsBody();
}

Ogre::Vector3 MovingEntity::getHeading() const 
{
	return getRotation() * Ogre::Vector3(0, 0, 1);
}

bool MovingEntity::handleMessage(const Message& msg) const
{
	return false;
}

float MovingEntity::getTurnRate() const 
{
	return mTurnRate;
}