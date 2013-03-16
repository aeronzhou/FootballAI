#include "TeamState.h"
#include "Team.h"
#include "PlayerPositionManager.h"

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