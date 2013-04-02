#include "FieldPlayerState.h"
#include "FieldPlayer.h"
#include "Team.h"
#include "ParamLoader.h"

SupportAttacker* SupportAttacker::get()
{
	static SupportAttacker instance;
	return &instance;
}

void SupportAttacker::enter(FieldPlayer* player)
{
	player->getSteering()->setArriveOn();
	player->setTarget(player->getTeam()->getBestSupportSpot());
}

void SupportAttacker::execute(FieldPlayer* player)
{
	// Lost the ball
	if (!player->getTeam()->isInControl())
	{
		player->getStateMachine()->changeState(Positioning::get());
		return;
	}

	// Update if the best support spot changed
	if (player->getTeam()->getBestSupportSpot() != player->getTarget())
	{
		player->setTarget(player->getTeam()->getBestSupportSpot());
		player->getSteering()->setArriveOn();
	}

	// If the player can shot 
	if (player->getTeam()->canShoot(player->getPosition(), Ogre::Vector3(), Prm.PlayerMaxShootingForce))
	{
		player->getTeam()->requestPass(player);
	}

	if (player->isAtTarget())
	{
		player->getSteering()->setArriveOff();
		player->turnAroundToBall();
		player->setVelocity(Ogre::Vector3::ZERO);

		// If this is not threatened, request pass
		if (!player->isThreatened())
		{
			player->getTeam()->requestPass(player);
		}
	}
}

void SupportAttacker::exit(FieldPlayer* player)
{
	player->getTeam()->setSupportingPlayer(nullptr);
	player->getSteering()->setArriveOff();
}

bool SupportAttacker::onMessage(FieldPlayer*, const Message&)
{
	return false;
}