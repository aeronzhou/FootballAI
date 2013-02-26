#ifndef FOOTBALL_AI_UTILS
#define FOOTBALL_AI_UTILS

#include <Scene/Node.hpp>

// Global functions

inline Ogre::Vector3 Vector3To2(Ogre::Vector3 vec)
{
	return Ogre::Vector3(vec.x, 0.f, vec.z);
}

inline Ogre::Vector3 Vector3To2Normalise(Ogre::Vector3 vec)
{
	return Vector3To2(vec).normalisedCopy();
}

// Return true if line-segment AB intersect line-segment CD
inline bool IsLineIntersect(Ogre::Vector3 A, Ogre::Vector3 B, Ogre::Vector3 C, Ogre::Vector3 D)
{
	float r_top = (A.z - C.z) * (D.x - C.x) - (A.x - C.x) * (D.z - C.z);
	float s_top = (A.z - C.z) * (B.x - A.x) - (A.x - C.x) * (B.z - A.z);

	float bot = (B.x - A.x) * (D.z - C.z) - (B.z - A.z) * (D.x - C.x);

	if (bot == 0)//parallel
	{
		return false;
	}

	float inv_bot = 1.0 / bot;
	float r = r_top * inv_bot;
	float s = s_top * inv_bot;

	if ( (r > 0) && (r < 1) && (s > 0) && (s < 1) )
	{
		//lines intersect
		return true;
	}

	//lines do not intersect
	return false;	
}

inline Ogre::Vector3 GetHeadingThroughRotation(Ogre::Quaternion rotation)
{
	//rotation = Ogre::Quaternion(1.f, Ogre::Vector3(0.f, rotation.getYaw(), 0.f));
	//return Ogre::Vector3(0.f, 0.f, 1.f) * rotation;
	return rotation * Ogre::Vector3(0.f, 0.f, 1.f);
}

#endif