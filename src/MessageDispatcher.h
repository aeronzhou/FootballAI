#ifndef FOOTBALL_AI_MESSAGE_DISPATCHER	
#define FOOTBALL_AI_MESSAGE_DISPATCHER

#include "Message.h"

#include <set>

/** 
  * A singleton class to dispatch message
  */ 
class MessageDispatcher
{
public:

	/** 
	  * Singleton
	  */
	static MessageDispatcher& get();

	void dispatchMessage(double delay_time, 
						MovingEntity* sender,
						MovingEntity* receiver,
						MessageType msg_type,
						void* data);

	/** 
	  * Lately deliver message, called every frame
	  */
	void latelyDispatchMessage();

private:

	void dispatchMessageNow(const Message& msg);

	std::set<Message> mMessagePool;      //!< Pool to store lately deliver message

};

#endif