#ifndef FOOTBALL_AI_FIELD_PLAYER
#define FOOTBALL_AI_FIELD_PLAYER

#include "Player.h"
#include "CoolingTimeComponent.h"

class FieldPlayer : public Player
{
public:

	FieldPlayer(const QString name,
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
	  * @return True if this player is ready to kick the ball
	  */
	bool isReadyForNextKick();

	void handleMessage(/* const Telegarm& msg */);

	//StateMachine<FieldPlayer>* getFSM() const;

protected:
	
	std::shared_ptr<CoolingTimeComponent> mTimer;   //!< Cooling time component

	//StateMachine<FieldPlayer> mStateMachine;       //!< State Machine

};

#endif