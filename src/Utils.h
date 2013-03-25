#ifndef FOOTBALL_AI_UTILS
#define FOOTBALL_AI_UTILS

#include "Constant.h"

#include <Scene/Node.hpp>
#include <Utils/Random.hpp>

#include <ostream>

// Global functions

inline Ogre::Vector3 Vector3To2(const Ogre::Vector3& vec)
{
	return Ogre::Vector3(vec.x, 0.f, vec.z);
}

inline Ogre::Vector3 Vector3To2Normalise(const Ogre::Vector3& vec)
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
	return rotation * STANDARD_HEADING;
}

inline Ogre::Quaternion GetRotationThroughHeading(Ogre::Vector3 heading)
{
	return STANDARD_HEADING.getRotationTo(heading);
}

inline void Vector3Truncate(Ogre::Vector3& vec, float magnitude)
{
	if (vec.squaredLength() > magnitude * magnitude)
	{
		vec = vec.normalisedCopy() * magnitude;
	}
}

/** 
  * With success rate to do something, return true if it is probable
  * @param success_rate Success rate
  * @returns Return true if it is probable to do something
  */
inline bool WithPossibility(float success_rate)
{
	return dt::Random::get(0.f, 1.f) < success_rate;
}

/** 
  * Add noise to a point
  * @param point Point to add noise to
  * @radius Noise range
  * @returns Result point
  */
inline Ogre::Vector3 AddNoiseToPoint(const Ogre::Vector3& point, float radius = 1.0f)
{
	float x = dt::Random::get(0, 1);
	float z = dt::Random::get(0, 1);
	return point + Ogre::Vector3(x, 0, z).normalisedCopy() * dt::Random::get(0.f, radius);
}

/** 
  * Add noise to a target, call when applying a ball kick
  * @param from Start
  * @param to Destination 
  * @param degree Degree noise range
  * @returns Result target
  */
inline Ogre::Vector3 AddNoiseToTarget(const Ogre::Vector3& from, const Ogre::Vector3& to, float degree = 30.f)
{
	Ogre::Radian angle(dt::Random::get(-degree / 360, degree / 360));
	Ogre::Vector3 to_target = Vector3To2(to - from);
	Ogre::Quaternion rotation = GetRotationThroughHeading(to_target) * Ogre::Quaternion(angle, Ogre::Vector3(0, 1, 0));

	return from + rotation * Ogre::Vector3(0, 0, to_target.length());
}


// Debug_Mode
#define DEBUG_MODE_SETUP \
	double _debug_time_interval = 2; \
	double _debug_current_time = 2;

#define DEBUG_MODE_BEGIN \
	_debug_current_time += TIME_DIFF; \
	if (_debug_current_time > _debug_time_interval) \
	{ \
		_debug_current_time = 0; 
#define DEBUG_MODE_END \
	}
// Debug_Mode



#endif