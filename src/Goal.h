#ifndef FOOTBALL_AI_GOAL
#define FOOTBALL_AI_GOAL

#include <Scene/Node.hpp>

class Ball;

/** 
  * Goal entity
  */
class Goal : public dt::Node
{
public:

	/** 
	  * Constructor 
	  * @name Node name
	  * @left Left post of this goal
	  * @right Right post of this goal
	  * @facing Direction this goal is facing
	  * @ball Pointer to the ball
	  */
	Goal(const QString& name, Ogre::Vector3 left, Ogre::Vector3 right, Ogre::Vector3 facing, Ball* ball);

	void onInitialize();

	void onUpdate(double time_diff);

	// Get ans set
	Ogre::Vector3 getLeftPost() const;
	Ogre::Vector3 getRightPost() const;
	Ogre::Vector3 getCenter() const;
	Ogre::Vector3 getFacing() const;
	
	int getScores() const;

	/** 
	  * @returns True if scored 
	  */
	bool isScored();

	/** 
	  * Call after position or rotation is changed
	  */
	void resetPhysicsBody();

private:

	Ogre::Vector3 mLeftPost;              
	Ogre::Vector3 mRightPost;
	Ogre::Vector3 mFacing;
	Ogre::Vector3 mCenter;                                   //!< Center of this goal

	int mScores;                                             //!< Number of points has been scored

	Ball* mBall;
};

#endif