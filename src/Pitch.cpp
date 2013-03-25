#include "Pitch.h"
#include "Player.h"
#include "Team.h"
#include "Region.h"
#include "Goal.h"
#include "ParamLoader.h"
#include "Utils.h"

#include <Utils/Random.hpp>

#include <Physics/PhysicsBodyComponent.hpp>

#include <OgreProcedural.h>

Pitch::Pitch(const QString name /* = "Pitch" */)
	: dt::Node(name) {}

void Pitch::onUpdate(double time_diff) 
{
	this->mIsUpdatingAfterChange = (time_diff == 0);

#define TEST_BALL_TIME_SPENT 0
#if	TEST_BALL_TIME_SPENT
	static bool test_ball = true; 
	if (test_ball)
	{
		test_ball = false;
		std::cout << "Ball cover time = " << mBall->getTimeToGoThroughDistance(3, 4) << std::endl;		
	}
	mBall->testTimeSpentByInitialForce(3, 4);
#endif

	Node::onUpdate(time_diff);
}

void AddPitchWall(dt::Node* parent, QString name, QString mesh_handle, Ogre::Vector3 position, Ogre::Vector3 heading)
{
	dt::Node* wall = parent->addChildNode(new dt::Node(name)).get();
	wall->setPosition(position);
	wall->setRotation(GetRotationThroughHeading(heading));

	wall->addComponent(new dt::MeshComponent(mesh_handle, "", MESH_COMPONENT));
	wall->addComponent(new dt::PhysicsBodyComponent(MESH_COMPONENT, PHYSICS_BODY_COMPONENT, dt::PhysicsBodyComponent::BOX, 0.0f));
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
		dt::PhysicsBodyComponent::BOX, 0.0f));

	// Create regions
	mPlayingArea = new Region(-Prm.HalfPitchWidth, -Prm.HalfPitchHeight, Prm.HalfPitchWidth, Prm.HalfPitchHeight, -1, Prm.PitchMargin);	
	mRegions.resize(Prm.NumRegionsHorizontal * Prm.NumRegionsVertical);
	createRegions(Prm.HalfPitchWidth * 2 / Prm.NumRegionsHorizontal, Prm.HalfPitchHeight * 2 / Prm.NumRegionsVertical);

	// Realize a ball
	OgreProcedural::SphereGenerator().setRadius(Prm.BallRadius).setUTile(.8f).realizeMesh("Football");
	mBall = (Ball*)addChildNode(new Ball("Football", "Football", "PlayerFlagBlue")).get();
	mBall->setPosition(Prm.BallPosX, 1, Prm.BallPosZ);
	mBall->resetPhysicsBody();

	// Create goals
	OgreProcedural::BoxGenerator().setSize(Ogre::Vector3(0.5, 2, 5)).realizeMesh("Goal");
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

	// Create evil walls... -_-|||
	// That is because we don't let foul-ball exists..
	OgreProcedural::BoxGenerator().setSize(Ogre::Vector3(Prm.HalfPitchWidth * 2, 1, 0.2)).realizeMesh("Wall_Horizonal");
	OgreProcedural::BoxGenerator().setSize(Ogre::Vector3(Prm.HalfPitchHeight * 2, 1, 0.2)).realizeMesh("Wall_Vertical");
	AddPitchWall(this, "Wall_Up", "Wall_Horizonal", Ogre::Vector3(0, 0, -Prm.HalfPitchHeight), Ogre::Vector3(0, 0, 1));
	AddPitchWall(this, "Wall_Down", "Wall_Horizonal", Ogre::Vector3(0, 0, Prm.HalfPitchHeight), Ogre::Vector3(0, 0, -1));
	AddPitchWall(this, "Wall_Left", "Wall_Vertical", Ogre::Vector3(-Prm.HalfPitchWidth, 0, 0), Ogre::Vector3(1, 0, 0));
	AddPitchWall(this, "Wall_Right", "Wall_Vertical", Ogre::Vector3(Prm.HalfPitchWidth, 0, 0), Ogre::Vector3(-1, 0, 0));

	// Initialize Random Value
	dt::Random::initialize();
}

void Pitch::onDeinitialize() 
{
	// Avoid naked pointers
	delete mPlayingArea;

	for (auto it = mRegions.begin(); it != mRegions.end(); ++it)
	{
		delete(*it);
	}
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
	return mPlayingArea;
}

void Pitch::createRegions(float width, float height)
{
	int idx = 0;

	for (int i = 0; i < Prm.NumRegionsVertical; ++i)
	{
		for (int j = 0; j < Prm.NumRegionsHorizontal; ++j)
		{
			mRegions[idx] = new Region(mPlayingArea->getLeft() + j * width, mPlayingArea->getTop() + i * height,
				                       mPlayingArea->getLeft() + j * width + width, mPlayingArea->getTop() + i * height + height, idx);
			++idx;
		}
	}
}

