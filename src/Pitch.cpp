#include "Pitch.h"
#include "Player.h"
#include "Team.h"
#include "Region.h"
#include "Goal.h"
#include "ParamLoader.h"
#include "FieldPlayer.h"//////////////////////////////////////////////////////////////////////////
#include <Physics/PhysicsBodyComponent.hpp>

#include <OgreProcedural.h>


Pitch::Pitch(const QString name /* = "Pitch" */)
	: dt::Node(name) {}

void Pitch::onUpdate(double time_diff) 
{
	this->mIsUpdatingAfterChange = (time_diff == 0);

	// Update State Machine
	//////////////////////////////////////////////////////////////////////////

	Node::onUpdate(time_diff);
}

void Pitch::onInitialize() 
{
	// Initialize global param loader
	ParamLoader* p = ParamLoader::get();

	// Realize a plane 
	OgreProcedural::PlaneGenerator().setSizeX(Prm.HalfPitchHeight * 2).setSizeY(Prm.HalfPitchWidth * 2).setUTile(1.0).setVTile(1.0).realizeMesh("PlayGround");
	auto play_ground_node = this->addChildNode(new dt::Node("PlayGround"));
	play_ground_node->addComponent(new dt::MeshComponent("PlayGround", "PrimitivesTest/Pebbles", "PlayGroundMesh"));
	play_ground_node->addComponent(new dt::PhysicsBodyComponent("PlayGroundMesh", "PlayGroundBody",
		dt::PhysicsBodyComponent::CONVEX, 0.0f));

	// Create regions
	mPlayGround = new Region(-Prm.HalfPitchWidth, -Prm.HalfPitchHeight, Prm.HalfPitchWidth, Prm.HalfPitchHeight);	
	mRegions.resize(Prm.NumRegionsHorizontal * Prm.NumRegionsVertical);
	createRegions(Prm.HalfPitchWidth * 2 / Prm.NumRegionsHorizontal, Prm.HalfPitchHeight * 2 / Prm.NumRegionsVertical);

	// Realize a ball
	OgreProcedural::SphereGenerator().setRadius(Prm.BallRadius).setUTile(.8f).realizeMesh("Football");
	mBall = (Ball*)addChildNode(new Ball("Football", "Football", "")).get();
	mBall->setPosition(0, 3, -2);
	mBall->resetPhysicsBody();

	// Create goals
	mRedGoal = (Goal*)addChildNode(new Goal("RedGoal", 
											Ogre::Vector3(-Prm.HalfPitchWidth, 0, -Prm.HalfGoalWidth), 
											Ogre::Vector3(-Prm.HalfPitchWidth, 0, Prm.HalfGoalWidth), 
											Ogre::Vector3(1.f, 0.f, 0.f), mBall)).get();
	mRedGoal->setPosition(-Prm.HalfPitchWidth, 0.5, 0);
	mRedGoal->resetPhysicsBody();

	mBlueGoal = (Goal*)addChildNode(new Goal("BlueGoal",
											 Ogre::Vector3(Prm.HalfPitchWidth, 0, Prm.HalfGoalWidth), 
											 Ogre::Vector3(Prm.HalfPitchWidth, 0, -Prm.HalfGoalWidth), 
											 Ogre::Vector3(-1.f, 0.f, 0.f), mBall)).get();
	mBlueGoal->setPosition(Prm.HalfPitchWidth, 0.5, 0);
	mBlueGoal->resetPhysicsBody();

	// CreatPlayerFlag
	OgreProcedural::SphereGenerator().setRadius(0.8f).realizeMesh("PlayerFlag");
									
	// Create Team: Red team at the left side
	mRedTeam = (Team*)addChildNode(new Team(mBall, this, Team::RED, mRedGoal)).get();
	mBlueTeam = (Team*)addChildNode(new Team(mBall, this, Team::BLUE, mBlueGoal)).get();
	mRedTeam->setOpponent(mBlueTeam);
	mBlueTeam->setOpponent(mRedTeam);
}

void Pitch::onDeinitialize() 
{
	// Avoid naked pointers
	delete mPlayGround;

	for (auto it = mRegions.begin(); it != mRegions.end(); ++it)
		delete(*it);

}

Ball* Pitch::getBall() const 
{
	return mBall;
}

Region* Pitch::getRegionFromIndex(int index)
{
	return mRegions[index];
}

Region* Pitch::getPlayingArea() const
{
	return mPlayGround;
}

void Pitch::createRegions(float width, float height)
{
	int idx = 0;

	for (int i = 0; i < Prm.NumRegionsVertical; ++i)
	{
		for (int j = 0; j < Prm.NumRegionsHorizontal; ++j)
		{
			mRegions[idx] = new Region(mPlayGround->getLeft() + j * width, mPlayGround->getTop() + i * height,
				                       mPlayGround->getLeft() + j * width + width, mPlayGround->getTop() + i * height + height, idx);
			++idx;
		}
	}
}

