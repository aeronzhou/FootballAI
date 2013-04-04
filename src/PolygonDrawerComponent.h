#ifndef FOOTBALL_AI_POLYGON_DRAWER_COMPONENT
#define FOOTBALL_AI_POLYGON_DRAWER_COMPONENT

#include <Scene/Component.hpp>

#include <OgreSceneNode.h>
#include <OgreManualObject.h>

#include <vector>

class PolygonDrawerComponent : public dt::Component
{
public:
	PolygonDrawerComponent(QString name, const std::vector<Ogre::Vector3>& path, float thickness, 
		Ogre::String material_name, Ogre::SceneNode* scene_node);

	void onInitialize();

	void onDeinitialize();

	void onUpdate(double time_diff);

	void setPos(const Ogre::Vector3& pos);

	void setRotation(const Ogre::Quaternion& rotation);

	std::vector<Ogre::Vector3>& getPolygonPoints();

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