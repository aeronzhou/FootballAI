#ifndef FOOTBALL_AI_FIELDPLAYERSTATES
#define FOOTBALL_AI_FIELDPLAYERSTATES

#include <string>
#include "State.h"
#include "Telegram.h"

class FieldPlayer;
class SoccerPitch;


/** 
  * GlobalPlayerState
  */
class GlobalPlayerState : public State<FieldPlayer>
{
private:

    GlobalPlayerState(){}

public:
	/** 
	* @return a singleton
	*/
	static GlobalPlayerState* Instance();

	void Enter(FieldPlayer* player){}

	void Execute(FieldPlayer* player);

	void Exit(FieldPlayer* player){}

	bool OnMessage(FieldPlayer*, const Telegram&);
};


/** 
  * ChaseBall state
  */
class ChaseBall : public State<FieldPlayer>
{
private:
  
  ChaseBall(){}

public:

	static ChaseBall* Instance();

	void Enter(FieldPlayer* player);

	void Execute(FieldPlayer* player);

	void Exit(FieldPlayer* player);

	bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};




/** 
  * Dribble state
  */
class Dribble : public State<FieldPlayer>
{
private:
  
  Dribble(){}

public:
	
	static Dribble* Instance();

	void Enter(FieldPlayer* player);

	void Execute(FieldPlayer* player);

	void Exit(FieldPlayer* player){}

	bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};



/** 
  * ReturnToHomeRegion state
  */
class ReturnToHomeRegion: public State<FieldPlayer>
{
private:
  
  ReturnToHomeRegion(){}

public:

	static ReturnToHomeRegion* Instance();

	void Enter(FieldPlayer* player);

	void Execute(FieldPlayer* player);

	void Exit(FieldPlayer* player);

	bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};



/** 
  * Wait state
  */
class Wait: public State<FieldPlayer>
{
private:
  
  Wait(){}

public:

	static Wait* Instance();

	void Enter(FieldPlayer* player);

	void Execute(FieldPlayer* player);

	void Exit(FieldPlayer* player);

	bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};




/** 
  * KickBall state
  */
class KickBall: public State<FieldPlayer>
{
private:
  
  KickBall(){}

public:

	static KickBall* Instance();

	void Enter(FieldPlayer* player);

	void Execute(FieldPlayer* player);

	void Exit(FieldPlayer* player){}

	bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};




/** 
  * ReceiveBall state
  */
class ReceiveBall: public State<FieldPlayer>
{
private:
  
  ReceiveBall(){}

public:

	static ReceiveBall* Instance();

	void Enter(FieldPlayer* player);

	void Execute(FieldPlayer* player);

	void Exit(FieldPlayer* player);

	bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};




/** 
  * SupportAttacker state
  */
class SupportAttacker: public State<FieldPlayer>
{
private:
  
  SupportAttacker(){}

public:

	static SupportAttacker* Instance();

	void Enter(FieldPlayer* player);

	void Execute(FieldPlayer* player);

	void Exit(FieldPlayer* player);

	bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};


#endif