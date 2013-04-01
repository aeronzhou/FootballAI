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
class SupportSpotCalculator;

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

	float getClosestDistToBall() const;

	std::vector<Player*>& getPlayers();

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
	  * Return if the team is controlling the ball
	  * @returns If the team is controlling the ball
	  */
	bool isInControl() const;

	Player* getControllingPlayer() const;
	void setControllingPlayer(Player* player);

	Player* getSupportingPlayer() const;
	void setSupportingPlayer(Player* player);

	Player* getReceivingPlayer() const;
	void setReceivingPlayer(Player* player);

	/** 
	  * Find a possible pass, return true if the pass exists
	  * @param passer Player who is passing the ball
	  * @param receiver Possible receiver
	  * @param proper_target Proper target
	  * @param max_force Max passing force
	  * @returns If there is a chance to pass
	  */
	bool canPass(Player* passer, Player*& receiver, Ogre::Vector3& proper_target, float passing_force);

	/** 
	  * Return true if the player is able to shoot
	  * @param player The shooter
	  * @param proper_target Proper target
	  * @param max_force Max shooting force
	  * @returns If the player can shoot now
	  */
	bool canShoot(Player* player, Ogre::Vector3& proper_target, float shooting_force);

	/**  
	  * Test if the ball can go through all opponents from a place to another
	  * @param from From place
	  * @param target Target place
	  * @param force Force to kick the ball
	  * @returns True if the ball can go througth all opponents
	  */
	bool isSafeGoingThroughAllOpponents(const Ogre::Vector3& from, const Ogre::Vector3& target, float force);

	bool isSafeGoingThroughOpponent(const Ogre::Vector3& from, const Ogre::Vector3& target, float force, Player* opponent);

	/** 
	  *	Player ask for pass, but with a possibility to execute
	  * @param player Player who is asking for pass
	  * @param delay_time Time to delay the pass
	  */
	void requestPass(Player* player, double delay_time = 0);

	void updateTargetsOfWaitingPlayers();

	/** 
	  * Return the best support spot
	  * @returns the best support spot
	  */
	Ogre::Vector3 getBestSupportSpot() const;

private:

	/** 
	  * Genrate players 
	  */
	void _createPlayers();

	/** 
	  * Find player closest to ball so as to chase the ball
	  */
	void _findPlayerClosestToBall();




	/** 
	  * Get the score of current position, 
	  * If it gets more scores, it means to be more beneficial for attacking(or defending)
	  * @param position Current position
	  * @returns Scores
	  */
	float _getScoreOfPosition(const Ogre::Vector3& position);

	/** 
	  * Get the best receiving spot
	  * @param receiver Receiver
	  * @param pass_force Passing force
	  * @param target Proper target
	  * @returns Score of the best spot
	  */
	float _getBestSpotOfReceiving(Player* receiver, float pass_force, Ogre::Vector3& target);


private:

	StateMachine<Team>* mStateMachine;                //!< StateMachine

	Ball* mBall;
	Pitch* mPitch;
	Goal* mGoal;
	TeamColor mColor;                                 //!< Team color, RED or BLUE
	Team* mOpponent;                                  //!< The opponent team of this
	std::vector<Player*> mPlayers;                    //!< Pointers of players this team hold

	bool mIsControllingBall;                          //!< If the team is controlling the ball

	Player* mControllingPlayer;                       //!< Pointer to the player which is controlling the ball 
	Player* mPlayerClosestToBall;                     //!< Pointer to the player which is closest to the ball
	Player* mSupportingPlayer;                        //!< Pointer to supporting player
	Player* mReceivingPlayer;                         //!< Pointer to receiving player
	SupportSpotCalculator* mSupportSpotCalculator;    //!< Calculator of best support spot

};

#endif