#include "Pitch.h"
#include "Player.h"
#include "Team.h"
#include "Region.h"
#include "ParamLoader.h"

#include <Physics/PhysicsBodyComponent.hpp>

#include <OgreProcedural.h>

Pitch::Pitch(const QString name /* = "Pitch" */)
	: dt::Node(name),
	  mGoalKeeperHasBall(false) {}

void Pitch::onUpdate(double time_diff) 
{
	this->mIsUpdatingAfterChange = (time_diff == 0);

	Node::onUpdate(time_diff);
}

void Pitch::onInitialize() 
{
	// Realize a mesh 
	OgreProcedural::PlaneGenerator().setSizeX(Prm.HalfPitchHeight * 2).setSizeY(Prm.HalfPitchWidth * 2).setUTile(1.0).setVTile(1.0).realizeMesh("Plane");
	auto plane_node = this->addChildNode(new dt::Node("planenode"));
	plane_node->addComponent(new dt::MeshComponent("Plane", "PrimitivesTest/Pebbles", "plane-mesh"));
	plane_node->addComponent(new dt::PhysicsBodyComponent("plane-mesh", "plane-body",
		dt::PhysicsBodyComponent::CONVEX, 0.0f));

	// Realize a ball
	OgreProcedural::SphereGenerator().setRadius(0.3f).setUTile(.8f).realizeMesh("Football");
	mBall = (Ball*)addChildNode(new Ball("Football", "Football", "")).get();
	mBall->setPosition(0, 10, 0);
	mBall->resetPhysicsBody();

	// Create Red Team: at the left side
	mRedTeam = (Team*)addChildNode(new Team(mBall, this, Team::RED)).get();
	mBlueTeam = (Team*)addChildNode(new Team(mBall, this, Team::BLUE)).get();

	// Create regions
	
	mRegions.resize(Prm.NumRegionsHorizontal * Prm.NumRegionsVertical);
	//createRegions
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

bool Pitch::getGameOn() const
{
	return mGameOn;
}

void Pitch::setGameOn(bool flag)
{
	mGameOn = flag;
}

Region* Pitch::getRegionFromIndex(int index)
{
	return mRegions[index];
}

Region* Pitch::getPlayingArea() const
{
	return mPlayingArea;
}

void Pitch::createRegions(float width, float height)
{

}