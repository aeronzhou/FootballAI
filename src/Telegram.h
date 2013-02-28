#ifndef FOOTBALL_AI_TELEGRAM
#define FOOTBALL_AI_TELEGRAM

#include <iostream>
#include <math.h>
#include <qstring.h>
#include "MovingEntity.h"

struct Telegram
{
	MovingEntity*	mSender;		//!< the entity that sent this telegram

	MovingEntity*   mReceiver;		//!< the entity that is to receive this telegram
	
	QString			mMsg;			//!< the message itself. These are all enumerated in the file
	
	double			mDispatchTime;  //!< dispatched immediately or delayed for a specified amount
	
	void*			mExtraInfo;		//!< any additional information that may accompany the message
	

	Telegram():mDispatchTime(-1),
			   mSender(NULL),
	 	       mReceiver(NULL)
	{}


	Telegram(double time,
		MovingEntity* sender,
		MovingEntity* receiver,
		QString    msg,
		void*  info = NULL): mDispatchTime(time),
		mSender(sender),
		mReceiver(receiver),
		mMsg(msg),
		mExtraInfo(info)
	{}

};


/** 
  * these telegrams will be stored in a priority queue. Therefore the >
  * operator needs to be overloaded so that the PQ can sort the telegrams
  * by time priority. Note how the times must be smaller than
  * SmallestDelay apart before two Telegrams are considered unique.
  */
const double SMALLESTDELAY = 0.25;


inline bool operator==(const Telegram& t1, const Telegram& t2)
{
	return ( fabs(t1.mDispatchTime-t2.mDispatchTime) < SMALLESTDELAY) &&
		(t1.mSender == t2.mSender)        &&
		(t1.mReceiver == t2.mReceiver)    &&
		(t1.mMsg == t2.mMsg);
}

inline bool operator<(const Telegram& t1, const Telegram& t2)
{
	if (t1 == t2)
	{
		return false;
	}

	else
	{
		return  (t1.mDispatchTime < t2.mDispatchTime);
	}
}

inline std::ostream& operator<<(std::ostream& os, const Telegram& t)
{
	os<< "time: " << t.mDispatchTime << "  Sender: " << t.mSender->getFullName().toStdString()
		<< "   Receiver: " << t.mReceiver->getFullName().toStdString() 
		<< "   Msg: " << t.mMsg.toStdString();

	return os;
}

/** 
  * handy helper function for dereferencing the ExtraInfo field of the Telegram 
  * to the required type.
  */
template <class T>
inline T DereferenceToType(void* p)
{
	return *(T*)(p);
}


#endif