#ifndef FOOTBALL_AI_PLAYER
#define FOOTBALL_AI_PLAYER

#include "MovingEntity.h"

class Team;
class Ball;
class SteeringBehaviors;

class Player : public MovingEntity
{
	Q_OBJECT

public:

	enum PlayerRole
	{
		GOAL_KEEPER,
		ATTACKER,
		DEFENDER
	};

	Player(const QString name,
		float bounding_radius,
		float max_speed,
		float max_force,
		float mass,
		float turn_rate,
		QString mesh_handle, 
		QString material_handle, 
		Team* team, 
		int home_region,
		PlayerRole role);

	void onInitialize();

	void onUpdate(double time_diff);


	/** 
	  * @returns If the current player is unsafe to keep the ball
	  */
	bool isThreatened() const;

	/** 
	  * Trace the ball
	  */
	void trackBall();

	SteeringBehaviors* getSteering() const;

	Team* getTeam() const;
	Ball* getBall() const;

	int getHomeRegion() const;
	void setHomeRegion(int home_region);


protected:

	PlayerRole mPlayerRole;                          //!< The player's role in this team

	Team* mTeam;                                     //!< The team this player belongs to
	int mHomeRegion;                                 //!< Indicate which home region this player assigned to
	int mDefaultRegion;                              //!< The default region player is standing on
	float mDistSqToBall;                             //!< Distance square from the ball

	std::shared_ptr<SteeringBehaviors> mSteering;    //!< 

};

#endif