#ifndef FOOTBALL_AI_COOLING_TIME_COMPONENT
#define FOOTBALL_AI_COOLING_TIME_COMPONENT

#include <Scene/Component.hpp>

class CoolingTimeComponent : public dt::Component
{
public:

	/** 
	  * Constructor
	  * @time_interval Time interval to get ready for next time tick
	  */
	CoolingTimeComponent(double cooling_time, QString name = "CoolingTimeComponent");

	void onInitialize();

	void onUpdate(double time_diff);

	/** 
	  * @returns True if the cooling time is run out
	  */
	bool ready();

	/** 
	  * Reset timer
	  */
	void reset();

protected:

	double mCoolingTime;
	double mCurTime;
};

#endif