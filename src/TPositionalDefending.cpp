#include "TeamState.h"
#include "Team.h"
#include "PlayerPositionManager.h"

// PositionalDefending
PositionalDefending* PositionalDefending::get()
{
	static PositionalDefending instance;
	return &instance;
}

void PositionalDefending::enter(Team* team)
{
	// Set team's assigned region
	team->setAssignedRegion(PlayerPositionManager::get().getAssignedPosition("PositionalDefending"));
}

void PositionalDefending::execute(Team* team)
{
	//if (!team->allPlayersInAssignedRegions())
	//{
	//	team->sendPlayersToAssignedRegion();
	//}
	
}

void PositionalDefending::exit(Team* team)
{

}

bool PositionalDefending::onMessage(Team*, const Message& msg)
{
	return false;
}