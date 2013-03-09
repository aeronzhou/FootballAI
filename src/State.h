#ifndef FOOTBALL_AI_STATE
#define FOOTBALL_AI_STATE

struct Message;

template <class EntityType>
class State
{
public:

	virtual ~State() {}

	/** 
	  * this will execute when the state is entered
	  */
	virtual void enter(EntityType*) = 0;

	/** 
	  * this is the states normal update function
	  */
	virtual void execute(EntityType*) = 0;

	/** 
	  * this will execute when the state is exited. 
	  */
	virtual void exit(EntityType*) = 0;

	/** 
	  * this executes if the agent receives a message from the message dispatcher
	  */
	virtual bool onMessage(EntityType*, const Message&) = 0;
};

#endif