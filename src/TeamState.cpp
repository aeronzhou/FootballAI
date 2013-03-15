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

// PositionalAttacking
PositionalAttacking* PositionalAttacking::get()
{
	static PositionalAttacking instance;
	return &instance;
}

void PositionalAttacking::enter(Team* team)
{
	// Set team's assigned region
	team->setAssignedRegion(PlayerPositionManager::get().getAssignedPosition("PositionalAttacking"));
}

void PositionalAttacking::execute(Team* team)
{
	if (!team->allPlayersInAssignedRegions())
	{
		team->sendPlayersToAssignedRegion();
	}
}

void PositionalAttacking::exit(Team* team)
{

}

bool PositionalAttacking::onMessage(Team*, const Message& msg)
{
	return false;
}

// PositionalDefending
PositionalDefending& PositionalDefending::get()
{
	static PositionalDefending instance;
	return instance;
}

void PositionalDefending::enter(Team* team)
{

}

void PositionalDefending::execute(Team* team)
{

}

void PositionalDefending::exit(Team* team)
{

}

bool PositionalDefending::onMessage(Team*, const Message& msg)
{
	return false;
}
