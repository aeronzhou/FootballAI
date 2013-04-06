#include "FieldPlayerState.h"
#include "FieldPlayer.h"
#include "SteeringBehaviors.h"
#include "ParamLoader.h"
#include "Utils.h"
#include "Team.h"

Receiving* Receiving::get()
{
	static Receiving instance;
	return &instance;
}

void Receiving::enter(FieldPlayer* player)
{
	//player->getSteering()->setArriveOn();	
	//player->getSteering()->setPursuitOn();
	player->getTeam()->setReceivingPlayer(player);	

	if ( (player->isInHotRegion() ||
		WithPossibility(Prm.ChanceOfUsingArriveToReceiveBall) ) && 
		!player->isOpponentWithinRange(Prm.PassThreatRadius) )
	{
		player->getSteering()->setArriveOn();
	}
	else 
	{
		player->getSteering()->setPursuitOn();
	}

	// The player is also the controlling player
	player->getTeam()->setControllingPlayer(player);
}

void Receiving::execute(FieldPlayer* player)
{
	// The ball is interuppted by others
	if (!player->getTeam()->isInControl() || 
		player->isWithinReceivingRange())
	{
		player->getStateMachine()->changeState(ChasingBall::get());
	}

	if (player->getSteering()->isPersuitOn())
	{
		//std::cout << "IsPursuitOn" << std::endl;
		player->setTarget(player->getBall()->getPosition());
	}

	Ogre::Vector3 target = player->getTarget();
	Ogre::Vector3 position = player->getPosition();

	// Player arrive there
	if (player->isAtTarget())
	{
		// Wait there and face to the ball
		player->getSteering()->setArriveOff();
		player->getSteering()->setPursuitOff();
		player->slowDown();
		player->turnAroundToBall();
	}
}

void Receiving::exit(FieldPlayer* player)
{
	player->getSteering()->setPursuitOff();
	player->getSteering()->setArriveOff();
	player->getTeam()->setReceivingPlayer(nullptr);
}

bool Receiving::onMessage(FieldPlayer*, const Message&)
{
	return false;
}