#include "Region.h"


Region::Region(float left, float top, float right, float bottom)
	: mLeft(left), mRight(right), mTop(top), mBottom(bottom)
{
	mWidth = mRight - mLeft;
	mHeight = mBottom - mTop;
}

bool Region::inside(Ogre::Vector3 position, RegionType type) const
{
	if (type == NORMAL)
	{
		return (position.x > mLeft && position.x < mRight && position.z > mTop && position.z < mBottom);
	}
	else
	{
		float half_x = mWidth / 2;
		float half_z = mHeight / 2;
		return (position.x > mLeft + half_x && position.x < mRight - half_x &&
				position.z > mTop + half_z && position.z < mBottom - half_z);
	}
}

Ogre::Vector3 Region::getRandomPosition() const
{
	//////////////////////////////////////////////////////////////////////////
	return Ogre::Vector3(0, 0, 0);
}