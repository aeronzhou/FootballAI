#ifndef FOOTBALL_AI_FOOTBALL_PITCH
#define FOOTBALL_AI_FOOTBALL_PITCH

#include <Scene/Node.hpp>
#include <Graphics/MeshComponent.hpp>

class Ball;
class Region;
class Goal;
class Team;
class Player;

class SoccerPitch : public dt::Node {
	Q_OBJECT

public:
	SoccerPitch(const QString name = "SoccerPitch");

	void onInitialize();

	void onDeinitialize();

	void onUpdate(double time_diff);

private:

	//dt::MeshComponent mMesh; 

};





#endif