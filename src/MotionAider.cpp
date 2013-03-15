#include "MotionAider.h"
#include "Player.h"
#include "Ball.h"
#include "ParamLoader.h"
#include "PlayerManager.h"
#include "Utils.h"
#include "Constant.h"

MotionAider::MotionAider(Player* player, Ball* ball)
	: mPlayer(player), mBall(ball),	mFlag(0), mMaxForce(player->getMaxForce()) {}

bool MotionAider::on(MotionType type) const
{
	 return ((mFlag & type) == type);
}

// Set On 
void MotionAider::seekOn()
{
	mFlag |= SEEK;
}

void MotionAider::arriveOn()
{
	mFlag |= ARRIVE;
}

void MotionAider::pursuitOn()
{
	mFlag |= PERSUIT;
}

void MotionAider::separationOn()
{
	mFlag |= SEPARATION;
}

void MotionAider::interposeOn()
{
	mFlag |= INTERPOSE;
}

// Bool

bool MotionAider::isSeekOn() const 
{
	return on(SEEK);
}

bool MotionAider::isArriveOn() const 
{
	return on(ARRIVE);
}

bool MotionAider::isPersuitOn() const 
{
	return on(PERSUIT);
}

bool MotionAider::isSeperationOn() const 
{
	return on(SEPARATION);
}

bool MotionAider::isInterposeOn() const 
{
	return on(SEPARATION);
}

// Set Off

void MotionAider::seekOff()
{
	if (on(SEEK))
		mFlag ^= SEEK;
}

void MotionAider::arriveOff()
{
	if (on(ARRIVE))
		mFlag ^= ARRIVE;
}

void MotionAider::interposeOff()
{
	if (on(INTERPOSE))
		mFlag ^= INTERPOSE;
}

void MotionAider::persuitOff()
{
	if (on(PERSUIT))
		mFlag ^= PERSUIT;
}

void MotionAider::seperationOff()
{
	if (on(SEPARATION))
		mFlag ^= SEPARATION;
}

Ogre::Vector3 MotionAider::seek(Ogre::Vector3 target)
{
	Ogre::Vector3 velocity = Vector3To2Normalise(target - mPlayer->getPosition()) * mPlayer->getMaxSpeed();

	return (velocity - mPlayer->getVelocity());
}

Ogre::Vector3 MotionAider::arrive(Ogre::Vector3 target, Deceleration decel)
{
	Ogre::Vector3 to_target = target - mPlayer->getPosition();
	Ogre::Vector3 this_pos = mPlayer->getPosition();
	float dist = to_target.length();

	if (abs(dist) > EPS) // Not zero
	{
		float decelerate_factor = Prm.DecelerationTweaker * decel;
		
		// Not over the MaxSpeed
		float speed = std::min(mPlayer->getMaxSpeed(), dist / decelerate_factor);

		Ogre::Vector3 disire_velocity = to_target.normalisedCopy() * speed;

		Ogre::Vector3 result = disire_velocity - mPlayer->getVelocity();

		Ogre::Vector3 getVelo = mPlayer->getVelocity();

		return disire_velocity - mPlayer->getVelocity();
	}

	return Ogre::Vector3::ZERO;
}

Ogre::Vector3 MotionAider::persuit(const Ball* ball)
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

Ogre::Vector3 MotionAider::separation()
{
	Ogre::Vector3 force(0, 0, 0);

	std::vector<Player*>& members = PlayerManager::get().getAllMembers();

	for (auto it = members.begin(); it != members.end(); ++it)
	{
		if (mPlayer != (*it) && !(*it)->getMotionAider()->isTag())
		{
			Ogre::Vector3 to_target = (*it)->getPosition() - mPlayer->getPosition();
			force += (to_target / to_target.length());
		}
	}

	float sep = Prm.SeperationCoefficient;
	
	return (force * Prm.SeperationCoefficient);
}

Ogre::Vector3 MotionAider::interpose(const Ball* ball, Ogre::Vector3 target, float dis_from_target)
{
	return arrive(target + Vector3To2Normalise(ball->getPosition() - target) * dis_from_target, NORMAL);	
}

void MotionAider::calculate()
{
	// Clear the combine force
	mDrivingForce = Ogre::Vector3::ZERO;

	combineForce();

	regularizeForce();
}

void MotionAider::combineForce()
{
	Ogre::Vector3 force(0, 0, 0);

	tagNeighbouringPlayers();

	if (on(SEPARATION))
	{
		force += separation();
		if (!accumulateForce(mDrivingForce, force)) 
			return;
	}

	if (on(SEEK))
	{
		force += seek(mTarget);
		if (!accumulateForce(mDrivingForce, force))
			return;
	}

	if (on(ARRIVE))
	{
		force += arrive(mTarget, FAST);
		if (!accumulateForce(mDrivingForce, force))
			return;
	}

	if (on(PERSUIT))
	{
		force += persuit(mBall);
		if (!accumulateForce(mDrivingForce, force))
			return;
	}

	if (on(INTERPOSE))
	{
		force += interpose(mBall, mTarget, mInterposeDist);
		if (!accumulateForce(mDrivingForce, force))
			return;
	}
}

void MotionAider::regularizeForce()
{
	if (mDrivingForce.squaredLength() > mMaxForce * mMaxForce)
	{
		mDrivingForce = Vector3To2Normalise(mDrivingForce) * mMaxForce;
	}
	else
	{
		mDrivingForce = Vector3To2(mDrivingForce);
	}
}

void MotionAider::tagNeighbouringPlayers()
{
	std::vector<Player*>& members = PlayerManager::get().getAllMembers();

	for (auto it = members.begin(); it != members.end(); ++it)
	{
		(*it)->getMotionAider()->setTag(false);
		
		if ((*it) != mPlayer &&  
			(*it)->getPosition().squaredDistance(mPlayer->getPosition()) < Prm.VisibleRangeSqr)
		{
			(*it)->getMotionAider()->setTag(true);
		}
	}
}

bool MotionAider::isTag() const
{
	return mTag;
}

void MotionAider::setTag(bool tag)
{
	mTag = tag;
}

bool MotionAider::accumulateForce(Ogre::Vector3& prev_force, Ogre::Vector3 force_add)
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

Ogre::Vector3 MotionAider::getDrivingForce() const 
{
	return mDrivingForce;
}

Ogre::Vector3 MotionAider::getTarget() const 
{
	return mTarget;
}

void MotionAider::setTarget(Ogre::Vector3 target)
{
	mTarget = target;
}