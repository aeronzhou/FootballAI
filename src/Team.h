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

public:
	// Get and set
	TeamColor getTeamColor() const;

	Pitch* getPitch() const;

	Ball* getBall() const;

	Team* getOpponent() const;
	void setOpponent(Team* opponent);

	/** 
	  * Send all players to their home regions
	  */
	void returnAllPlayersToHome();

private:
	/** 
	  * Set the pointer of mPlayerClosestToBall
	  */
	void calculatePlayerClosestToBall();

	/** 
	  * Genrate players 
	  */
	void createPlayers();

private:

	//StateMachine<Team>* mStateMachine;   //!< StateMachine

	Ball* mBall;
	Pitch* mPitch;
	TeamColor mColor;                      //!< Team color, RED or BLUE
	Team* mOpponent;                       //!< The opponent team of this
	std::vector<Player*> mPlayers;         //!< Pointers of players this team hold

	Player* mControllingPlayer;            //!< Pointer to the player which is controlling the ball 
	Player* mSupportingPlayer;
	Player* mReceivingPlayer;              //!< Pointer to the player which is receiving the ball
	Player* mPlayerClosestToBall;

	float mDistSqToBallOfClosestPlayer;    //!< Square distance from the ball to the nearest player, update every frame

};

#endif