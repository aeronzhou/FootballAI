#ifndef FOOTBALL_AI_MESSAGE
#define FOOTBALL_AI_MESSAGE

#include "MovingEntity.h"

#include <QString>

#include <iostream>

enum MessageType
{
	MSG_PASS
};

struct Message
{
	double			deliver_time;   //!< deliver immediately or delayed for a specified amount
	MovingEntity*	sender;		    //!< the entity that sent this message
	MovingEntity*   receiver;		//!< the entity that is to receive this message
	MessageType		msg_type;		//!< the message type 
	void*			data;		    //!< any additional data that may accompany the message
	

	Message();

	Message(double deliver_time, 
			MovingEntity* sender, 
			MovingEntity* receiver, 
			MessageType msg_type, 
			void* data = NULL);

	bool operator < (const Message& t) const;
};



#endif