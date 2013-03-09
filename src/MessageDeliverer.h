#ifndef FOOTBALL_AI_MESSAGE_DELIVERER
#define FOOTBALL_AI_MESSAGE_DELIVERER

#include "Message.h"

#include <set>

/** 
  * A singleton class to dispatch message
  */ 
class MessageDeliverer
{
public:

	/** 
	  * Singleton
	  */
	static MessageDeliverer& get();

	void deliverMessage(double delay_time, 
						MovingEntity* sender,
						MovingEntity* receiver,
						MessageType msg_type,
						void* data);

	/** 
	  * Lately deliver message, called every frame
	  */
	void latelyDeliverMessage();

private:

	void deliverMessageNow(const Message& msg);

	std::set<Message> mMessagePool;      //!< Pool to store lately deliver message

};

#endif