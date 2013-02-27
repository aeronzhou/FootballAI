#include "MessageDispatcher.h"
#include "MovingEntity.h"
#include <time.h>

using std::set;

//uncomment below to send message info to the debug window
//#define SHOW_MESSAGING_INFO

/** 
    * this class is a singleton
	*/
MessageDispatcher* MessageDispatcher::Instance()
{
  static MessageDispatcher instance; 
  
  return &instance;
}

/** 
    * see description in header
	*/
void MessageDispatcher::Discharge(MovingEntity* pReceiver, const Telegram& telegram)
{
  if (!pReceiver->HandleMessage(telegram))
  {
    //telegram could not be handled
    #ifdef SHOW_MESSAGING_INFO
    debug_con << "Message not handled" << "";
    #endif
  }
}

/** 
    * given a message, a receiver, a sender and any time delay, this function
	* routes the message to the correct agent (if no delay) or stores
	* in the message queue to be dispatched at the correct time
	*/
void MessageDispatcher::DispatchMsg(double       delay,
                                    int          sender,
                                    int          receiver,
                                    int          msg,
                                    void*        AdditionalInfo = NULL)
{

  //get a pointer to the receiver
  MovingEntity* pReceiver = 0/*= EntityMgr->GetEntityFromID(receiver)*/;

  //make sure the receiver is valid
  if (pReceiver == NULL)
  {
    #ifdef SHOW_MESSAGING_INFO
    debug_con << "\nWarning! No Receiver with ID of " << receiver << " found" << "";
    #endif

    return;
  }
  
  //create the telegram
  Telegram telegram(0, sender, receiver, msg, AdditionalInfo);
  
  //if there is no delay, route telegram immediately                       
  if (delay <= 0.0)                                                        
  {
    #ifdef SHOW_MESSAGING_INFO
    debug_con << "\nTelegram dispatched at time: " << TickCounter->GetCurrentFrame()
         << " by " << sender << " for " << receiver 
         << ". Msg is " << msg << "";
    #endif

    //send the telegram to the recipient
    Discharge(pReceiver, telegram);
  }

  //else calculate the time when the telegram should be dispatched
  else
  {
    double CurrentTime = clock() * 0.001; 

    telegram.mDispatchTime = CurrentTime + delay;

    //and put it in the queue
    mPriorityQ.insert(telegram);   

    #ifdef SHOW_MESSAGING_INFO
    debug_con << "\nDelayed telegram from " << sender << " recorded at time " 
            << TickCounter->GetCurrentFrame() << " for " << receiver
            << ". Msg is " << msg << "";
    #endif
  }
}

/** 
    * This function dispatches any telegrams with a timestamp that has
	* expired. Any dispatched telegrams are removed from the queue
	*/
void MessageDispatcher::DispatchDelayedMessages()
{ 
  //first get current time
  double CurrentTime = clock() * 0.001; 

  //now peek at the queue to see if any telegrams need dispatching.
  //remove all telegrams from the front of the queue that have gone
  //past their sell by date
  while( !mPriorityQ.empty() &&
	     (mPriorityQ.begin()->mDispatchTime < CurrentTime) && 
         (mPriorityQ.begin()->mDispatchTime > 0) )
  {
    //read the telegram from the front of the queue
    const Telegram& telegram = *mPriorityQ.begin();

    //find the recipient
    MovingEntity* pReceiver = 0/*= EntityMgr->GetEntityFromID(telegram.Receiver)*/;

    #ifdef SHOW_MESSAGING_INFO
    debug_con << "\nQueued telegram ready for dispatch: Sent to " 
         << pReceiver->ID() << ". Msg is "<< telegram.Msg << "";
    #endif

    //send the telegram to the recipient
    Discharge(pReceiver, telegram);

	//remove it from the queue
    mPriorityQ.erase(mPriorityQ.begin());
  }
}



