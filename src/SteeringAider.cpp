#include "SteeringAider.h"
#include "Player.h"
#include "Ball.h"
#include "ParamLoader.h"
#include "Utils.h"
#include "Constant.h"

SteeringAider::SteeringAider(Player* player, Ball* ball)
	: mPlayer(player), mBall(ball),	mFlag(0), mMaxForce(player->getMaxForce()) {}

bool SteeringAider::on(SteeingType type) const
{
	 return ((mFlag & type) == type);
}

// Set On 
void SteeringAider::seekOn()
{
	mFlag |= SEEK;
}

void SteeringAider::arriveOn()
{
	mFlag |= ARRIVE;
}

void SteeringAider::pursuitOn()
{
	mFlag |= PERSUIT;
}

void SteeringAider::separationOn()
{
	mFlag |= SEPARATION;
}

void SteeringAider::interposeOn()
{
	mFlag |= INTERPOSE;
}

// Bool

bool SteeringAider::isSeekOn() const 
{
	return on(SEEK);
}

bool SteeringAider::isArriveOn() const 
{
	return on(ARRIVE);
}

bool SteeringAider::isPersuitOn() const 
{
	return on(PERSUIT);
}

bool SteeringAider::isSeperationOn() const 
{
	return on(SEPARATION);
}

bool SteeringAider::isInterposeOn() const 
{
	return on(SEPARATION);
}

// Set Off

void SteeringAider::seekOff()
{
	if (on(SEEK))
		mFlag ^= SEEK;
}

void SteeringAider::arriveOff()
{
	if (on(ARRIVE))
		mFlag ^= ARRIVE;
}

void SteeringAider::interposeOff()
{
	if (on(INTERPOSE))
		mFlag ^= INTERPOSE;
}

void SteeringAider::persuitOff()
{
	if (on(PERSUIT))
		mFlag ^= PERSUIT;
}

void SteeringAider::seperationOff()
{
	if (on(SEPARATION))
		mFlag ^= SEPARATION;
}

//////////////////////////////////////////////////////////////////////////
Ogre::Vector3 SteeringAider::seek(Ogre::Vector3 target)
{
	//return Ogre::Vector3::ZERO;	
	Ogre::Vector3 velocity = Vector3To2Normalise(target - mPlayer->getPosition()) * mPlayer->getMaxSpeed();

	return (velocity - mPlayer->getVelocity());
}

Ogre::Vector3 SteeringAider::arrive(Ogre::Vector3 target, Deceleration decel)
{
	Ogre::Vector3 to_target = target - mPlayer->getPosition();
	float dist = to_target.length();

	if (abs(dist) > EPS) // Not zero
	{
		float decelerate_factor = Prm.DecelerationTweaker * decel;
		
		// Not over the MaxSpeed
		float speed = std::min(mPlayer->getMaxSpeed(), dist / decelerate_factor);

		Ogre::Vector3 disire_velocity = to_target.normalisedCopy() * speed;

		return disire_velocity - mPlayer->getVelocity();
	}

	return Ogre::Vector3::ZERO;
}

Ogre::Vector3 SteeringAider::persuit(const Ball* ball)
{
	Ogre::Vector3 to_target = ball->getPosition() - mPlayer->getPosition();
	float ball_dot_player = ball->getHeading().dotProduct(mPlayer->getHeading());

	if (ball_dot_player < -0.95 &&
		to_target.dotProduct(mPlayer->getHeading()) > 0)
	{
		return seek(ball->getPosition());
	}

	float look_ahead_time = to_target.length() / (mPlayer->getMaxSpeed() + ball->getMaxSpeed());
	
	return seek(ball->getPosition() + ball->getVelocity() * look_ahead_time);	
}

Ogre::Vector3 SteeringAider::separation()
{
	Ogre::Vector3 force;

	std::vector<Player*>& members = mPlayer->getAllMembers();

	for (auto it = members.begin(); it != members.end(); ++it)
	{
		if (mPlayer != (*it) && !(*it)->getSteering()->isTag())
		{
			Ogre::Vector3 to_target = (*it)->getPosition() - mPlayer->getPosition();
			force += (to_target / to_target.length());
		}
	}
	
	return (force * Prm.SeperationCoefficient);
}

Ogre::Vector3 SteeringAider::interpose(const Ball* ball, Ogre::Vector3 target, float dis_from_target)
{
	return arrive(target + Vector3To2Normalise(ball->getPosition() - target) * dis_from_target, NORMAL);	
}

void SteeringAider::calculate()
{
	// Clear the combine force
	mSteeringForce = Ogre::Vector3::ZERO;

	combineForce();

	regularizeForce();
}

void SteeringAider::combineForce()
{
	Ogre::Vector3 force;

	findNeighbours();

	if (on(SEPARATION))
	{
		force += separation();
		if (!accumulateForce(mSteeringForce, force)) 
			return;
	}

	if (on(SEEK))
	{
		force += seek(mTarget);
		if (!accumulateForce(mSteeringForce, force))
			return;
	}

	if (on(ARRIVE))
	{
		force += arrive(mTarget, FAST);
		if (!accumulateForce(mSteeringForce, force))
			return;
	}

	if (on(PERSUIT))
	{
		force += persuit(mBall);
		if (!accumulateForce(mSteeringForce, force))
			return;
	}

	if (on(INTERPOSE))
	{
		force += interpose(mBall, mTarget, mInterposeDist);
		if (!accumulateForce(mSteeringForce, force))
			return;
	}
}

void SteeringAider::regularizeForce()
{
	if (mSteeringForce.squaredLength() > mMaxForce * mMaxForce)
	{
		mSteeringForce = Vector3To2Normalise(mSteeringForce) * mMaxForce;
	}
	else
	{
		mSteeringForce = Vector3To2(mSteeringForce);
	}
}

void SteeringAider::findNeighbours()
{
	std::vector<Player*>& members = mPlayer->getAllMembers();

	for (auto it = members.begin(); it != members.end(); ++it)
	{
		(*it)->getSteering()->setTag(false);
		
		if ((*it) != mPlayer &&  
			(*it)->getPosition().squaredDistance(mPlayer->getPosition()) < Prm.VisibleRangeSqr)
		{
			(*it)->getSteering()->setTag(true);
		}
	}
}

bool SteeringAider::isTag() const
{
	return mTag;
}

void SteeringAider::setTag(bool tag)
{
	mTag = tag;
}

bool SteeringAider::accumulateForce(Ogre::Vector3& prev_force, Ogre::Vector3 force_add)
{
	float magnitude_remain = mMaxForce - prev_force.length();

	// Over max force
	if (magnitude_remain < EPS)
		return false;

	if (magnitude_remain > force_add.length())
	{
		prev_force += force_add;
	}
	else 
	{
		prev_force += force_add.normalise() * magnitude_remain;
	}

	return true;
}

Ogre::Vector3 SteeringAider::getSteeringForce() const 
{
	return mSteeringForce;
}