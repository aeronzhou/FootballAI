#ifndef FOOTBALL_AI_MESSAGE_DISPATCHER
#define FOOTBALL_AI_MESSAGE_DISPATCHER
#pragma warning (disable:4786)

#include "Telegram.h"
#include <set>


class MovingEntity;

#define Dispatcher MessageDispatcher::Instance()

const double SEND_MSG_IMMEDIATELY = 0.0;
const int    NO_ADDITIONAL_INFO   = 0;
const int    SENDER_ID_IRRELEVANT = -1;


class MessageDispatcher
{
private:  
  
	std::set<Telegram> mPriorityQ;  //!< used as the container for the delayed messages

	/** 
      * utilized by DispatchMsg or DispatchDelayedMessages.
      */
    void Discharge(MovingEntity* pReceiver, const Telegram& msg);	

    MessageDispatcher(){}

	/** 
      * copy ctor and assignment should be private
	  */
    MessageDispatcher(const MessageDispatcher&);  
    MessageDispatcher& operator=(const MessageDispatcher&);

public:

	/** 
      *@return a singleton
	 */
	static MessageDispatcher* Instance();

	/** 
      *@param ExtraInfo in case need extral information
	  */
	void DispatchMsg(double			delay,
                     MovingEntity*  sender,
                     MovingEntity*  receiver,
                     QString		msg,
                     void*			ExtraInfo);

	/** 
      * send out any delayed messages.
	  */
	void DispatchDelayedMessages();
};


#endif