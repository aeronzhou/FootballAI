#ifndef FOOTBALL_AI_SUPPORT_SPOT_CALCULATOR
#define FOOTBALL_AI_SUPPORT_SPOT_CALCULATOR

#include "CoolingTimeComponent.h"
#include "CircleDrawer.h"

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
		Ogre::Vector3 position;                             //!< Position of the spot
		float score;                                        //!< Score of this spot
		std::shared_ptr<CircleDrawer> drawer;               //!< Circle drawer

		SupportSpot() {}
		SupportSpot(const Ogre::Vector3& pos, float score) : position(pos), score(score) {}
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

protected:

	std::vector<SupportSpot> mSpots;                       //!< Spots
	SupportSpot* mBestSupportSpot;                         //!< Best spot to support
	Team* mTeam;                                           //!< Team belongs to
	std::shared_ptr<CoolingTimeComponent> mCoolingTime;    //!< We should not calculate every single frame, so...
};

#endif