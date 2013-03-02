#include "FieldPlayer.h"
#include "SteeringBehaviors.h"

FieldPlayer::FieldPlayer(const QString name, float bounding_radius, float max_speed, 
	float max_force, float mass, float turn_rate, QString mesh_handle, QString material_handle,  Team* team, 
	int home_region, PlayerRole role)
	: Player(name, bounding_radius, max_speed, max_force, mass, turn_rate, mesh_handle, material_handle, team, home_region, role) {}

void FieldPlayer::onInitialize()
{
	Player::onInitialize();

	// Set up state machine 
	// and initialize state

	mSteering->separationOn();

	mTimer = addComponent(new CoolingTimeComponent(0.5));
}

void FieldPlayer::onDeinitialize()
{
	Player::onDeinitialize();
}

void FieldPlayer::onUpdate(double time_diff)
{
	this->mIsUpdatingAfterChange = (time_diff == 0);

	//Update here

	Player::onUpdate(time_diff);
}

void FieldPlayer::handleMessage(/* const Telegarm& msg */)
{

}

//StateMachine<FieldPlayer>* FieldPlayer::getFSM() const 
//{
//	return mStateMachine;
//}

bool FieldPlayer::isReadyForNextKick() 
{
	return mTimer->ready();
}