#include "FieldPlayerState.h"
#include "FieldPlayer.h"
#include "MessageDispatcher.h"
#include "Constant.h"

FieldPlayerGlobalState* FieldPlayerGlobalState::get()
{
	static FieldPlayerGlobalState instance;
	return &instance;
}

bool FieldPlayerGlobalState::onMessage(FieldPlayer* receiver, const Message& msg)
{
	switch (msg.msg_type)
	{
	case MSG_BACK_TO_ORIGIN:
		{
			receiver->getStateMachine()->changeState(BackToOrigin::get());
			return true;
		}

	case MSG_RECEIVE_BALL:
		{
			Ogre::Vector3 target = *((Ogre::Vector3*)(msg.data));
			receiver->setTarget(target);
			receiver->getStateMachine()->changeState(Receiving::get());
		}
	}
	return false;
}