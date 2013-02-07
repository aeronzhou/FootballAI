#ifndef FOOTBALL_AI_PLAYER
#define FOOTBALL_AI_PLAYER

#include "MovingEntity.h"

class Team;

class Player : public MovingEntity
{
public:

	enum PlayerRole
	{
		GOAL_KEEPER,
		ATTACKER,
		DEFENDER
	};

	Player();


	/** 
	  * @returns If the current player is unsafe to keep the ball
	  */
	bool isThreatened() const;

	/** 
	  * Trace the ball
	  */
	void trackBall();

protected:

	PlayerRole mPlayerRole; //!< The player's role in this team

	Team* mTeam;            //!< The team this player belongs to

	int mHomeRegion;        //!< Indicate which home region this player assigned to

	int mDefaultRegion;     //!< The default region player is standing on

	float mDistSqToBall;    //!< Distance square from the ball

};

#endif