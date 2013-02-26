#ifndef FOOTBALL_AI_PLAYER
#define FOOTBALL_AI_PLAYER

#include "MovingEntity.h"

class Team;
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

	Player(QString name,
		float bounding_radius,
		float max_speed,
		Ogre::Vector3 heading,
		float max_force,
		float mass,
		float turn_rate,
		QString mesh_handle, 
		QString material_handle, 
		Team* team);

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

	Ogre::Vector3 getHeading() const;
	void setHeading(Ogre::Vector3 heading);


protected:

	Ogre::Vector3 mHeading;          //!< The direction this player moving towards

	PlayerRole mPlayerRole;          //!< The player's role in this team

	Team* mTeam;                     //!< The team this player belongs to
	int mHomeRegion;                 //!< Indicate which home region this player assigned to
	int mDefaultRegion;              //!< The default region player is standing on
	float mDistSqToBall;             //!< Distance square from the ball

	SteeringBehaviors* mSteering;    //!< 

};

#endif