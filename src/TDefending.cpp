#include "TeamState.h"
#include "Team.h"
#include "PlayerPositionManager.h"


// Defending
Defending* Defending::get()
{
	static Defending instance;
	return &instance;
}

void Defending::enter(Team* team)
{
	// Set team's assigned region
	team->setAssignedRegion(PlayerPositionManager::get().getAssignedPosition("Defending"));

	team->updateTargetsOfWaitingPlayers();
}

void Defending::execute(Team* team)
{
	if (team->isInControl())
	{
		team->getStateMachine()->changeState(Attacking::get());
	}
}

void Defending::exit(Team* team)
{

}

bool Defending::onMessage(Team*, const Message& msg)
{
	return false;
}