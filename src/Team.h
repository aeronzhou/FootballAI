#ifndef FOOTBALL_AI_TEAM
#define FOOTBALL_AI_TEAM

#include <Scene/Node.hpp>

#include <vector>

class Ball;
class Pitch;
class Player;

class Team : public dt::Node
{
public:

	enum TeamColor
	{
		RED,
		BLUE
	};

	Team(Ball* ball, Pitch* pitch, TeamColor color);

	void onInitialize();

	void onUpdate(double time_diff);

	/** 
	  * Genrate players 
	  */
	void createPlayers();

	/** 
	  * Set the pointer of mPlayerClosestToBall
	  */
	void calculatePlayerClosestToBall();

public:
	// Get and set
	TeamColor getTeamColor() const { return mColor; }

	Pitch* getPitch() const { return mPitch; }

protected:

	Ball* mBall;
	Pitch* mPitch;
	TeamColor mColor;
	Team* mOpponent;
	std::vector<Player*> mPlayers;

	Player* mControllingPlayer;         
	Player* mSupportingPlayer;
	Player* mReceivingPlayer;
	Player* mPlayerClosestToBall;

};

#endif