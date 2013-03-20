#include "FieldPlayerState.h"
#include "FieldPlayer.h"
#include "MessageDeliverer.h"
#include "Team.h"
#include "Ball.h"
#include "Constant.h"


// Dribbling
Dribbling* Dribbling::get()
{
	static Dribbling instance;
	return &instance;
}

void Dribbling::enter(FieldPlayer* player)
{
	// Set team controller	
	player->getTeam()->setControllingPlayer(player);
	player->getTeam()->getOpponent()->setControllingPlayer(nullptr);
}

void Dribbling::execute(FieldPlayer* player)
{
	Ogre::Quaternion rotation = player->getRotation();

	// Can shoot 

	// Can pass

	// Go on controlling the ball
	Ball* ball = player->getBall();
	ball->kick(rotation * Ogre::Vector3(0, 0, 1), 1.f);
	player->getStateMachine()->changeState(ChasingBall::get());

}

void Dribbling::exit(FieldPlayer*)
{

}

bool Dribbling::onMessage(FieldPlayer*, const Message&)
{
	return false;
}