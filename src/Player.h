#ifndef FOOTBALL_AI_PLAYER
#define FOOTBALL_AI_PLAYER

#include "MovingEntity.h"
#include "SteeringBehaviors.h"
#include "Region.h"

#include <Graphics/TextComponent.hpp>

class Team;
class Ball;
class SteeringBehaviors;
class Pitch;

class Player : public MovingEntity
{
	Q_OBJECT

public:

	enum PlayerRole
	{
		GOAL_KEEPER,  
		ATTACKER,
		DEFENDER,
		BACK
	};

	Player(const QString name,
		float control_range,
		float max_speed,
		float max_force,
		float mass,
		float turn_rate,
		QString mesh_handle, 
		QString material_handle, 
		Team* team, 
		int assigned_region,
		PlayerRole role);

	void onInitialize();

	void onDeinitialize();

	void onUpdate(double time_diff);

	SteeringBehaviors* getSteering() const;
	Team* getTeam() const;
	Ball* getBall() const;
	Pitch* getPitch() const;
	PlayerRole getPlayerRole() const;

	Region* getAssignedRegion() const;
	void setAssignedRegion(int assigned_region);

	float getControlRange() const;

	void setDebugText(QString debug_text);

	bool isClosestTeamMemberToBall() const;

	bool isClosestPlayerOnPitchToBall() const;

	/** 
	  * Return true if this player is controlling the ball
	  * @returns True if this player is controlling the ball
	  */
	bool isControllingPlayer() const;

	/** 
	  * Return true if this player is being ahead of the controlling player
	  */
	bool isAheadOfController() const;

	/** 
	  * Return distance to ball 
	  * @returns Distance to ball 
	  */
	float getDistToBall() const;

	/** 
	  * Return a position with self's region
	  * @param random If true, return a random position
	  * @returns A position
	  */
	Ogre::Vector3 getPositionWithRegion(bool random = false);

	/** 
	  * Return true if this player is within target or near it
	  * @returns true if this player is within target or near it
	  */
	bool isAtTarget() const;

	Ogre::Vector3 getTarget() const;

	void setTarget(Ogre::Vector3 target);

	bool isWithinAssignedRegion() const;

	/** 
	  * Return if the player is in receiving range, so as to chase and control the ball
	  * @returns If the player is in receiving range
	  */
	bool isWithinReceivingRange() const;

	/** 
	  * Return if the player is in control range, so as to control the ball
	  * @return if the player is in control range
	  */
	bool isBallWithinControlRange() const;

	/** 
	  * Turn around to face towards the ball
	  */
	void turnAroundToBall();

	/** 
	  * Turn around to face to the target
	  * @target Target to face to
	  */
	void turnAroundToTarget(const Ogre::Vector3& target);

	/** 
	  * Return if the player is threatened by others, goto findReceiver if threatened
	  * @returns If the player is threatened by others
	  */
	bool isThreatened() const;

	/** 
	  * This function is to find the best support spot and 
	  * set the player closest to it as the supporter
	  */
	void findSupport();


protected:

	/** 
	  * Rotate to face a target with a turn rate
	  * @param target Target to face to
	  */
	void _rotateToFaceTarget(const Ogre::Vector3& target);


protected:

	float mControlRange;                             //!< Within this region, player can kick the ball
	float mReceivingRange;                           //!< Within this region, player can receive the ball
	Ogre::Radian mIsTurnningAroundAtTarget;          //!< Angle turnning around after the player arrive the target

	PlayerRole mPlayerRole;                          //!< The player's role in this team

	Team* mTeam;                                     //!< The team this player belongs to
	int mAssignedRegion;                             //!< Indicate which home region this player assigned to
	float mDistSqToBall;                             //!< Distance square from the ball
	float mDistSqAtTarget;                           //!< Distance square to be at target

	SteeringBehaviors* mSteeringBehaviors;           //!< Motion aider

	dt::TextComponent* mDebugText;                   //!< Text to show players' current state

};

#endif