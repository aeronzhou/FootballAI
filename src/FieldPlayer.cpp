#include "FieldPlayer.h"
#include "MotionAider.h"
#include "Team.h"
#include "FieldPlayerState.h"
#include "Utils.h"
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
}

void FieldPlayer::onDeinitialize()
{
	delete mStateMachine;

	Player::onDeinitialize();
}

void FieldPlayer::onUpdate(double time_diff)
{
	this->mIsUpdatingAfterChange = (time_diff == 0);

	mStateMachine->onUpdate();

	// Update here
	mMotionAider->calculateDrivingForce();

	// Apply a small rotation 
	Ogre::Vector3 current_velocity = getVelocity();
	Ogre::Quaternion rotation = getRotation();
	Ogre::Vector3 current_heading = GetHeadingThroughRotation(rotation);
	float velocity_magnitude = current_velocity.length();
	Ogre::Vector3 driving_force = mMotionAider->getDrivingForce();

	if (driving_force.length() > EPS)
	{
		Ogre::Radian angle = current_heading.getRotationTo(driving_force).getYaw();

		if (angle > Ogre::Radian(mTurnRate))
			angle = Ogre::Radian(mTurnRate);

		if (angle < Ogre::Radian(-mTurnRate))
			angle = Ogre::Radian(-mTurnRate);

		float accumulate_force = current_heading.dotProduct(driving_force);

		// If at the same line
		if (fabs(angle.valueRadians()) < EPS && accumulate_force < 0)
			angle = mTurnRate;

        rotation = rotation * Ogre::Quaternion(angle, Ogre::Vector3(0, 1, 0));
		btMotionState* motion = mPhysicsBody->getRigidBody()->getMotionState();

		btTransform trans = mPhysicsBody->getRigidBody()->getWorldTransform();
		trans.setRotation(BtOgre::Convert::toBullet(rotation));
		motion->setWorldTransform(trans);

		velocity_magnitude += accumulate_force;
		
		if (velocity_magnitude < 0)
			velocity_magnitude = 0;
	}

	if (velocity_magnitude > mMaxSpeed)
		velocity_magnitude = mMaxSpeed;

	setVelocity(rotation * Ogre::Vector3(0, 0, velocity_magnitude));

	setDebugText(mStateMachine->getNameOfCurrentState());

	//Player::onUpdate(time_diff);
	dt::Node::onUpdate(time_diff);
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