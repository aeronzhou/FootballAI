#include "FieldPlayerState.h"
#include "FPWaiting.h"
#include "FieldPlayer.h"
#include "MessageDispatcher.h"
#include "Constant.h"

BackToOrigin* BackToOrigin::get()
{
	static BackToOrigin instance;
	return &instance;
}

void BackToOrigin::enter(FieldPlayer* player)
{
	//dt::Logger::get().debug("Enter to Back To Origin...");
	player->getSteering()->setArriveOn();
	player->setTarget(player->getAssignedRegion()->getCenter());
}

void BackToOrigin::execute(FieldPlayer* player)
{
	// If player arrive the region
	if (player->getAssignedRegion()->inside(player->getPosition(), Region::HALF_SIZE))
	{
		player->getStateMachine()->changeState(Waiting::get());
	}
}

void BackToOrigin::exit(FieldPlayer* player)
{
	player->getSteering()->setArriveOff();
}

bool BackToOrigin::onMessage(FieldPlayer*, const Message&)
{
	return false;
}