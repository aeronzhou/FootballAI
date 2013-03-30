#ifndef FOOTBALL_AI_STEERING_AIDER
#define FOOTBALL_AI_STEERING_AIDER

#include <Scene/Node.hpp>

class Ball;
class Player;

/** 
  * Motion aider of moving entity
  */
class SteeringBehaviors 
{
public:
	
	enum SteeringType
	{
		NONE =       0x0000,
		SEEK =       0x0001,
		ARRIVE =     0x0002,
		SEPARATION = 0x0004,
		PERSUIT =    0x0008,
		INTERPOSE =  0x0010
	};

	enum Deceleration 
	{
		SLOW = 3,
		NORMAL = 2,
		FAST = 1
	};

	SteeringBehaviors(Player* player, Ball* ball);

	Ogre::Vector3 getTarget() const;
	void setTarget(Ogre::Vector3 target);

	bool isTag() const;
	void setTag(bool tag);

	Ogre::Vector3 getSteeringForce() const;

	// Set On 
	void setSeekOn();
	void setArriveOn();
	void setPursuitOn();
	void setInterposeOn();
	void setSeparationOn();

	// Set off
	void setSeekOff();
	void setArriveOff();
	void setPursuitOff();
	void setInterposeOff();
	void setSeperationOff();

	bool isSeekOn() const;
	bool isArriveOn() const;
	bool isPersuitOn() const;
	bool isInterposeOn() const;
	bool isSeperationOn() const;

	/** 
	  * Calculate the steering force
	  */
	void calculateDrivingForce();


protected:

	Ogre::Vector3 mTarget;           
	Ogre::Vector3 mSteeringForce;     

	Player* mPlayer;                  //!< The player this steering component attach to
	Ball* mBall;   

	int mFlag;                        //!< Behavior Mask
	int mTag;                         //!< Indicate if the attached player is chosen by others
	float mMaxForce;                  //!< Max force this steering component can accept

private:

	bool on(SteeringType type) const;

	Ogre::Vector3 seek(Ogre::Vector3 target);

	Ogre::Vector3 arrive(Ogre::Vector3 target, Deceleration decel);

	Ogre::Vector3 pursuit(const Ball* ball);

	Ogre::Vector3 interpose(const Ball* ball, Ogre::Vector3 pos, float dist_from_target);

	Ogre::Vector3 separation();

	/** 
	  * Return if the previous force can add another one
	  * @param prev_force Previous force
	  * @force_add Force to add
	  * @returns If the previous force can add another one
	  */
	bool accumulateForce(Ogre::Vector3& prev_force, Ogre::Vector3 force_add);

	/** 
	  * Combine all force
	  */
	void combineForce();

	/** 
	  * If the length of mStreeringForc over max_force
	  * truncate it, make sure Z axis speed is zero
	  */
	void regularizeForce();

	/** 
	  * Tagged neighbours who are in visible range
	  */
	void tagNeighbouringPlayers();

};

#endif 