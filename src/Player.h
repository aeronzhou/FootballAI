#ifndef FOOTBALL_AI_PLAYER
#define FOOTBALL_AI_PLAYER

#include "MovingEntity.h"
#include "IList.h"
#include "MotionAider.h"
#include "Region.h"

#include <Graphics/TextComponent.hpp>

class Team;
class Ball;
class MotionAider;
class Pitch;

class Player : public MovingEntity
{
	Q_OBJECT

public:

	enum PlayerRole
	{
		GOAL_KEEPER,  
		FORWARD,
		MIDFIELD,
		BACK
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
		int assigned_region,
		PlayerRole role);

	void onInitialize();

	void onDeinitialize();

	void onUpdate(double time_diff);


	MotionAider* getMotionAider() const;

	Team* getTeam() const;
	Ball* getBall() const;
	Pitch* getPitch() const;

	Region* getAssignedRegion() const;
	void setAssignedRegion(int assigned_region);

	void setDebugText(QString debug_text);

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
	bool atTarget() const;

	void setTarget(Ogre::Vector3 target);

	bool withinAssignedRegion() const;


protected:

	PlayerRole mPlayerRole;                          //!< The player's role in this team

	Team* mTeam;                                     //!< The team this player belongs to
	int mAssignedRegion;                             //!< Indicate which home region this player assigned to
	float mDistSqToBall;                             //!< Distance square from the ball
	float mDistSqAtTarget;                           //!< Distance square to be at target

	MotionAider* mMotionAider;                       //!< Motion aider
	bool mTag;                                       //!< Flag to indicate this player is chosen

	dt::TextComponent* mDebugText;                   //!< Text to show players' current state

};

#endif