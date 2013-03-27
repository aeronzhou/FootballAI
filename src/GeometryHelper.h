#ifndef FOOTBALL_AI_GEOMETRY_HELPER
#define FOOTBALL_AI_GEOMETRY_HELPER

#include <OgreVector3.h>

/** 
  * Class to solve geometry problem
  */
class GeometryHelper 
{
public:
	static GeometryHelper& get();

	/** 
	  * Return true if u1-u2 and v1-v2 intersect
	  * @param u1 Point u1
	  * @param u2 Point u2
	  * @param v1 Point v1
	  * @param v2 Point v2
	  * @param ret intersect point
	  * @returns True if u1-u2 and v1-v2 intersect 
	  */
	bool lineSegmentIntersect(const Ogre::Vector3& u1, const Ogre::Vector3& u2, 
		const Ogre::Vector3& v1, const Ogre::Vector3& v2, Ogre::Vector3 &ret);

private:

	float _xmult(const Ogre::Vector3& p1, const Ogre::Vector3& p2, const Ogre::Vector3& p0);
	int _dot_online_in(const Ogre::Vector3& p, const Ogre::Vector3& l1, const Ogre::Vector3& l2);
	int _same_side(const Ogre::Vector3& p1, const Ogre::Vector3& p2, const Ogre::Vector3& l1, const Ogre::Vector3& l2);
	int _parallel(const Ogre::Vector3& u1, const Ogre::Vector3& u2, const Ogre::Vector3& v1, const Ogre::Vector3& v2);
	int _dots_inline(const Ogre::Vector3& p1, const Ogre::Vector3& p2, const Ogre::Vector3& p3);
	int _intersect_in(const Ogre::Vector3& u1, const Ogre::Vector3& u2, const Ogre::Vector3& v1, const Ogre::Vector3& v2);

};

#endif