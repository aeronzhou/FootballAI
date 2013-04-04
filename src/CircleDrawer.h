#ifndef FOOTBALL_AI_CIRCLE_DRAWER
#define FOOTBALL_AI_CIRCLE_DRAWER

#include <OgreSceneNode.h>
#include <OgreManualObject.h>

#include <QString>

class CircleDrawer
{
public:

	CircleDrawer(QString name, Ogre::SceneNode* scene_node, float thickness, Ogre::String material);

	void highlight(float radius, const Ogre::String& material_name);

	void draw(float radius);

	void clear();

	void setPos(const Ogre::Vector3& pos);

private:

	Ogre::SceneNode* mSceneNode;
	std::shared_ptr<Ogre::ManualObject> mObject;
	float mThickness;
	Ogre::Vector3 mPos;
	Ogre::String mMaterialName;

};

#endif