#include "Message.h"

#include <math.h>

const double MIN_TIME_DELAY_DIFF = 0.15;

Message::Message(): deliver_time(-1), sender(NULL), receiver(NULL) {}

Message::Message(double time, MovingEntity* sender, MovingEntity* receiver, const QString& contents, void* info)
	: deliver_time(time), sender(sender), receiver(receiver), contents(contents), info(info) {}


bool operator== (const Message& p1, const Message& p2)
{
	return ((fabs(p1.deliver_time - p2.deliver_time) < MIN_TIME_DELAY_DIFF) &&
			p1.sender == p2.sender &&
			p2.receiver == p2.receiver);
}

bool operator< (const Message& p1, const Message& p2)
{
	if (p1 == p2)
	{
		return false;
	}

	return p1.deliver_time < p2.deliver_time;
}

//std::ostream& operator<<(std::ostream& os, const Message& msg)
//{
//	os << "From " << msg.sender << " to " << msg.receiver << ", contents: " << msg.contents;
//	return os;
//}
