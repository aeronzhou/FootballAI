#ifndef FOOTBALL_AI_BALL
#define FOOTBALL_AI_BALL

#include "MovingEntity.h"

class Ball : public MovingEntity
{
	Q_OBJECT

public:

	Ball(QString name, QString mesh_handle, QString material_handle = "");

	void onInitialize();

	void onUpdate(double time_diff);

	/** 
	  * Kick the ball with directional force
	  * @param direction Direction of the force
	  * @param force Magnitude of the force
	  */
	void kick(Ogre::Vector3 direction, float force);

	/** 
	  * Stop the ball, set the ball's velocity to be zero
	  */
	void stop() { /*mVelocity = Ogre::Vector3::ZERO;*/ }

	Ogre::Vector3 getOldPos() { return mOldPos; }

private:

	Ogre::Vector3 mOldPos; //!< Previous position of the ball
	
};

/** 
  * Change the accuarcy of the ball
  */
Ogre::Vector3 addNoiseToKick(Ogre::Vector3 ball_pos, Ogre::Vector3 ball_target);

#endif