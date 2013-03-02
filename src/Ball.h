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
	  * Test if the ball out of pitch
	  * Deal with such situation
	  */
	void ballOutOfPitch();


	/** 
	  * Kick the ball with directional force
	  * @param direction Direction of the force
	  * @param force Magnitude of the force
	  */
	void kick(Ogre::Vector3 direction, float force);

	/** 
	  * Calculate time of ball to move from a place to another with a force
	  * @param from Place from
	  * @param to Place to reach
	  * @param force Magnitude of the force
	  */
	double timeToCoverDistance(Ogre::Vector3 from, Ogre::Vector3 to, float force) const;


	/** 
	  * Next position the ball will be within time seconds
	  * @param time 
	  * @returns Future position
	  */
	Ogre::Vector3 getFuturePosition(double time) const;

	/** 
	  * Stop the ball, set the ball's velocity to be zero
	  */
	void stop() { /*mVelocity = Ogre::Vector3::ZERO;*/ }

	Ogre::Vector3 getOldPos() { return mOldPos; }

	/** 
	  * Put the ball in a particular position
	  */
	void playAtPosition(Ogre::Vector3 pos);

private:

	Ogre::Vector3 mOldPos; //!< Previous position of the ball
	
};

/** 
  * Change the accuarcy of the ball
  */
Ogre::Vector3 addNoiseToKick(Ogre::Vector3 ball_pos, Ogre::Vector3 ball_target);

#endif