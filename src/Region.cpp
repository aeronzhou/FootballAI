#include "Region.h"

#include <Utils/Random.hpp>

#include <math.h>

Region::Region(float left, float top, float right, float bottom, int id, float margin)
	: mLeft(left), mRight(right), mTop(top), mBottom(bottom), mID(id), mMargin(margin)
{
	mWidth = mRight - mLeft;
	mHeight = mBottom - mTop;
	mCenter = Ogre::Vector3(mLeft + mWidth / 2, 0.f, mTop + mHeight / 2);

	mMargin = std::min(mMargin, mWidth / 2);
	mMargin = std::min(mMargin, mHeight / 2);
}

bool Region::inside(Ogre::Vector3 position, RegionType type) const
{
	if (type == NORMAL)
	{
		return (position.x > mLeft && position.x < mRight && position.z > mTop && position.z < mBottom);
	}
	else
	{
		float half_x = mWidth / 4;
		float half_z = mHeight / 4;
		return (position.x > mLeft + half_x && position.x < mRight - half_x &&
				position.z > mTop + half_z && position.z < mBottom - half_z);
	}
}

Ogre::Vector3 Region::getRandomPosition() const
{
	float x = dt::Random::get(mLeft, mRight);
	float z = dt::Random::get(mTop, mBottom);
	return Ogre::Vector3(x, 0, z);
}

bool Region::onMargin(const Ogre::Vector3& position) const 
{
	return (position.x < mLeft + mMargin || 
		position.x > mRight - mMargin ||
		position.z < mTop + mMargin ||
		position.z > mBottom - mMargin);
}

float Region::getLeft() const {	return mLeft; }

float Region::getTop() const { return mTop; }

float Region::getRight() const { return mRight; }

float Region::getBottom() const { return mBottom; }

float Region::getWidth() const { return mWidth; }

float Region::getHeight() const { return mHeight; }

int Region::getID() const { return mID; }

Ogre::Vector3 Region::getCenter() const { return mCenter; }