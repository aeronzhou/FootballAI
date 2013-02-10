#include "Pitch.h"
#include "Player.h"
#include "Team.h"

#include <Physics/PhysicsBodyComponent.hpp>

#include <OgreProcedural.h>

Pitch::Pitch(const QString name /* = "Pitch" */)
	: dt::Node(name),
	  mGoalKeeperHasBall(false) {}

void Pitch::onUpdate(double time_diff) 
{
	Node::onUpdate(time_diff);
	//dt::Logger::get().error("shi***************t\n");
}

void Pitch::onInitialize() 
{
	// Realize a mesh 
	OgreProcedural::PlaneGenerator().setSizeX(13.6f).setSizeY(21.0f).setUTile(1.0).setVTile(1.0).realizeMesh("Plane");
	auto plane_node = this->addChildNode(new dt::Node("planenode"));
	plane_node->addComponent(new dt::MeshComponent("Plane", "PrimitivesTest/Pebbles", "plane-mesh"));
	plane_node->addComponent(new dt::PhysicsBodyComponent("plane-mesh", "plane-body",
		dt::PhysicsBodyComponent::CONVEX, 0.0f));

	// Initialize the ball
	mBall = new Ball("Ball.mesh");
	mBall->setPosition(0, 10, 0);
	addChildNode(mBall);	

	auto red_team = new Team(mBall, this, Team::RED);
	auto player = new Player("zehong", 1.0f, 12.f, Ogre::Vector3::ZERO, 12.0f, 70.f, 5.f, "Sinbad.mesh", "", red_team);
}

void Pitch::onDeinitialize() 
{

}

bool Pitch::getGoalKeeperHasBall() const
{
	return mGoalKeeperHasBall;
}

void Pitch::setGoalKeeperHasBall(bool flag)
{
	mGoalKeeperHasBall = flag;
}


