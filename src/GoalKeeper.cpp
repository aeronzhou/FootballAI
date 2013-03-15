#include "GoalKeeper.h"

GoalKeeper::GoalKeeper(const QString name, float bounding_radius, float max_speed, 
	float max_force, float mass, float turn_rate, QString mesh_handle, 
	QString material_handle, Team* team, int assigned_region)
	: Player(name, bounding_radius, max_speed, max_force, mass, turn_rate, 
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

bool GoalKeeper::ballWithRangeForIntercept() const 
{
	return false;
}

bool GoalKeeper::tooFarFromGoalMouth() const 
{
	return false;
}