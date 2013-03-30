#include "GoalKeeper.h"
#include "Team.h"
#include "Goal.h"
#include "ParamLoader.h"

GoalKeeper::GoalKeeper(const QString name, float control_range, float max_speed, 
	float max_force, float mass, float turn_rate, QString mesh_handle, 
	QString material_handle, Team* team, int assigned_region)
	: Player(name, control_range, max_speed, max_force, mass, turn_rate, 
	mesh_handle, material_handle, team, assigned_region, GOAL_KEEPER) {}


void GoalKeeper::onInitialize()
{
	Player::onInitialize();

}

void GoalKeeper::onDeinitialize()
{
	Player::onDeinitialize();
}


void GoalKeeper::onUpdate(double time_diff)
{
	this->mIsUpdatingAfterChange = (time_diff == 0);

	//Update here

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
	target.x = goal->getCenter().x + (getTeam()->getTeamColor() == Team::RED ? 1 : -1) * goal->getPenaltyAreaWidth() / 2;

	target.z = getPitch()->getPlayingArea()->getCenter().z - goal->getPenaltyAreaLength() / 2 + 
		(getBall()->getPosition().z - getPitch()->getPlayingArea()->getCenter().z) * goal->getPenaltyAreaLength() /
		getPitch()->getPlayingArea()->getHeight();

	return target;
}