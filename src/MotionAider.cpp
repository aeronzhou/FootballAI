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
void MotionAider::setSeekOn()
{
	mFlag |= SEEK;
}

void MotionAider::setArriveOn()
{
	mFlag |= ARRIVE;
}

void MotionAider::setPursuitOn()
{
	mFlag |= PERSUIT;
}

void MotionAider::setSeparationOn()
{
	mFlag |= SEPARATION;
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

// Set Off

void MotionAider::setSeekOff()
{
	if (on(SEEK))
		mFlag ^= SEEK;
}

void MotionAider::setArriveOff()
{
	if (on(ARRIVE))
		mFlag ^= ARRIVE;
}

void MotionAider::setPersuitOff()
{
	if (on(PERSUIT))
		mFlag ^= PERSUIT;
}

void MotionAider::setSeperationOff()
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
	std::vector<Player*>& members = PlayerManager::get().getAllMembers();

	Ogre::Vector3 force(0, 0, 0);

	for (auto it = members.begin(); it != members.end(); ++it)
	{
		if (mPlayer != (*it) && (*it)->getMotionAider()->isTag())
		{
			Ogre::Vector3 to_target = mPlayer->getPosition() - (*it)->getPosition();
			force += (to_target / to_target.length());
		}
	}

	// Add some noise to avoid players gather together
	return ((force /*+ Ogre::Vector3(-0.1, 0, 0.1)*/ ) * Prm.SeperationCoefficient);
}

void MotionAider::calculateDrivingForce()
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