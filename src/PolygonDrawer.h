#ifndef FOOTBALL_AI_POLYGON_DRAWER
#define FOOTBALL_AI_POLYGON_DRAWER

#include <QString>

#include <OgreSceneNode.h>
#include <OgreManualObject.h>

#include <vector>

class PolygonDrawer 
{
public:
	PolygonDrawer(QString name, const std::vector<Ogre::Vector3>& path, float thickness, 
		Ogre::String material_name, Ogre::SceneNode* scene_node);

	void draw();

	void clear();

	void setPos(const Ogre::Vector3& pos);

	void setRotation(const Ogre::Quaternion& rotation);

private:

	void _updateRealPoints();

	Ogre::Quaternion mRotation;                //!< Rotation of this pologon
	Ogre::Vector3 mPos;
	std::vector<Ogre::Vector3> mPath;
	std::vector<Ogre::Vector3> mPoints;        //!< Points of polygon

	float mThickness;
	Ogre::String mMaterialName;
	Ogre::SceneNode* mSceneNode;
	std::shared_ptr<Ogre::ManualObject> mObject;
};

#endif