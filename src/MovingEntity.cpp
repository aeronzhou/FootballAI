#include "MovingEntity.h"

#include <Graphics/MeshComponent.hpp>

const QString MovingEntity::MESH_COMPONENT = "MeshComponent";
const QString MovingEntity::PHYSICS_BODY_COMPONENT = "PhysicsBodyComponent";

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
	this->mIsUpdatingAfterChange = (time_diff == 0);

	dt::Node::onUpdate(time_diff);
}

void MovingEntity::onInitialize()
{
	addComponent(new dt::MeshComponent(mMeshHandle, mMaterialHandle, MESH_COMPONENT));
	mPhysicsBody = addComponent(new dt::PhysicsBodyComponent(MESH_COMPONENT, PHYSICS_BODY_COMPONENT));
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

float MovingEntity::getMaxSpeed() const
{
	return mMaxSpeed;
}

void MovingEntity::resetPhysicsBody()
{
	mPhysicsBody->disable();
	mPhysicsBody->enable();
}