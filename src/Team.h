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
	TeamColor getTeamColor() const;

	Pitch* getPitch() const;

	Team* getOpponent() const;
	void setOpponent(Team* opponent);

private:

	//StateMachine<Team>* mStateMachine;   //!< StateMachine

	Ball* mBall;
	Pitch* mPitch;
	TeamColor mColor;                 //!< Team color, RED or BLUE
	Team* mOpponent;                  //!< The opponent team of this
	std::vector<Player*> mPlayers;    //!< Pointers of players this team hold

	Player* mControllingPlayer;         
	Player* mSupportingPlayer;
	Player* mReceivingPlayer;
	Player* mPlayerClosestToBall;

};

#endif