#include "MovingEntity.h"
#include "Utils.h"
#include "Constant.h"

#include <Graphics/MeshComponent.hpp>

MovingEntity::MovingEntity(const QString name,
	float bounding_radius, 
	float max_speed, 
	float max_force, float mass, float turn_rate, 
	QString mesh_handle, QString material_handle)
	: Node(name),
	  mBoundingRadius(bounding_radius),
	  mMass(mass),
	  mMaxForce(max_force),
	  mTurnRate(turn_rate),
	  mMeshHandle(mesh_handle),
	  mMaterialHandle(material_handle),
	  mHeading(0.f, 0.f, 1.f) {}

void MovingEntity::onUpdate(double time_diff)
{
	this->mIsUpdatingAfterChange = (time_diff == 0);

	// Update here
	mHeading = GetHeadingThroughRotation(getRotation());

	dt::Node::onUpdate(time_diff);
}

void MovingEntity::onInitialize()
{
	addComponent(new dt::MeshComponent(mMeshHandle, mMaterialHandle, MESH_COMPONENT));
	mPhysicsBody = addComponent(new dt::PhysicsBodyComponent(MESH_COMPONENT, PHYSICS_BODY_COMPONENT, dt::PhysicsBodyComponent::BOX));
}

Ogre::Vector3 MovingEntity::getVelocity() const
{
	return BtOgre::Convert::toOgre(mPhysicsBody->getRigidBody()->getLinearVelocity());
}

void MovingEntity::setVelocity(Ogre::Vector3 velocity) 
{
	mPhysicsBody->getRigidBody()->setLinearVelocity(BtOgre::Convert::toBullet(velocity));
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

float MovingEntity::getMass() const
{
	return mMass;
}

void MovingEntity::placeAtPosition(Ogre::Vector3 position, Ogre::Vector3 heading, float scale)
{
	setPosition(position);
	setScale(scale);
	setHeading(heading);

	resetPhysicsBody();
}

Ogre::Vector3 MovingEntity::getHeading() const 
{
	return mHeading;
}

void MovingEntity::setHeading(Ogre::Vector3 heading)
{
	setRotation(GetRotationThroughHeading(mHeading = heading));
}