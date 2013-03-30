#include "MessageDispatcher.h"
#include "Timer.h"
#include "Constant.h"

MessageDispatcher& MessageDispatcher::get()
{
	static MessageDispatcher singleton;
	return singleton;
}

void MessageDispatcher::dispatchMessage(double delay_time, MovingEntity* sender, 
	MovingEntity* receiver, MessageType msg_type, void* data)
{
	Message msg(delay_time, sender, receiver, msg_type, data);

	if (delay_time < EPS)
	{
		dispatchMessageNow(msg);
	}
	else 
	{
		msg.deliver_time += Timer::get().getCurrentTime();
		mMessagePool.insert(msg);
	}
}

void MessageDispatcher::dispatchMessageNow(const Message& msg)
{
	MovingEntity* receiver = msg.receiver;

	receiver->handleMessage(msg);
}

void MessageDispatcher::latelyDispatchMessage()
{
	double current_time = Timer::get().getCurrentTime();

	while (!mMessagePool.empty() &&
		   mMessagePool.begin()->deliver_time < current_time)
	{
		dispatchMessageNow(*mMessagePool.begin());
		mMessagePool.erase(mMessagePool.begin());
	}
}