#ifndef TELEGRAM_H
#define TELEGRAM_H

#include <iostream>
#include <math.h>


struct Telegram
{
	int          Sender;		//!< the entity that sent this telegram

	int          Receiver;		//!< the entity that is to receive this telegram
	
	int          Msg;			//!< the message itself. These are all enumerated in the file
	
	double       DispatchTime;	//!< messages can be dispatched immediately or delayed for a specified amount
								//!< of time. If a delay is necessary this field is stamped with the time 
								//!< the message should be dispatched.
	
	void*        ExtraInfo;		//!< any additional information that may accompany the message
	

	Telegram():DispatchTime(-1),
		Sender(-1),
		Receiver(-1),
		Msg(-1)
	{}


	Telegram(double time,
		int    sender,
		int    receiver,
		int    msg,
		void*  info = NULL): DispatchTime(time),
		Sender(sender),
		Receiver(receiver),
		Msg(msg),
		ExtraInfo(info)
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
	return ( fabs(t1.DispatchTime-t2.DispatchTime) < SMALLESTDELAY) &&
		(t1.Sender == t2.Sender)        &&
		(t1.Receiver == t2.Receiver)    &&
		(t1.Msg == t2.Msg);
}

inline bool operator<(const Telegram& t1, const Telegram& t2)
{
	if (t1 == t2)
	{
		return false;
	}

	else
	{
		return  (t1.DispatchTime < t2.DispatchTime);
	}
}

inline std::ostream& operator<<(std::ostream& os, const Telegram& t)
{
	os << "time: " << t.DispatchTime << "  Sender: " << t.Sender
		<< "   Receiver: " << t.Receiver << "   Msg: " << t.Msg;

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