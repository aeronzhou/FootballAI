#include "TeamState.h"
#include "Team.h"
#include "PlayerPositionManager.h"

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