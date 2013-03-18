#ifndef FOOTBALL_AI_FIELD_PLAYER_CHASING_BALL
#define FOOTBALL_AI_FIELD_PLAYER_CHASING_BALL

#include "State.h"

class FieldPlayer;

/** 
  * Chasing ball state of FieldPlayer
  */
class ChasingBall: public State<FieldPlayer>
{
public:
	static ChasingBall* get();

	void enter(FieldPlayer*);

	void execute(FieldPlayer*);

	void exit(FieldPlayer*);

	bool onMessage(FieldPlayer*, const Message&);
};


#endif