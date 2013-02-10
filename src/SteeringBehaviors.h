#ifndef FOOTBALL_AI_STEERING_BEHAVIORS
#define FOOTBALL_AI_STEERING_BEHAVIORS

#include <Scene/Node.hpp>

class Ball;
class Player;

/** 
  * Aid of moving entity
  */
class SteeringBehaviors 
{
public:
	
	enum SteeingType
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

protected:

	Ogre::Vector3 mTarget;           
	Ogre::Vector3 mSteeringForce;     
	float mInterposeDist;             //!< Distance the player try to interpose opponents

	Player* mPlayer;                  //!< The player this steering component attach to
	Ball* mBall;   

	int mFlag;

private:

	bool on(SteeingType type) const { return ((mFlag & type) == type); }

	Ogre::Vector3 seek(Ogre::Vector3 target);

	Ogre::Vector3 arrive(Ogre::Vector3 target, Deceleration decel);

	Ogre::Vector3 persuit(const Ball* ball);

	Ogre::Vector3 separation();

	Ogre::Vector3 interpose(const Ball* ball, Ogre::Vector3 pos, float dis_from_target);

public:

	void seekOn() { mFlag |= SEEK; }
	void arriveOn() { mFlag |= ARRIVE; }
	void pursuitOn() { mFlag |= PERSUIT; }
	void separationOn() { mFlag |= SEPARATION; }
	void interposeOn() { mFlag |= INTERPOSE; }

	void seekOff();
	void arriveOff();
	void persuitOff();
	void seperationOff();
	void interposeOff();

	bool isSeekOn() const { return on(SEEK); }
	bool isArriveOn() const { return on(ARRIVE); } 
	bool isPersuitOn() const { return on(PERSUIT); }
	bool isSeperationOn() const { return on(SEPARATION); }
	bool isInterposeOn() const { return on(INTERPOSE); }
};

#endif 