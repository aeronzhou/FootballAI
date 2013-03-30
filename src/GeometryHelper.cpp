#include "GeometryHelper.h"
#include "Constant.h"

#define zero(x) (((x)>0?(x):-(x))<EPS)

GeometryHelper& GeometryHelper::get() 
{
	static GeometryHelper instance;
	return instance;
}

float GeometryHelper::_xmult(const Ogre::Vector3& p1, const Ogre::Vector3& p2, const Ogre::Vector3& p0)
{
	return (p1.x - p0.x) * (p2.z - p0.z) - (p2.x - p0.x) * (p1.z - p0.z);
}

int GeometryHelper::_dot_online_in(const Ogre::Vector3& p, const Ogre::Vector3& l1, const Ogre::Vector3& l2)
{
	return zero(_xmult(p, l1, l2)) && (l1.x - p.x) * (l2.x - p.x) < EPS && (l1.z - p.z) * (l2.z - p.z) < EPS;
}

int GeometryHelper::_same_side(const Ogre::Vector3& p1, const Ogre::Vector3& p2, const Ogre::Vector3& l1, const Ogre::Vector3& l2)
{
	return _xmult(l1, p1, l2) * _xmult(l1, p2, l2) > EPS;
}

int GeometryHelper::_parallel(const Ogre::Vector3& u1, const Ogre::Vector3& u2, const Ogre::Vector3& v1, const Ogre::Vector3& v2)
{
	return zero((u1.x - u2.x) * (v1.z - v2.z) - (v1.x - v2.x) * (u1.z - u2.z));
}

int GeometryHelper::_dots_inline(const Ogre::Vector3& p1, const Ogre::Vector3& p2, const Ogre::Vector3& p3)
{
	return zero(_xmult(p1, p2, p3));
}

int GeometryHelper::_intersect_in(const Ogre::Vector3& u1, const Ogre::Vector3& u2, const Ogre::Vector3& v1, const Ogre::Vector3& v2)
{
	if (!_dots_inline(u1, u2, v1) || !_dots_inline(u1, u2, v2))
		return !_same_side(u1, u2, v1, v2) && !_same_side(v1, v2, u1, u2);
	return _dot_online_in(u1, v1, v2) || _dot_online_in(u2, v1, v2) || _dot_online_in(v1, u1, u2) || _dot_online_in(v2, u1, u2);
}


bool GeometryHelper::lineSegmentIntersect(const Ogre::Vector3& u1, const Ogre::Vector3& u2,
	const Ogre::Vector3& v1, const Ogre::Vector3& v2, Ogre::Vector3 &ret)
{
	if (_parallel(u1, u2, v1, v2) || !_intersect_in(u1, u2, v1, v2))
		return false;

	ret = u1;
	float t = ((u1.x - v1.x) * (v1.z - v2.z) - (u1.z - v1.z) * (v1.x - v2.x))
		/ ((u1.x - u2.x) * (v1.z - v2.z) - (u1.z - u2.z) * (v1.x - v2.x));
	ret.x += (u2.x - u1.x) * t;
	ret.z += (u2.z - u1.z) * t;
	ret.y = 0.f;

	return true;
}