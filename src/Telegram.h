#ifndef FOOTBALL_AI_TELEGRAM_H
#define FOOTBALL_AI_TELEGRAM_H

#include <iostream>
#include <math.h>


struct Telegram
{
	int          mSender;		//!< the entity that sent this telegram

	int          mReceiver;		//!< the entity that is to receive this telegram
	
	int          mMsg;			//!< the message itself. These are all enumerated in the file
	
	double       mDispatchTime;	//!< messages can be dispatched immediately or delayed for a specified amount
								//!< of time. If a delay is necessary this field is stamped with the time 
								//!< the message should be dispatched.
	
	void*        mExtraInfo;		//!< any additional information that may accompany the message
	

	Telegram():mDispatchTime(-1),
		mSender(-1),
		mReceiver(-1),
		mMsg(-1)
	{}


	Telegram(double time,
		int    sender,
		int    receiver,
		int    msg,
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
	os << "time: " << t.mDispatchTime << "  Sender: " << t.mSender
		<< "   Receiver: " << t.mReceiver << "   Msg: " << t.mMsg;

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