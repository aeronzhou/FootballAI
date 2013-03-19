#include "Ball.h"
#include "ParamLoader.h"
#include "Utils.h"

#include <Graphics/MeshComponent.hpp>
#include <Physics/PhysicsBodyComponent.hpp>

#include <math.h>

Ball::Ball(QString name, QString mesh_handle, QString material_handle)
	: MovingEntity(name, 12.f, 12.f, Prm.BallMass, 10.f, mesh_handle, material_handle) {}

void Ball::onInitialize() 
{
	MovingEntity::onInitialize();

	addComponent(new dt::MeshComponent(mMeshHandle, mMaterialHandle, MESH_COMPONENT));
	mPhysicsBody = addComponent(new dt::PhysicsBodyComponent(MESH_COMPONENT, PHYSICS_BODY_COMPONENT, 
		dt::PhysicsBodyComponent::SPHERE, mMass));

	mPhysicsBody->getRigidBody()->setFriction(Prm.BallFriction);
}

void Ball::onUpdate(double time_diff)
{
	this->mIsUpdatingAfterChange = (time_diff == 0);

	// Update every frame

	MovingEntity::onUpdate(time_diff);
}

void Ball::kick(Ogre::Vector3 direction, float force)
{
	direction = Vector3To2Normalise(direction) * force;
	
	// Give it a momentary force
	mPhysicsBody->applyCentralImpulse(BtOgre::Convert::toBullet(direction));
}
