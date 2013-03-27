#include "TeamState.h"
#include "Team.h"
#include "Pitch.h"
#include "PlayerPositionManager.h"

// WaitingForKickOff
WaitingForKickOff* WaitingForKickOff::get()
{
	static WaitingForKickOff instance;
	return &instance;
}

void WaitingForKickOff::enter(Team* team)
{
	// Set team's assigned region
	team->setAssignedRegion(PlayerPositionManager::get().getAssignedPosition("WaitingForKickOff"));
	
	team->setControllingPlayer(nullptr);
	team->setReceivingPlayer(nullptr);
	team->setSupportingPlayer(nullptr);

	team->playersBackForKickOff();
}

void WaitingForKickOff::execute(Team* team)
{
	if (team->allPlayersInAssignedRegions())
	{
		//if (team->getPitch()->isGoingForKickingOff(team))
		//{
		//	team->getStateMachine()->changeState(Attacking::get());
		//}
		//else 
		//{
		//	team->getStateMachine()->changeState(Defending::get());
		//}
		// 稍后实现该功能，
		// 判断由哪支队开球
		// 现在统一一开始转为防守
		team->getStateMachine()->changeState(Defending::get());
	}
}

void WaitingForKickOff::exit(Team* team)
{
	// Now we can start the game
	team->getPitch()->setGameOn(true);
}

bool WaitingForKickOff::onMessage(Team*, const Message& msg)
{
	return false;
}