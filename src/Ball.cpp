#include "Ball.h"
#include "ParamLoader.h"

#include <Graphics/MeshComponent.hpp>
#include <Physics/PhysicsBodyComponent.hpp>

#include <OgreProcedural.h>


Ball::Ball(QString mesh_handle, QString material_handle)
	: MovingEntity("BallNode", 1.0f, 12.f, Ogre::Vector3::ZERO, 12.f, 5.0f, 10.f, mesh_handle, material_handle) {}

void Ball::onInitialize() 
{
	MovingEntity::onInitialize();

	// remove handle first
	removeComponent(getName() + "_mesh");
	removeComponent(getName() + "_physics");

	OgreProcedural::SphereGenerator().setRadius(.3f).setUTile(.1f).realizeMesh("Football");
	addComponent(new dt::MeshComponent("Football", "", "BallMesh"));
	mPhysicsBody = addComponent(new dt::PhysicsBodyComponent("BallMesh", "BallPhysicsBody", dt::PhysicsBodyComponent::SPHERE));

	mPhysicsBody->getRigidBody()->setFriction(2.f);
}

void Ball::onUpdate(double time_diff)
{
	MovingEntity::onUpdate(time_diff);
}

void Ball::ballOutOfPitch()
{

}

void Ball::kick(Ogre::Vector3 direction, float force)
{

}

double Ball::timeToCoverDistance(Ogre::Vector3 from, Ogre::Vector3 to, float force) const
{
	//////////////////////////////////////////////////////////////////////////
	return 0.0;
}

Ogre::Vector3 Ball::futurePosition(double time) const
{
	//////////////////////////////////////////////////////////////////////////
	return getPosition();
}

void Ball::playAtPosition(Ogre::Vector3 pos)
{
	mPhysicsBody->getRigidBody()->setLinearVelocity(btVector3(0.f, 0.f, 0.f));
	this->setPosition(pos);
	this->mOldPos = pos;
	this->resetPhysicsBody();
}