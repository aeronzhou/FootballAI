#include "CircleDrawerComponent.h"
#include "Constant.h"

CircleDrawerComponent::CircleDrawerComponent(QString name, Ogre::String material_name, float radius, 
	float thickness, Ogre::SceneNode* scene_node) : dt::Component(name), mMaterialName(material_name), mRadius(radius),
	mThickness(thickness), mSceneNode(scene_node), mPos(Ogre::Vector3::ZERO) {}

void CircleDrawerComponent::onInitialize()
{
	mObject = std::shared_ptr<Ogre::ManualObject>(new Ogre::ManualObject(getName().toStdString() + "CircleDrawer"));
	mSceneNode->attachObject(mObject.get());
}

void CircleDrawerComponent::onDeinitialize() {}

const float accuracy = 20;

void CircleDrawerComponent::onUpdate(double time_diff)
{
	mObject->clear();

	mObject->begin(mMaterialName, Ogre::RenderOperation::OT_TRIANGLE_LIST);

	unsigned point_index = 0;

	for (float theta = 0; theta <= 2 * PI; theta += PI / accuracy) {
		mObject->position(mRadius * cos(theta) + mPos.x,
			0.1,
			mRadius * sin(theta) + mPos.z);
		mObject->position(mRadius * cos(theta - PI / accuracy) + mPos.x,
			0.1,
			mRadius * sin(theta - PI / accuracy ) + mPos.z);
		mObject->position((mRadius - mThickness) * cos(theta - PI / accuracy)  + mPos.x,
			0.1,
			(mRadius - mThickness) * sin(theta - PI / accuracy) + mPos.z);
		mObject->position((mRadius - mThickness) * cos(theta) + mPos.x,
			0.1,
			(mRadius - mThickness) * sin(theta) + mPos.z);
		// Join the 4 vertices created above to form a quad.
		mObject->quad(point_index, point_index + 1, point_index + 2, point_index + 3);
		point_index += 4;
	}

	mObject->end();
}


void CircleDrawerComponent::setRadius(float radius)
{
	mRadius = radius;
}

void CircleDrawerComponent::setThickNess(float thickness)
{
	mThickness = thickness;
}

void CircleDrawerComponent::setPos(const Ogre::Vector3& pos)
{
	mPos = pos;
}