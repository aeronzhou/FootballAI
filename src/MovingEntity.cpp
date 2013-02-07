#include "MovingEntity.h"

#include <Graphics/MeshComponent.hpp>

MovingEntity::MovingEntity(QString name,
	float bounding_radius, 
	float max_speed, Ogre::Vector3 heading, 
	float max_force, float mass, float turn_rate, 
	QString mesh_handle, QString material_handle)
	: Node(name),
	  mBoundingRadius(bounding_radius),
	  mHeading(heading),
	  mMass(mass),
	  mMaxForce(max_force),
	  mTurnRate(turn_rate),
	  mVelocity(Ogre::Vector3::ZERO),
	  mMeshHandle(mesh_handle),
	  mMaterialHandle(material_handle)
{
}

void MovingEntity::onUpdate(double time_diff)
{
	dt::Node::onUpdate(time_diff);
}

void MovingEntity::onInitialize()
{
	Node::onInitialize();

	addComponent(new dt::MeshComponent(mMeshHandle, mMaterialHandle, getName() + "_mesh"));
	mPhysicsBody = addComponent(new dt::PhysicsBodyComponent(getName() + "_mesh", getName() + "_physics"));
}

Ogre::Vector3 MovingEntity::getHeading() const 
{
	return mHeading;
}

void MovingEntity::setHeading(Ogre::Vector3 heading)
{
	mHeading = heading;
}

Ogre::Vector3 MovingEntity::getVelocity() const
{
	return mVelocity;
}

void MovingEntity::setVelocity(Ogre::Vector3 velocity) 
{
	mVelocity = velocity;
}

void MovingEntity::resetPhysicsBody()
{
	mPhysicsBody->disable();
	mPhysicsBody->enable();
}