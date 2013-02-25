#include "Goal.h"
#include "Ball.h"
#include "Utils.h"

Goal::Goal(Ogre::Vector3 left, Ogre::Vector3 right, Ogre::Vector3 facing, Ball* ball)
	: mLeftPost(left), mRightPost(right), mFacing(facing), mBall(ball), mScores(0) {}

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

