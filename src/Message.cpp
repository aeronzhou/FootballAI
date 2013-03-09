#include "Message.h"

#include <math.h>

const double MIN_TIME_DELAY_DIFF = 0.15;

Message::Message(): deliver_time(-1), sender(NULL), receiver(NULL) {}

Message::Message(double deliver_time, MovingEntity* sender, MovingEntity* receiver, MessageType msg_type, void* data)
	: deliver_time(deliver_time), sender(sender), receiver(receiver), msg_type(msg_type), data(data) {}

bool Message::operator < (const Message& t) const 
{
	if (fabs(deliver_time - t.deliver_time) < MIN_TIME_DELAY_DIFF &&
		sender == t.sender &&
		receiver == t.receiver)
	{
		return false;
	}

	return deliver_time < t.deliver_time;
}