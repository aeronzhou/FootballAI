#include "TeamState.h"
#include "Team.h"
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
	team->playersBackForKickOff();
}

void WaitingForKickOff::execute(Team* team)
{
	if (team->allPlayersInAssignedRegions())
	{
		team->getStateMachine()->changeState(PositionalAttacking::get());
	}
}

void WaitingForKickOff::exit(Team* team)
{

}

bool WaitingForKickOff::onMessage(Team*, const Message& msg)
{
	return false;
}