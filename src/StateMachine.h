#ifndef FOOTBALL_AI_STATEMACHINE
#define FOOTBALL_AI_STATEMACHINE


#include "State.h"
#include "Message.h"

#include <cassert>
#include <string>



template <class EntityType>
class StateMachine
{

private:

	EntityType*          mAgent;			    //!< A pointer to the agent that owns this instance

	State<EntityType>*   mCurrentState;         //!< Current State

	State<EntityType>*   mPreviousState;	    //!< a record of the last state the agent was in
	
	State<EntityType>*   mGlobalState;		    //!< this is called every time the FSM is updated
	

public:

	StateMachine(EntityType* agent)
		:
		mAgent(agent),
		mCurrentState(nullptr),
		mPreviousState(nullptr),
		mGlobalState(nullptr) {}

	virtual ~StateMachine() {}

	// getter
	State<EntityType>* getCurrentState() const{ return mCurrentState;}
	State<EntityType>* getGlobalState() const{ return mGlobalState;}
	State<EntityType>* getPreviousState() const{ return mPreviousState;}

	// setter
	void setCurrentState(State<EntityType>* s) { mCurrentState = s; }
	void setGlobalState(State<EntityType>* s) { mGlobalState = s; }
	void setPreviousState(State<EntityType>* s) { mPreviousState = s;}

	/** 
	  * call this to update the FSM
	  */
	void onUpdate() const
	{
		if (mGlobalState)   
			mGlobalState->execute(mAgent);

		if (mCurrentState) 
			mCurrentState->execute(mAgent);
	}


	bool handleMessage(const Message& msg) const
	{
		if (mCurrentState && mCurrentState->onMessage(mAgent, msg))
		{
			return true;
		}

		if (mGlobalState && mGlobalState->onMessage(mAgent, msg))
		{
			return true;
		}

		return false;
	}

	/** 
	  * change to a new state
	  */
	void changeState(State<EntityType>* new_state)
	{
		//assert(pNewState && "<StateMachine::ChangeState>:trying to assign null state to current");
		mPreviousState = mCurrentState;
		mCurrentState->exit(mAgent);
		mCurrentState = new_state;
		mCurrentState->enter(mAgent);
	}


	/** 
	  * change state back to the previous state
	  */
	void revertToPreviousState()
	{
		changeState(mPreviousState);
	}


	/** 
	  * returns true if the current state's type is equal to the type of the
	  * class passed as a parameter.
	  */
	bool isInState(const State<EntityType>& state) const
	{
		if (typeid(*mCurrentState) == typeid(state)) 
			return true;

		return false;
	}

	/** 
	  * Show the name of the current state
	  */
	QString getNameOfCurrentState() const
	{
		std::string s(typeid(*mCurrentState).name());
		// Class class_name...
		if (s.size() > 5)
		{
			s.erase(0, 6);
		}
		return dt::Utils::toString(s);
	}
};

#endif


