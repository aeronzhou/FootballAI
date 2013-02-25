#include "SteeringBehaviors.h"
#include "Player.h"
#include "Ball.h"
#include "Utils.h"

SteeringBehaviors::SteeringBehaviors(Player* player, Ball* ball)
	: mPlayer(player), mBall(ball),	mFlag(0) {}

bool SteeringBehaviors::on(SteeingType type) const
{
	 return ((mFlag & type) == type);
}

// Set On 
void SteeringBehaviors::seekOn()
{
	mFlag |= SEEK;
}

void SteeringBehaviors::arriveOn()
{
	mFlag |= ARRIVE;
}

void SteeringBehaviors::pursuitOn()
{
	mFlag |= PERSUIT;
}

void SteeringBehaviors::separationOn()
{
	mFlag |= SEPARATION;
}

void SteeringBehaviors::interposeOn()
{
	mFlag |= INTERPOSE;
}

// Bool

bool SteeringBehaviors::isSeekOn() const 
{
	return on(SEEK);
}

bool SteeringBehaviors::isArriveOn() const 
{
	return on(ARRIVE);
}

bool SteeringBehaviors::isPersuitOn() const 
{
	return on(PERSUIT);
}

bool SteeringBehaviors::isSeperationOn() const 
{
	return on(SEPARATION);
}

bool SteeringBehaviors::isInterposeOn() const 
{
	return on(SEPARATION);
}

// Set Off

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