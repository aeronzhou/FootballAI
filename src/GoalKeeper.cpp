#include "GoalKeeper.h"
#include "Team.h"
#include "Goal.h"
#include "GoalKeeperState.h"
#include "StateMachine.h"
#include "ParamLoader.h"
#include "Utils.h"

GoalKeeper::GoalKeeper(const QString name, float control_range, float max_speed, 
	float max_force, float mass, float turn_rate, QString mesh_handle, 
	QString material_handle, Team* team, int assigned_region)
	: Player(name, control_range, max_speed, max_force, mass, turn_rate, 
	mesh_handle, material_handle, team, assigned_region, GOAL_KEEPER) {}


void GoalKeeper::onInitialize()
{
	Player::onInitialize();

	mStateMachine = new StateMachine<GoalKeeper>(this);
	mStateMachine->setCurrentState(ReturnHome::get());
	mStateMachine->setGlobalState(GoalKeeperGlobalState::get());

	// Set defult animation
	mMesh->setAnimation("RunBase");
	mMesh->setLoopAnimation(true);

	mKickCoolingTime = addComponent(new CoolingTimeComponent(Prm.PlayerKickCoolingTime));

}

void GoalKeeper::onDeinitialize()
{
	Player::onDeinitialize();
}


void GoalKeeper::onUpdate(double time_diff)
{
	this->mIsUpdatingAfterChange = (time_diff == 0);

	mStateMachine->onUpdate();

	// Update here
	mSteeringBehaviors->calculateDrivingForce();

	// Apply a small rotation 
	Ogre::Quaternion rotation = GetRotationThroughHeading(getBall()->getPosition() - getPosition());
	Ogre::Vector3 current_velocity = getVelocity();

	Ogre::Vector3 driving_force = mSteeringBehaviors->getSteeringForce();

	btTransform trans = mPhysicsBody->getRigidBody()->getWorldTransform();
	btMotionState* motion = mPhysicsBody->getRigidBody()->getMotionState();

	if (driving_force.length() > 1e-7)
	{
		current_velocity += driving_force;
		Vector3Truncate(current_velocity, mMaxSpeed);
	} 
	else 
	{
		current_velocity *= 0.8;
	}

	mVelocity = current_velocity;

	trans.setOrigin(trans.getOrigin() + BtOgre::Convert::toBullet(mVelocity) * 0.02);
	trans.setRotation(BtOgre::Convert::toBullet(rotation));
	
	motion->setWorldTransform(trans);

	mIsTurnningAroundAtTarget = Ogre::Radian(0);

	setDebugText(getStateMachine()->getNameOfCurrentState());

	Player::onUpdate(time_diff);
}

StateMachine<GoalKeeper>* GoalKeeper::getStateMachine() const 
{
	return mStateMachine;
}

float GoalKeeper::getDistToGoal() const 
{
	return getPosition().distance(getTeam()->getGoal()->getCenter());
}

bool GoalKeeper::isBallWithInterceptRange() const 
{
	return getDistToBall() < Prm.GoalKeeperInterceptRange;
}

bool GoalKeeper::isTooFarFromGoalMouth() const 
{
	//////////////////////////////////////////////////////////////////////////
	return getDistToGoal() > 12.f;
}

Ogre::Vector3 GoalKeeper::getRearInterposeTarget() const 
{
	Ogre::Vector3 target(0, 0, 0);
	Goal* goal = getTeam()->getGoal();
	target.x = goal->getCenter().x;

	target.z = -Prm.HalfGoalWidth +	2 * Prm.HalfGoalWidth * (getBall()->getPosition().z - getPitch()->getPlayingArea()->getTop()) /
		getPitch()->getPlayingArea()->getHeight();

	return target;
}