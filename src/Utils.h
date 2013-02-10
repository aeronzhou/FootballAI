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



#endif