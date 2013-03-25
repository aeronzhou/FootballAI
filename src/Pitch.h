#ifndef FOOTBALL_AI_PITCH
#define FOOTBALL_AI_PITCH

#include "Ball.h"
#include "Region.h"

#include <Scene/Node.hpp>
#include <Graphics/MeshComponent.hpp>

#include <vector>

class Team;
class Ball;
class Goal;

class Pitch : public dt::Node {
	Q_OBJECT

public:
	Pitch(const QString name = "Pitch");

	void onInitialize();

	void onDeinitialize();

	void onUpdate(double time_diff);

	Region* getRegionFromIndex(int index);
	Region* getPlayingArea() const;

	Ball* getBall() const;

private:

	/** 
	  * Create all regions
	  * @width Width of each region
	  * @height Height of each region
	  */
	void createRegions(float width, float height);


private:

	Ball* mBall;                   //!< Pointer to the ball
	Team* mRedTeam;                //!< Team at the left side
	Team* mBlueTeam;               //!< Team at the right side
	Goal* mRedGoal;                //!< Goal of red team
	Goal* mBlueGoal;               //!< Goal of blue team

	std::vector<Region*> mRegions; //!< Regions
	Region* mPlayingArea;          //!< Play ground area

};





#endif