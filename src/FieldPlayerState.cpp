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

BackToOrigin* BackToOrigin::get()
{
	static BackToOrigin instance;
	return &instance;
}

void BackToOrigin::enter(FieldPlayer* player)
{
	//dt::Logger::get().debug("Enter to Back To Origin...");
	player->getMotionAider()->arriveOn();
	player->setTarget(player->getAssignedRegion()->getCenter());
}

void BackToOrigin::execute(FieldPlayer* player)
{
	// If player arrive the region
	if (player->getAssignedRegion()->inside(player->getPosition(), Region::HALF_SIZE))
	{
		player->getStateMachine()->changeState(Waiting::get());
	}
}

void BackToOrigin::exit(FieldPlayer* player)
{
	player->getMotionAider()->arriveOff();
}

bool BackToOrigin::onMessage(FieldPlayer*, const Message&)
{
	return false;
}

// Waiting
Waiting* Waiting::get()
{
	static Waiting instance;
	return &instance;
}

void Waiting::enter(FieldPlayer*)
{
	dt::Logger::get().debug("Enter to Back To Origin...");
}

void Waiting::execute(FieldPlayer*)
{

}

void Waiting::exit(FieldPlayer*)
{

}

bool Waiting::onMessage(FieldPlayer*, const Message&)
{
	return false;
}