#include "SteeringBehaviors.h"
#include "Player.h"
#include "Ball.h"
#include "Utils.h"

SteeringBehaviors::SteeringBehaviors(Player* player, Ball* ball)
	: mPlayer(player), mBall(ball),	mFlag(0) {}

void SteeringBehaviors::seekOff()
{
	if (on(SEEK))
		mFlag ^= SEEK;
}

void SteeringBehaviors::arriveOff()
{
	if (on(ARRIVE))
		mFlag ^= ARRIVE;
}

void SteeringBehaviors::interposeOff()
{
	if (on(INTERPOSE))
		mFlag ^= INTERPOSE;
}

void SteeringBehaviors::persuitOff()
{
	if (on(PERSUIT))
		mFlag ^= PERSUIT;
}

void SteeringBehaviors::seperationOff()
{
	if (on(SEPARATION))
		mFlag ^= SEPARATION;
}

//////////////////////////////////////////////////////////////////////////
Ogre::Vector3 SteeringBehaviors::seek(Ogre::Vector3 target)
{
	//return Ogre::Vector3::ZERO;	
	auto velocity = Vector3To2Normalise(target - mPlayer->getPosition()) * mPlayer->getMaxSpeed();

	return Ogre::Vector3::ZERO;	
}

Ogre::Vector3 SteeringBehaviors::arrive(Ogre::Vector3 target, Deceleration decel)
{
	return Ogre::Vector3::ZERO;
}

Ogre::Vector3 SteeringBehaviors::persuit(const Ball* ball)
{
	return Ogre::Vector3::ZERO;
}

Ogre::Vector3 SteeringBehaviors::separation()
{
	return Ogre::Vector3::ZERO;
}

Ogre::Vector3 SteeringBehaviors::interpose(const Ball* ball, Ogre::Vector3 pos, float dis_from_target)
{
	return Ogre::Vector3::ZERO;
}
//////////////////////////////////////////////////////////////////////////