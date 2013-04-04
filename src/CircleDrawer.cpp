#include "CircleDrawer.h"
#include "Constant.h"

CircleDrawer::CircleDrawer(QString name, Ogre::SceneNode* scene_node, float thikness, Ogre::String material) 
	: mSceneNode(scene_node), mThickness(thikness), mPos(Ogre::Vector3::ZERO), mMaterialName(material)
{
	mObject = std::shared_ptr<Ogre::ManualObject>(new Ogre::ManualObject(name.toStdString() + "Spot"));
	mSceneNode->attachObject(mObject.get());
}

const float accuracy = 20;

void CircleDrawer::draw(float radius)
{
	mObject->clear();

	mObject->begin(mMaterialName, Ogre::RenderOperation::OT_TRIANGLE_LIST);

	unsigned point_index = 0;

	for (float theta = 0; theta <= 2 * PI; theta += PI / accuracy) {
		mObject->position(radius * cos(theta) + mPos.x,
			0.1,
			radius * sin(theta) + mPos.z);
		mObject->position(radius * cos(theta - PI / accuracy) + mPos.x,
			0.1,
			radius * sin(theta - PI / accuracy ) + mPos.z);
		mObject->position((radius - mThickness) * cos(theta - PI / accuracy)  + mPos.x,
			0.1,
			(radius - mThickness) * sin(theta - PI / accuracy) + mPos.z);
		mObject->position((radius - mThickness) * cos(theta) + mPos.x,
			0.1,
			(radius - mThickness) * sin(theta) + mPos.z);
		// Join the 4 vertices created above to form a quad.
		mObject->quad(point_index, point_index + 1, point_index + 2, point_index + 3);
		point_index += 4;
	}

	mObject->end();
}

void CircleDrawer::highlight(float radius, const Ogre::String& material_name)
{
	mObject->clear();

	mObject->begin(material_name, Ogre::RenderOperation::OT_TRIANGLE_LIST);

	float thickness = mThickness * 2.2;

	unsigned point_index = 0;

	for (float theta = 0; theta <= 2 * PI; theta += PI / accuracy) {
		mObject->position(radius * cos(theta) + mPos.x,
			0.1,
			radius * sin(theta) + mPos.z);
		mObject->position(radius * cos(theta - PI / accuracy) + mPos.x,
			0.1,
			radius * sin(theta - PI / accuracy ) + mPos.z);
		mObject->position((radius - thickness) * cos(theta - PI / accuracy)  + mPos.x,
			0.1,
			(radius - thickness) * sin(theta - PI / accuracy) + mPos.z);
		mObject->position((radius - thickness) * cos(theta) + mPos.x,
			0.1,
			(radius - thickness) * sin(theta) + mPos.z);
		// Join the 4 vertices created above to form a quad.
		mObject->quad(point_index, point_index + 1, point_index + 2, point_index + 3);
		point_index += 4;
	}

	mObject->end();
}

void CircleDrawer::clear()
{
	mObject->clear();
}

void CircleDrawer::setPos(const Ogre::Vector3& pos)
{
	mPos = pos;
}