#include "TeamState.h"
#include "Team.h"
#include "PlayerPositionManager.h"

// Attacking
Attacking* Attacking::get()
{
	static Attacking instance;
	return &instance;
}

void Attacking::enter(Team* team)
{
	// Set team's assigned region
	team->setAssignedRegion(PlayerPositionManager::get().getAssignedPosition("Attacking"));
}

void Attacking::execute(Team* team)
{
	if (!team->isInControl())
	{
		team->getStateMachine()->changeState(Defending::get());
	}
}

void Attacking::exit(Team* team)
{
	team->setSupportingPlayer(nullptr);
}

bool Attacking::onMessage(Team*, const Message& msg)
{
	return false;
}