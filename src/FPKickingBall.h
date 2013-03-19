#ifndef FOOTBALL_AI_FIELD_PLAYER_KICKING_BALL
#define FOOTBALL_AI_FIELD_PLAYER_KICKING_BALL

#include "State.h"

class FieldPlayer;

/** 
  * Kicking Ball
  */
class KickingBall: public State<FieldPlayer>
{
public:
	static KickingBall* get();

	void enter(FieldPlayer*);

	void execute(FieldPlayer*);

	void exit(FieldPlayer*);

	bool onMessage(FieldPlayer*, const Message&);
};

#endif