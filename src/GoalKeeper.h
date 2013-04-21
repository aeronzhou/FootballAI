#ifndef FOOTBALL_AI_GOAL_KEEPER
#define FOOTBALL_AI_GOAL_KEEPER

#include "Player.h"
#include "StateMachine.h"
#include "CoolingTimeComponent.h"

class GoalKeeper : public Player
{
public:
	
	GoalKeeper(const QString name,
		float control_range,
		float max_speed,
		float max_force,
		float mass,
		float turn_rate,
		QString mesh_handle, 
		QString material_handle, 
		Team* team, 
		int home_region);

	void onInitialize();

	void onDeinitialize();

	void onUpdate(double time_diff);

	StateMachine<GoalKeeper>* getStateMachine() const;

	float getDistToGoal() const;

	/** 
	  * @returns True if ball is close enough for goal keeper to consider to intercept
	  */
	bool isBallWithInterceptRange() const;

	/** 
      * @returns True if the goal keeper is too far away from goal mouth
	  */
	bool isTooFarFromGoalMouth() const;

	/** 
	  * To determined the target when the keeper is tending goal
	  * @returns Target when the keeper is tending goal
	  */
	Ogre::Vector3 getRearInterposeTarget() const;


	

protected:

	StateMachine<GoalKeeper>* mStateMachine;

	std::shared_ptr<CoolingTimeComponent> mKickCoolingTime;   //!< Cooling time component


};
#endif