#ifndef FOOTBALL_AI_TEAM
#define FOOTBALL_AI_TEAM

#include "Pitch.h"
#include "StateMachine.h"

#include <Scene/Node.hpp>

#include <vector>

class Ball;
class Pitch;
class Player;
class Goal;

class Team : public dt::Node
{
public:

	enum TeamColor
	{
		RED,
		BLUE
	};

	Team(Ball* ball, Pitch* pitch, TeamColor color, Goal* goal);

	void onInitialize();

	void onDeinitialize();

	void onUpdate(double time_diff);


public:
	// Get and set
	TeamColor getTeamColor() const;
	Pitch* getPitch() const;
	Ball* getBall() const;
	Goal* getGoal() const;

	Team* getOpponent() const;
	void setOpponent(Team* opponent);

	Player* getPlayerClosestToBall() const;

	StateMachine<Team>* getStateMachine() const;

	/** 
	  * Call when the game start or scored, all players back to origin region
	  */
	void playersBackForKickOff();

	/** 
	  * Return true if all players are in assigned regions
	  * @returns True if all players are in assigned regions
	  */
	bool allPlayersInAssignedRegions() const;

	/** 
	  * Set players' current assigned regions
	  * @param vec_pos Vector to represent the assigned regions
	  */
	void setAssignedRegion(const std::vector<int>& vec_pos);

	/** 
	  * Send players to assigned region and wait for next command
	  */
	void sendPlayersToAssignedRegion();

	/** 
	  * Find player closest to ball so as to chase the ball
	  */
	void findPlayerClosestToBall();

	/** 
	  * Return if the team is controlling the ball
	  * @returns If the team is controlling the ball
	  */
	bool isControllingBall() const;

	Player* getControllingPlayer() const;
	void setControllingPlayer(Player* player);

private:

	/** 
	  * Genrate players 
	  */
	void createPlayers();

private:

	StateMachine<Team>* mStateMachine;     //!< StateMachine

	Ball* mBall;
	Pitch* mPitch;
	Goal* mGoal;
	TeamColor mColor;                      //!< Team color, RED or BLUE
	Team* mOpponent;                       //!< The opponent team of this
	std::vector<Player*> mPlayers;         //!< Pointers of players this team hold

	bool mIsControllingBall;               //!< If the team is controlling the ball

	Player* mControllingPlayer;            //!< Pointer to the player which is controlling the ball 
	Player* mPlayerClosestToBall;          //!< Pointer to the player which is closest to the ball

};

#endif