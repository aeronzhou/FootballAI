#ifndef FOOTBALL_AI_GOAL_KEEPER
#define FOOTBALL_AI_GOAL_KEEPER

#include "Player.h"

class GoalKeeper : public Player
{
public:
	
	GoalKeeper(const QString name,
		float bounding_radius,
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

	//StateMachine<GoalKeeper>* getFSM() const;

	/** 
	  * @returns True if ball is close enough for goal keeper to consider to intercept
	  */
	bool ballWithRangeForIntercept() const;

	/** 
      * @returns True if the goal keeper is too far away from goal mouth
	  */
	bool tooFarFromGoalMouth() const;


	

protected:

	//StateMachine<GoalKeeper>* mStateMachine;


};
#endif