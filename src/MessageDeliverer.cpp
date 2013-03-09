#include "MessageDeliverer.h"
#include "Timer.h"
#include "Constant.h"

MessageDeliverer& MessageDeliverer::get()
{
	static MessageDeliverer singleton;
	return singleton;
}

void MessageDeliverer::deliverMessage(double delay_time, MovingEntity* sender, 
	MovingEntity* receiver, MessageType msg_type, void* data)
{
	Message msg(delay_time, sender, receiver, msg_type, data);

	if (delay_time < EPS)
	{
		deliverMessageNow(msg);
	}
	else 
	{
		msg.deliver_time += Timer::get().getCurrentTime();
		mMessagePool.insert(msg);
	}
}

void MessageDeliverer::deliverMessageNow(const Message& msg)
{
	MovingEntity* receiver = msg.receiver;

	receiver->HandleMessage(msg);
}

void MessageDeliverer::latelyDeliverMessage()
{
	double current_time = Timer::get().getCurrentTime();

	while (!mMessagePool.empty() &&
		   mMessagePool.begin()->deliver_time < current_time)
	{
		deliverMessageNow(*mMessagePool.begin());
		mMessagePool.erase(mMessagePool.begin());
	}
}