#ifndef FOOTBALL_AI_MANUAL_COMPONENT
#define FOOTBALL_AI_MANUAL_COMPONENT

#include <Scene/Component.hpp>

class ManualComponent : public dt::Component
{
public:

	/** 
	  * Constructor
	  * @position 
	  * @radius
	  */
	ManualComponent(Ogre::Vector3 position, double radius, QString name = "ManualComponent");

	void onInitialize();

	void onUpdate(double time_diff);

protected:

       Ogre::Vector3 mPosition;

	   double mRadius;
};

#endif