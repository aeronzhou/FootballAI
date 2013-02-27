#ifndef FOOTBALL_AI_STATEMACHINE_H
#define FOOTBALL_AI_STATEMACHINE_H


#include <cassert>
#include <string>
#include "State.h"
#include "Telegram.h"


template <class entity_type>
class StateMachine
{

private:    

	entity_type*          mpOwner;				//!< a pointer to the agent that owns this instance

	State<entity_type>*   mpCurrentState;

	State<entity_type>*   mpPreviousState;		//!< a record of the last state the agent was in
	
	State<entity_type>*   mpGlobalState;		//!< this is called every time the FSM is updated
	

public:

	StateMachine(entity_type* owner):mpOwner(owner),
		mpCurrentState(NULL),
		mpPreviousState(NULL),
		mpGlobalState(NULL)
	{}

	virtual ~StateMachine(){}

	/** 
	  * use these methods to initialize the FSM
	  */
	void setCurrentState(State<entity_type>* s){mpCurrentState = s;}
	void setGlobalState(State<entity_type>* s) {mpGlobalState = s;}
	void setPreviousState(State<entity_type>* s){mpPreviousState = s;}

	/** 
	  * call this to update the FSM
	  */
	void  update()const
	{
		//if a global state exists, call its execute method, else do nothing
		if(mpGlobalState)   mpGlobalState->Execute(mpOwner);

		//same for the current state
		if (mpCurrentState) mpCurrentState->Execute(mpOwner);
	}

	bool  handleMessage(const Telegram& msg)const
	{
		//first see if the current state is valid and that it can handle
		//the message
		if (mpCurrentState && mpCurrentState->OnMessage(mpOwner, msg))
		{
			return true;
		}

		//if not, and if a global state has been implemented, send 
		//the message to the global state
		if (mpGlobalState && mpGlobalState->OnMessage(mpOwner, msg))
		{
			return true;
		}

		return false;
	}

	/** 
	  * change to a new state
	  */
	void  changeState(State<entity_type>* pNewState)
	{
		assert(pNewState && "<StateMachine::ChangeState>:trying to assign null state to current");

		//keep a record of the previous state
		m_pPreviousState = m_pCurrentState;

		//call the exit method of the existing state
		m_pCurrentState->Exit(m_pOwner);

		//change state to the new state
		m_pCurrentState = pNewState;

		//call the entry method of the new state
		m_pCurrentState->Enter(m_pOwner);
	}

	/** 
	  * change state back to the previous state
	  */
	void  revertToPreviousState()
	{
		ChangeState(m_pPreviousState);
	}

	/** 
	  * returns true if the current state's type is equal to the type of the
	  * class passed as a parameter.
	  */
	bool  isInState(const State<entity_type>& st)const
	{
		if (typeid(*m_pCurrentState) == typeid(st)) return true;
		return false;
	}

	State<entity_type>*  currentState()  const{return m_pCurrentState;}
	State<entity_type>*  globalState()   const{return m_pGlobalState;}
	State<entity_type>*  previousState() const{return m_pPreviousState;}

	/** 
	  * only ever used during debugging to grab the name of the current state
	  */
	std::string getNameOfCurrentState()const
	{
		std::string s(typeid(*m_pCurrentState).name());

		//remove the 'class ' part from the front of the string
		if (s.size() > 5)
		{
			s.erase(0, 6);
		}

		return s;
	}
};


#endif


