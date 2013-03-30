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

	const std::vector<Region*>& getAllRegions() const;

	/** 
	  * Return true if the game is going on
	  * @returns True if the game is going on
	  */
	bool isGameOn() const;
	void setGameOn(bool flag);

	bool isGoalKeeperHasBall() const;
	void setGoalKeeperHasBall(bool flag);

	/** 
	  * Set the team to kick off
	  * @param team Team to kick off
	  */
	void setTeamToKickOff(Team* team);

	/** 
	  * Return true if the team is going for kicking off
	  * @returns True if the team is going for kicking off
	  */
	bool isGoingForKickingOff(Team* team);

private:

	/** 
	  * Create all regions
	  * @width Width of each region
	  * @height Height of each region
	  */
	void createRegions(float width, float height);


private:

	Ball* mBall;                    //!< Pointer to the ball
	Team* mRedTeam;                 //!< Team at the left side
	Team* mBlueTeam;                //!< Team at the right side
	Goal* mRedGoal;                 //!< Goal of red team
	Goal* mBlueGoal;                //!< Goal of blue team

	std::vector<Region*> mRegions;  //!< Regions
	Region* mPlayingArea;           //!< Play ground area

	bool mGameOn;                   //!< If game is on
	bool mGoalKeeperHasBall;        //!< If the goal keeper has captured the ball
	Team* mTeamToKickOff;           //!< Team to kick of the ball at the very beginning
};





#endif