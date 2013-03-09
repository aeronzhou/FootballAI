#ifndef FOOTBALL_AI_TELEGRAM
#define FOOTBALL_AI_TELEGRAM

#include "MovingEntity.h"

#include <QString>

#include <iostream>

struct Message
{
	double			deliver_time;   //!< deliver immediately or delayed for a specified amount
	MovingEntity*	sender;		    //!< the entity that sent this message
	MovingEntity*   receiver;		//!< the entity that is to receive this message
	QString			contents;		//!< the message contents
	void*			info;		    //!< any additional information that may accompany the message
	

	Message();

	Message(double time, 
			MovingEntity* sender, 
			MovingEntity* receiver, 
			const QString& contents, 
			void* info = NULL);

	friend bool operator==(const Message& p1, const Message& p2);

	friend bool operator<(const Message& p1, const Message& p2);

	//friend std::ostream& operator<<(std::ostream& os, const Message& other);

};



#endif