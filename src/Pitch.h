#ifndef FOOTBALL_AI_PITCH
#define FOOTBALL_AI_PITCH

#include "Ball.h"
#include "Region.h"

#include <Scene/Node.hpp>
#include <Graphics/MeshComponent.hpp>

#include <vector>

class Pitch : public dt::Node {
	Q_OBJECT

public:
	Pitch(const QString name = "Pitch");

	void onInitialize();

	void onDeinitialize();

	void onUpdate(double time_diff);

	bool getGoalKeeperHasBall() const;

	void setGoalKeeperHasBall(bool flag);

private:

	Ball* mBall;                   //!< Pointer to the ball

	std::vector<Region*> mRegions; //!< Regions

	bool mGameOn;                  //!< Whether game is running

	bool mGoalKeeperHasBall;       //!< If the goal keeper is controlling the ball

	

};





#endif