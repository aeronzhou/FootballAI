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
		}

	case MSG_REQUEST_PASS:
		{
			FieldPlayer* receiver = static_cast<FieldPlayer*>(msg.data);

			// Cannot pass the ball
			if (receiver->getTeam()->getReceivingPlayer() != nullptr ||
				!receiver->isBallWithinControlRange())
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
	}
	return false;
}