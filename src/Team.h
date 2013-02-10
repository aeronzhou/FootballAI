#ifndef FOOTBALL_AI_TEAM
#define FOOTBALL_AI_TEAM

#include <Scene/Node.hpp>

class Ball;
class Pitch;

class Team
{
public:

	enum TeamColor
	{
		RED,
		BLUE
	};

	Team(Ball* ball,
		 Pitch* pitch,
		 TeamColor color);

protected:

	Ball* mBall;
	Pitch* mPitch;
	TeamColor mColor;
};

#endif