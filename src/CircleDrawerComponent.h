#ifndef FOOTBALL_AI_CIRCLE_DRAWER
#define FOOTBALL_AI_CIRCLE_DRAWER

#include <Scene/Component.hpp>

#include <OgreSceneNode.h>
#include <OgreManualObject.h>

#include <QString>

class CircleDrawerComponent : public dt::Component
{
public:

	CircleDrawerComponent(QString name, 
						  Ogre::String material_name, 
						  float radius, 
						  float thickness,
						  Ogre::SceneNode* scene_node);

	void onInitialize();

	void onDeinitialize();

	void onUpdate(double time_diff);

	void setRadius(float radius);

	void setThickNess(float thickness);

	void setPos(const Ogre::Vector3& pos);

private:

	Ogre::String mMaterialName;
	Ogre::SceneNode* mSceneNode;
	std::shared_ptr<Ogre::ManualObject> mObject;
	Ogre::Vector3 mPos;
	float mRadius;
	float mThickness;

};

#endif