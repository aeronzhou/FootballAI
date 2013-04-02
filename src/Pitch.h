#ifndef FOOTBALL_AI_PITCH
#define FOOTBALL_AI_PITCH

#include "Ball.h"
#include "Region.h"
#include "CircleDrawerComponent.h"

#include <Scene/Node.hpp>
#include <Graphics/MeshComponent.hpp>

#include <OgreSceneNode.h>

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

	Region* getRegionByIndex(int index);
	int getRegionIndexByPosition(const Ogre::Vector3& position);
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
	void _createRegions(float width, float height);

	/** 
	  * Update player range drawer
	  */
	void _updatePlayerRangeDrawer();

	/** 
	  * Drawer to show player's target
	  */
	void _updatePlayerTargetDrawer();




private:

	Ball* mBall;                                                     //!< Pointer to the ball
	Team* mRedTeam;                                                  //!< Team at the left side
	Team* mBlueTeam;                                                 //!< Team at the right side
	Goal* mRedGoal;                                                  //!< Goal of red team
	Goal* mBlueGoal;                                                 //!< Goal of blue team

	std::vector<Region*> mRegions;                                   //!< Regions
	Region* mPlayingArea;                                            //!< Play ground area

	bool mGameOn;                                                    //!< If game is on
	bool mGoalKeeperHasBall;                                         //!< If the goal keeper has captured the ball
	Team* mTeamToKickOff;                                            //!< Team to kick of the ball at the very beginning

	Ogre::SceneNode* mSceneNode;                                     //!< Scene Node
	std::shared_ptr<CircleDrawerComponent> mPlayerRangeDrawer;       //!< Circle Drawer of player range
	std::shared_ptr<CircleDrawerComponent> mPlayerTargetDrawer;      //!< Circle Drawer of player target
};





#endif