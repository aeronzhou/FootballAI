#ifndef FOOTBALL_AI_PITCH
#define FOOTBALL_AI_PITCH

#include "Ball.h"

#include <Scene/Node.hpp>
#include <Graphics/MeshComponent.hpp>



class Pitch : public dt::Node {
	Q_OBJECT

public:
	Pitch(const QString name = "Pitch");

	void onInitialize();

	void onDeinitialize();

	void onUpdate(double time_diff);

private:

	//dt::MeshComponent mMesh; 

	Ball* mBall;              //!< Pointer to the ball

};





#endif