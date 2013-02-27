#include "Goal.h"
#include "Ball.h"
#include "Utils.h"

#include <Graphics/MeshComponent.hpp>
#include <Physics/PhysicsBodyComponent.hpp>

#include <OgreProcedural.h>

Goal::Goal(const QString& name, Ogre::Vector3 left, Ogre::Vector3 right, Ogre::Vector3 facing, Ball* ball)
	: dt::Node(name), mLeftPost(left), mRightPost(right), mFacing(facing), mBall(ball), mScores(0) {}

void Goal::onInitialize()
{
	OgreProcedural::BoxGenerator().setSize(Ogre::Vector3(0.5, 2, 5)).realizeMesh("Goal");

	addComponent(new dt::MeshComponent("Goal", "", "MeshComponent"));
	addComponent(new dt::PhysicsBodyComponent("MeshComponent", "PhysicsBodyComponent", dt::PhysicsBodyComponent::CONVEX, 0.f));
}

void Goal::onUpdate(double time_diff)
{
	mIsUpdatingAfterChange = (time_diff == 0);

	// Update here

	dt::Node::onUpdate(time_diff);
}

// Get function
Ogre::Vector3 Goal::getLeftPost() const
{
	return mLeftPost;
}

Ogre::Vector3 Goal::getRightPost() const
{
	return mRightPost;
}

Ogre::Vector3 Goal::getCenter() const
{
	return mCenter;
}

Ogre::Vector3 Goal::getFacing() const
{
	return mFacing;
}

int Goal::getScores() const
{
	return mScores;
}

bool Goal::isScored()
{
	if (IsLineIntersect(mLeftPost, mRightPost, mBall->getOldPos(), mBall->getPosition()))
	{
		++mScores;
		return true;
	}

	return false;
}

void Goal::resetPhysicsBody()
{
	auto physics_body = findComponent<dt::PhysicsBodyComponent>("PhysicsBodyComponent");
	physics_body->disable();
	physics_body->enable();
}