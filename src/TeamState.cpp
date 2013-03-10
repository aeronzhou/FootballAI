#include "TeamState.h"
#include "Team.h"
#include "PlayerPositionManager.h"

// WaitingForKickOff
WaitingForKickOff* WaitingForKickOff::get()
{
	static WaitingForKickOff instance;
	return &instance;
}

std::vector<int> WaitingForKickOff::getOriginPosition()
{
	if (mOriginPosition.empty())
	{
		mOriginPosition = PlayerPositionManager::get().getOriginPosition("WaitingForKickOff");
	}
	return mOriginPosition;
}

void WaitingForKickOff::enter(Team* team)
{

}

void WaitingForKickOff::execute(Team* team)
{

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

std::vector<int> PositionalAttacking::getOriginPosition()
{
	if (mOriginPosition.empty())
	{
		mOriginPosition = PlayerPositionManager::get().getOriginPosition("PositionalAttacking");
	}
	return mOriginPosition;
}

void PositionalAttacking::enter(Team* team)
{

}

void PositionalAttacking::execute(Team* team)
{

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

std::vector<int> PositionalDefending::getOriginPosition()
{
	if (mOriginPosition.empty())
	{
		mOriginPosition = PlayerPositionManager::get().getOriginPosition("PositionalDefending");
	}
	return mOriginPosition;
}