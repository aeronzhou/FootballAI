#include "FieldPlayerState.h"
#include "Team.h"
#include "MessageDeliverer.h"
#include "Utils.h"
#include "ParamLoader.h"

// KickingBall
KickingBall* KickingBall::get()
{
	static KickingBall instance;
	return &instance;
}

void KickingBall::enter(FieldPlayer* player)
{
	player->getTeam()->setControllingPlayer(player);
	player->getTeam()->getOpponent()->setControllingPlayer(nullptr);

	if (!player->isReadyToKick())
	{
		player->getStateMachine()->changeState(ChasingBall::get());
	}
}

void KickingBall::execute(FieldPlayer* player)
{
	Ball* ball = player->getBall();
	float dot = player->getHeading().dotProduct(player->getBall()->getPosition() - player->getPosition());
	Ogre::Vector3 target;

	if (dot < 0)
	{
		// This player is behind the ball
		player->getStateMachine()->changeState(ChasingBall::get());
	}

	// Cannot kick the ball

	// Can shoot
	float shooting_foce = Prm.PlayerMaxShootingForce * dot;
	if (player->getTeam()->canShoot(player, target, shooting_foce))
	{
		target = AddNoiseToTarget(ball->getPosition(), target);
		ball->kick(target - ball->getPosition(), shooting_foce);
		player->getStateMachine()->changeState(ChasingBall::get());

		return;
	}

	// Can pass
	Player* receiver = nullptr;
	float passing_force = Prm.PlayerMaxPassingForce;

	if (player->isThreatened() && 
		player->getTeam()->canPass(player, receiver, target, dot))
	{
		MessageDeliverer::get().deliverMessage(
			0,
			player, 
			receiver,
			MSG_RECEIVE_BALL,
			&target	
			);

		// Apply a force
		ball->kick(receiver->getPosition() - ball->getPosition(), passing_force);


		// After passing, the player should change to wait
		player->getStateMachine()->changeState(Waiting::get());

		return;
	}

	// Should dribble
	player->getStateMachine()->changeState(Dribbling::get());
}

void KickingBall::exit(FieldPlayer*)
{

}

bool KickingBall::onMessage(FieldPlayer*, const Message&)
{
	return false;
}