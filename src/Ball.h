#ifndef FOOTBALL_AI_BALL
#define FOOTBALL_AI_BALL

#include "MovingEntity.h"
#include "CoolingTimeComponent.h"

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
	  * Function to test time spent when applying the ball
	  * a exact force. Compare with the getTimeToGoThroughDistance
	  * !!!!!!!Called only in onUpdate function!!!!!!!
	  * @length Distance to go through
	  * @force Force to apply to the ball
	  */
	void testTimeSpentByInitialForce(float length, float force);

	/** 
	  * Return time of the ball to go through a distance with a kick
	  * @param length Length of distance
	  * @param force Force to kick the ball
	  */
	float getTimeToGoThroughDistance(float length, float force);

	/** 
	  * Stop the ball, set the ball's velocity to be zero
	  */
	void stop(); 

	Ogre::Vector3 getOldPos() const;

	Ogre::Vector3 getVelocity() const;
	void setVelocity(Ogre::Vector3 velocity);

	Ogre::Vector3 getHeading() const;

private:

	Ogre::Vector3 mOldPos;                                      //!< Previous position of the ball
	std::shared_ptr<CoolingTimeComponent> mResistanceCoolTime;  //!< Cooling time component for resistance
	
};

#endif