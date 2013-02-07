#ifndef FOOTBALL_AI_REGION
#define FOOTBALL_AI_REGION

#include <Scene/Node.hpp>

class Region 
{
	enum RegionType 
	{
		HALF_SIZE,
		NORMAL
	};

protected:

	float mLeft;
	float mTop;
	float mRight;
	float mBottom;
	float mWidth;
	float mHeight;

	Ogre::Vector3 mCenter;

	int mId;

public:

	Region(float left, float top, float right, float bottom);

	/** 
	  * @param position
	  * @param type Region type
	  * @returns If the position is inside this region
	  */
	bool inside(Ogre::Vector3 position, RegionType type) const;	

	/** 
	  * @returns A random position within this region
	  */
	Ogre::Vector3 getRandomPosition() const;
};

#endif