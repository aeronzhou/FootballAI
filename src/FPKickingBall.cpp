#include "FieldPlayerState.h"
#include "Team.h"
#include "Goal.h"
#include "MessageDispatcher.h"
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

	//std::cout << "KickBall>>> dist_to_ball = "<< player->getDistToBall() << std::endl;

	// Cannot kick the ball
	// This player is behind the ball
	if (dot < 0 ||
		player->getTeam()->getReceivingPlayer() == nullptr ||
		player->getPitch()->isGoalKeeperHasBall() )
	{
		player->getStateMachine()->changeState(ChasingBall::get());
	}

	// Can shoot
	float shooting_foce = Prm.PlayerMaxShootingForce;
	
	// Must face to the goal
	float dot_to_goal = player->getHeading().dotProduct(player->getTeam()->getGoal()->getFacing());

	if (dot_to_goal > 0 && player->getTeam()->canShoot(ball->getPosition(), target, shooting_foce))
	{
		target = AddNoiseToKick(ball->getPosition(), target);
		ball->kick(target - ball->getPosition(), shooting_foce);
		player->getStateMachine()->changeState(ChasingBall::get());

		// Decide to shoot
		// Find supporter
		player->findSupport();

		return;
	}

	// Can pass
	Player* receiver = nullptr;

	if (player->isThreatened() && 
		player->getTeam()->canPass(player, receiver, target, dot))
	{
		MessageDispatcher::get().dispatchMessage(
			0,
			player, 
			receiver,
			MSG_RECEIVE_BALL,
			&target	
			);

		// Adjust passing force
		float passing_force = ball->getProperForceToKick(Vector3To2(receiver->getPosition() - ball->getPosition()).length());

		// Apply a force
		ball->kick(receiver->getPosition() - ball->getPosition(), passing_force);

		//std::cout << "Can Pass!!!!!!" << std::endl;

		// After passing, the player should change to wait
		player->getStateMachine()->changeState(Waiting::get());

		// Decide to pass
		// Find support
		player->findSupport();

		return;
	}

	// Should dribble
	// Ask for help
	player->findSupport();

	player->getStateMachine()->changeState(Dribbling::get());
}

void KickingBall::exit(FieldPlayer*)
{

}

bool KickingBall::onMessage(FieldPlayer*, const Message&)
{
	return false;
}