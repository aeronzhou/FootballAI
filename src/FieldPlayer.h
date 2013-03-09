#ifndef FOOTBALL_AI_FIELD_PLAYER
#define FOOTBALL_AI_FIELD_PLAYER

#include "Player.h"
#include "CoolingTimeComponent.h"
#include "StateMachine.h"

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

	void onDeinitialize();

	void onUpdate(double time_diff);

	/** 
	  * @return True if this player is ready to kick the ball
	  */
	bool isReadyToKick() const;

	bool handleMessage(const Message& msg) const;

	StateMachine<FieldPlayer>* getStateMachine() const;

protected:
	
	std::shared_ptr<CoolingTimeComponent> mShootCoolTime;   //!< Cooling time component

	StateMachine<FieldPlayer>* mStateMachine;               //!< State Machine

};

#endif