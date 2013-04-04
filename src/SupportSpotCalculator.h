#ifndef FOOTBALL_AI_SUPPORT_SPOT_CALCULATOR
#define FOOTBALL_AI_SUPPORT_SPOT_CALCULATOR

#include "Region.h"
#include "CoolingTimeComponent.h"
#include "CircleDrawerComponent.h"

#include <Scene/Node.hpp>
#include <Graphics/MeshComponent.hpp>

#include <vector>

class Team;


/** 
  * Class to calculate the best support spot of team when attacking
  */
class SupportSpotCalculator : public dt::Node 
{
protected:

	struct SupportSpot 
	{
		Region* region;        //!< Pointer to region
		float score;           //!< Score of this spot

		SupportSpot() {}
		SupportSpot(Region* region, float score) : region(region), score(score) {}
	};

public:

	/** 
	  * Constructor
	  * @param name Name of this node
	  * @param team Team attached to
	  */
	SupportSpotCalculator(const QString& name, Team* team);

	void onInitialize();

	void onDeinitialize();

	void onUpdate(double time_diff);

	Ogre::Vector3 getBestSupportSpot();
	
	virtual void determineBestSupportSpot();

	void setShowFlag(bool flag);

protected:

	std::vector<SupportSpot> mSpots;                       //!< Spots
	SupportSpot* mBestSupportSpot;                         //!< Best spot to support
	Team* mTeam;                                           //!< Team belongs to
	std::shared_ptr<CoolingTimeComponent> mCoolingTime;    //!< We should not calculate every single frame, so...
	std::shared_ptr<CircleDrawerComponent> mSpotFlagDrawer;//!< Circle drawer component of spot flag
};

#endif