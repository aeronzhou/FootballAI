#include "ManualComponent.h"
#include <OgreManualObject.h>

ManualComponent::ManualComponent(Ogre::Vector3 position, double radius, QString name)
	:Component(name),mPosition(position),mRadius(radius){}


void ManualComponent::onInitialize()
{
	Ogre::Vector3 points[3];
	points[0] = points[1] = points[2] = mPosition;
	points[1].y += 5;	points[1].x += 5;		points[1].z += 7;
	points[2].x += 10;  points[2].y += 100;		points[2].z += 100; 

	Ogre::ManualObject* pManual = new Ogre::ManualObject("circle");
	pManual->begin("circle", Ogre::RenderOperation::OT_LINE_LIST);
	pManual->position(points[0]);
	pManual->position(points[1]);
	pManual->position(points[2]);
	pManual->end();

}


void ManualComponent::onUpdate(double time_diff)
{

}