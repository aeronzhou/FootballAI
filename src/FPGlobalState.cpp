#include "FieldPlayerState.h"
#include "FieldPlayer.h"
#include "MessageDeliverer.h"
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

	case MSG_PASS:
		{

		}
	}
	return false;
}