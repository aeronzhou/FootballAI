#include "FieldPlayerState.h"
#include "FieldPlayer.h"
#include "Ball.h"
#include "Team.h"
#include "ParamLoader.h"
#include "MessageDispatcher.h"
#include "Constant.h"

FieldPlayerGlobalState* FieldPlayerGlobalState::get()
{
	static FieldPlayerGlobalState instance;
	return &instance;
}

bool FieldPlayerGlobalState::onMessage(FieldPlayer* player, const Message& msg)
{
	switch (msg.msg_type)
	{
	case MSG_BACK_TO_ORIGIN:
		{
			player->getStateMachine()->changeState(BackToOrigin::get());

			return true;
		}

	case MSG_RECEIVE_BALL:
		{
			Ogre::Vector3 target = *((Ogre::Vector3*)(msg.data));
			player->setTarget(target);
			player->getStateMachine()->changeState(Receiving::get());

			return true;
		}

	case MSG_REQUEST_PASS:
		{
			FieldPlayer* receiver = static_cast<FieldPlayer*>(msg.data);

			// Cannot pass the ball
			if (player->getTeam()->getReceivingPlayer() != nullptr ||
				!player->isBallWithinControlRange())
			{
				return true;
			}

			// Make the pass
			player->getBall()->kick(receiver->getPosition() - player->getBall()->getPosition(), 
				Prm.PlayerMaxPassingForce);

			MessageDispatcher::get().dispatchMessage(
				DELIVER_IMMEDIATELY,
				player, 
				receiver, 
				MSG_RECEIVE_BALL,
				&receiver->getPosition()
				);

			player->getStateMachine()->changeState(Waiting::get());

			player->findSupport();

			return true;
		}

	case MSG_SUPPORT_ATTACKER:
		{
			// Already in this state
			if (player->getStateMachine()->isInState(*SupportAttacker::get()))
			{
				return true;
			}

			player->setTarget(player->getTeam()->getBestSupportSpot());

			player->getStateMachine()->changeState(SupportAttacker::get());

			return true;
		}

	case MSG_POSITIONING:
		{
			player->getStateMachine()->changeState(Positioning::get());

			return true;
		}

	case MSG_WAIT:
		{
			player->getStateMachine()->changeState(Waiting::get());

			return true;
		}

	case MSG_TURN_AROUND:
		{
			player->setIsAskedToTurnAround(true);
			player->setAskedTurnAroundTarget(msg.sender->getPosition());

			return true;	
		}
	}
	return false;
}