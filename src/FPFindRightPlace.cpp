#include "FieldPlayerState.h"
#include "Team.h"

FindRightPlace* FindRightPlace::get()
{
	static FindRightPlace instance;
	return &instance;
}

void FindRightPlace::enter(FieldPlayer* player)
{
	player->getSteering()->setArriveOn();
	player->setTarget(player->getAssignedRegion()->getCenter());
}

void FindRightPlace::execute(FieldPlayer* player)
{
	if (player->isClosestTeamMemberToBall() && 
		player->getTeam()->getReceivingPlayer() == nullptr) // && !GoalKeeperHasBall()
	{
		player->getStateMachine()->changeState(ChasingBall::get());
		return;
	}

	// Update proper spot

	// If the player arrive the place, change to wait
	if (player->atTarget())
	{
		player->getStateMachine()->changeState(Waiting::get());
	}
}

void FindRightPlace::exit(FieldPlayer* player)
{
	player->getSteering()->setArriveOff();
}

bool FindRightPlace::onMessage(FieldPlayer*, const Message&)
{
	return false;
}