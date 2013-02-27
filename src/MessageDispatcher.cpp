#include "MessageDispatcher.h"
#include "MovingEntity.h"
#include <time.h>

using std::set;

//uncomment below to send message info to the debug window
//#define SHOW_MESSAGING_INFO


MessageDispatcher* MessageDispatcher::Instance()
{
	static MessageDispatcher instance; 
  
	return &instance;
}

void MessageDispatcher::Discharge(MovingEntity* pReceiver, const Telegram& telegram)
{
	if (!pReceiver->HandleMessage(telegram))
	{
		#ifdef SHOW_MESSAGING_INFO
		debug_con << "Message not handled" << "";
		#endif
	}
}

void MessageDispatcher::DispatchMsg(double       delay,
                                    int          sender,
                                    int          receiver,
                                    int          msg,
                                    void*        AdditionalInfo = NULL)
{

	MovingEntity* pReceiver = 0/*= EntityMgr->GetEntityFromID(receiver)*/;

	if (pReceiver == NULL)
	{
		#ifdef SHOW_MESSAGING_INFO
		debug_con << "\nWarning! No Receiver with ID of " << receiver << " found" << "";
		#endif

		return;
	}
  
	Telegram telegram(0, sender, receiver, msg, AdditionalInfo);
  
	if (delay <= 0.0)                                                        
	{
		#ifdef SHOW_MESSAGING_INFO
		debug_con << "\nTelegram dispatched at time: " << TickCounter->GetCurrentFrame()
			<< " by " << sender << " for " << receiver 
			<< ". Msg is " << msg << "";
		#endif

		Discharge(pReceiver, telegram);
	}

	else
	{
		double CurrentTime = clock() * 0.001; 

		telegram.mDispatchTime = CurrentTime + delay;

		mPriorityQ.insert(telegram);   

		#ifdef SHOW_MESSAGING_INFO
		debug_con << "\nDelayed telegram from " << sender << " recorded at time " 
				<< TickCounter->GetCurrentFrame() << " for " << receiver
				<< ". Msg is " << msg << "";
		#endif
	}
}


void MessageDispatcher::DispatchDelayedMessages()
{ 
	double CurrentTime = clock() * 0.001; 

	while( !mPriorityQ.empty() &&
			(mPriorityQ.begin()->mDispatchTime < CurrentTime) && 
			(mPriorityQ.begin()->mDispatchTime > 0) )
	{
    //read the telegram from the front of the queue
    const Telegram& telegram = *mPriorityQ.begin();

    MovingEntity* pReceiver = 0/*= EntityMgr->GetEntityFromID(telegram.Receiver)*/;

    #ifdef SHOW_MESSAGING_INFO
    debug_con << "\nQueued telegram ready for dispatch: Sent to " 
         << pReceiver->ID() << ". Msg is "<< telegram.Msg << "";
    #endif

    Discharge(pReceiver, telegram);

	mPriorityQ.erase(mPriorityQ.begin());
	}
}



