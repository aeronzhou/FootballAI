#include "FieldPlayerState.h"
#include "Team.h"

Positioning* Positioning::get()
{
	static Positioning instance;
	return &instance;
}

void Positioning::enter(FieldPlayer* player)
{
	player->getSteering()->setArriveOn();
	player->setTarget(player->getAssignedRegion()->getCenter());
}

void Positioning::execute(FieldPlayer* player)
{
	if (player->isClosestTeamMemberToBall() && 
		player->getTeam()->getReceivingPlayer() == nullptr) // && !GoalKeeperHasBall()
	{
		player->getStateMachine()->changeState(ChasingBall::get());
		return;
	}

	// Update proper spot

	// If the player arrive the place, change to wait
	if (player->isAtTarget())
	{
		player->getStateMachine()->changeState(Waiting::get());
	}
}

void Positioning::exit(FieldPlayer* player)
{
	player->getSteering()->setArriveOff();
}

bool Positioning::onMessage(FieldPlayer*, const Message&)
{
	return false;
}