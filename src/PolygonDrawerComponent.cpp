#include "PolygonDrawerComponent.h"

PolygonDrawerComponent::PolygonDrawerComponent(QString name, const std::vector<Ogre::Vector3>& path, float thikness,
	Ogre::String material_name, Ogre::SceneNode* scene_node) : dt::Component(name), mPath(path), mRotation(Ogre::Quaternion::ZERO),
	mSceneNode(scene_node), mPos(Ogre::Vector3::ZERO), mMaterialName(material_name), mThickness(thikness) {} 

void PolygonDrawerComponent::onInitialize() 
{
	mPoints.resize(mPath.size());
	mObject = std::shared_ptr<Ogre::ManualObject>(new Ogre::ManualObject(getName().toStdString() + "Drawer"));
	mSceneNode->attachObject(mObject.get());
}

void PolygonDrawerComponent::onDeinitialize() {}

const float accuracy = 20;

void PolygonDrawerComponent::onUpdate(double time_diff)
{
	_updateRealPoints();

	mObject->clear();

	mObject->begin(mMaterialName, Ogre::RenderOperation::OT_TRIANGLE_LIST);

	unsigned point_index = 0;
	unsigned sz = mPath.size(); 

	for (int i = 0; i < sz; ++i)
	{
		float dx = (mPoints[(i + 1) % sz].x - mPoints[i].x) / accuracy;
		float dz = (mPoints[(i + 1) % sz].z - mPoints[i].z) / accuracy;
		Ogre::Vector3 nr = Ogre::Vector3(dx, 0, dz).normalisedCopy();
		Ogre::Vector3 ng = mThickness * Ogre::Vector3(nr.z, 0, -nr.x);

		for (int j = 0; j < accuracy; ++j)
		{
			mObject->position(mPoints[i].x + j * dx, 0.1, mPoints[i].z + j * dz);
			mObject->position(mPoints[i].x + j * dx + dx, 0.1, mPoints[i].z + j * dz + dz);
			mObject->position(mPoints[i].x + j * dx + dx + ng.x, 0.1, mPoints[i].z + j * dz + dz + ng.z);
			mObject->position(mPoints[i].x + j * dx + ng.x, 0.1, mPoints[i].z + j * dz + ng.z);
			mObject->quad(point_index, point_index + 1, point_index + 2, point_index + 3);
			point_index += 4;
		}
	}

	mObject->end();	
}

void PolygonDrawerComponent::setPos(const Ogre::Vector3& pos)
{
	mPos = pos;
}

void PolygonDrawerComponent::setRotation(const Ogre::Quaternion& rotation)
{
	mRotation = rotation;
}

void PolygonDrawerComponent::_updateRealPoints()
{
	for (int i = mPath.size() - 1; i >= 0; --i)
	{
		mPoints[i] = mRotation * mPath[i] + mPos;
	}
}

std::vector<Ogre::Vector3>& PolygonDrawerComponent::getPolygonPoints()
{
	return mPoints;
}