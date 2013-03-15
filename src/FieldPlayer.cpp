#include "FieldPlayer.h"
#include "MotionAider.h"
#include "Team.h"
#include "FieldPlayerState.h"
#include "Constant.h"

#include <OgreManualObject.h>

FieldPlayer::FieldPlayer(const QString name, float bounding_radius, float max_speed, 
	float max_force, float mass, float turn_rate, QString mesh_handle, QString material_handle,  Team* team, 
	int assigned_region, PlayerRole role)
	: Player(name, bounding_radius, max_speed, max_force, mass, turn_rate, mesh_handle, material_handle, team, assigned_region, role) {}

void FieldPlayer::onInitialize()
{
	Player::onInitialize();

	// Set up state machine 
	// and initialize state
	mStateMachine = new StateMachine<FieldPlayer>(this);
	mStateMachine->setCurrentState(Waiting::get());
	mStateMachine->setGlobalState(FieldPlayerGlobalState::get());

	mMotionAider->separationOn();

	mShootCoolTime = addComponent(new CoolingTimeComponent(0.5));

	setVelocity(Ogre::Vector3(1.f, 0.f, 0.f));
}

void FieldPlayer::onDeinitialize()
{
	delete mStateMachine;

	Player::onDeinitialize();
}

//float sum = 1.f;

void FieldPlayer::onUpdate(double time_diff)
{
	this->mIsUpdatingAfterChange = (time_diff == 0);

	mStateMachine->onUpdate();

	// Update here
	getMotionAider()->calculate();

	Ogre::Vector3& force = getMotionAider()->getDrivingForce();

	QString qsforce = "x=" + dt::Utils::toString(force.x) + ",z=" + dt::Utils::toString(force.z);

	Ogre::Vector3 velocity = getVelocity();

	velocity = velocity + force / getMass() * TIME_DIFF;

	if (velocity.length() > getMaxSpeed())
	{
		velocity = velocity.normalisedCopy() * getMaxSpeed();
	}

	setVelocity(velocity);
	setDebugText("len=" + dt::Utils::toString(velocity ));

	Player::onUpdate(time_diff);
}

StateMachine<FieldPlayer>* FieldPlayer::getStateMachine() const 
{
	return mStateMachine;
}

bool FieldPlayer::isReadyToKick() const
{
	return mShootCoolTime->ready();
}

bool FieldPlayer::handleMessage(const Message& msg) const 
{
	return mStateMachine->handleMessage(msg);	
}