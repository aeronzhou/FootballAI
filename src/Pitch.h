#ifndef FOOTBALL_AI_PITCH
#define FOOTBALL_AI_PITCH

#include <Scene/Node.hpp>
#include <Graphics/MeshComponent.hpp>

class Ball;
class Region;
class Goal;
class Team;
class Player;

class Pitch : public dt::Node {
	Q_OBJECT

public:
	Pitch(const QString name = "Pitch");

	void onInitialize();

	void onDeinitialize();

	void onUpdate(double time_diff);

private:

	//dt::MeshComponent mMesh; 

};





#endif