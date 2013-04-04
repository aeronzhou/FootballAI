#include "Pitch.h"
#include "Player.h"
#include "Team.h"
#include "Region.h"
#include "Goal.h"
#include "ParamLoader.h"
#include "Utils.h"

#include "GeometryHelper.h"

#include <Utils/Random.hpp>
#include <Scene/Scene.hpp>
#include <Physics/PhysicsBodyComponent.hpp>

#include <OgreProcedural.h>
#include <OgreManualObject.h>

Pitch::Pitch(const QString name /* = "Pitch" */)
	: dt::Node(name) {}

Ogre::ManualObject* circle;

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
	mBall->testTimeSpentByInitialForce(15, 10);
#endif

	_updatePlayerRangeDrawer();
	_updatePlayerTargetDrawer();
	_updatePlayerPassSafeRange();

	// Test if the ball is scored!!!
	// Set team to kick off and send players back to origin region

	Node::onUpdate(time_diff);
}

void AddPitchWall(dt::Node* parent, QString name, QString mesh_handle, Ogre::Vector3 position, Ogre::Vector3 heading)
{
	dt::Node* wall = parent->addChildNode(new dt::Node(name)).get();
	wall->setPosition(position);
	wall->setRotation(GetRotationThroughHeading(heading));
	wall->addComponent(new dt::MeshComponent(mesh_handle, "PitchWall", MESH_COMPONENT));
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

	// Create Drawer
	mSceneNode =  getScene()->getSceneManager()->getRootSceneNode()->createChildSceneNode("ObjectDrawer");
	mPlayerRangeDrawer = addComponent(new CircleDrawerComponent("PlayerRange", "BaseWhite",
		Prm.PlayerThreatenedRange, 0.1, mSceneNode));
	mPlayerTargetDrawer = addComponent(new CircleDrawerComponent("PlayerTarget", "PlayerTarget", 0.7f, 0.25f, mSceneNode));
	
	// Array of pass safe range
	Ogre::Vector3 pass_safe_array[4] = {
		Ogre::Vector3(-0.6, 0, 0), 
		Ogre::Vector3(-Prm.PlayerPassSafeRangeWidth, 0, Prm.PlayerPassSafeRangeLength),
		Ogre::Vector3(Prm.PlayerPassSafeRangeWidth, 0, Prm.PlayerPassSafeRangeLength), 
		Ogre::Vector3(0.6, 0, 0)
	};
	mPassSafePolygon = std::vector<Ogre::Vector3>(pass_safe_array, pass_safe_array + 4);
	mPlayerPassSafeDrawer = addComponent(new PolygonDrawerComponent("PassSafe", mPassSafePolygon, 0.08f, "PlayerTarget", mSceneNode));

	if (!Prm.ShowPlayerRange)
		mPlayerRangeDrawer->disable();
	if (!Prm.ShowPlayerTarget)
		mPlayerTargetDrawer->disable();
	if (!Prm.ShowPassSafeDetectRange)
		mPlayerPassSafeDrawer->disable();

	// Create regions
	mPlayingArea = new Region(-Prm.HalfPitchWidth, -Prm.HalfPitchHeight, Prm.HalfPitchWidth, Prm.HalfPitchHeight, -1, Prm.PitchMargin);	
	mRegions.resize(Prm.NumRegionsHorizontal * Prm.NumRegionsVertical);
	_createRegions(Prm.HalfPitchWidth * 2 / Prm.NumRegionsHorizontal, Prm.HalfPitchHeight * 2 / Prm.NumRegionsVertical);

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
	setTeamToKickOff(mRedTeam);

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

	// Start the game
	mGameOn = true;
	mGoalKeeperHasBall = false;
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

Region* Pitch::getRegionByIndex(int index)
{
	return mRegions[index];
}

int Pitch::getRegionIndexByPosition(const Ogre::Vector3& position)
{
	int n = (position.z - mPlayingArea->getTop()) / (2 * Prm.HalfPitchHeight / Prm.NumRegionsVertical);
	int m = (position.x - mPlayingArea->getLeft()) / (2 * Prm.HalfPitchWidth / Prm.NumRegionsHorizontal);
	return n * Prm.NumRegionsHorizontal + m;
}

Region* Pitch::getPlayingArea() const
{
	return mPlayingArea;
}

void Pitch::_createRegions(float width, float height)
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

void Pitch::_updatePlayerRangeDrawer()
{
	if (mRedTeam->isInControl())
	{
		mPlayerRangeDrawer->setPos(mRedTeam->getControllingPlayer()->getPosition());
	}
	else if (mBlueTeam->isInControl())
	{
		mPlayerRangeDrawer->setPos(mBlueTeam->getControllingPlayer()->getPosition());
	}
	else 
	{
		mPlayerRangeDrawer->setPos(mBall->getPosition());
	}
}

void Pitch::_updatePlayerTargetDrawer()
{
	if (mRedTeam->isInControl())
	{
		mPlayerTargetDrawer->setPos(mRedTeam->getControllingPlayer()->getTarget());
	}
	else if (mBlueTeam->isInControl())
	{
		mPlayerTargetDrawer->setPos(mBlueTeam->getControllingPlayer()->getTarget());
	}
	else 
	{
		mPlayerTargetDrawer->setPos(mBall->getPosition());
	}
}

void Pitch::_updatePlayerPassSafeRange()
{
	if (mRedTeam->isInControl())
	{
		mPlayerPassSafeDrawer->setPos(mRedTeam->getControllingPlayer()->getPosition());
		mPlayerPassSafeDrawer->setRotation(mRedTeam->getControllingPlayer()->getRotation());
	}
	else if (mBlueTeam->isInControl())
	{
		mPlayerPassSafeDrawer->setPos(mBlueTeam->getControllingPlayer()->getPosition());
		mPlayerPassSafeDrawer->setRotation(mBlueTeam->getControllingPlayer()->getRotation());
	}
	else 
	{
		mPlayerPassSafeDrawer->setPos(Ogre::Vector3::ZERO);
	}
}


const std::vector<Region*>& Pitch::getAllRegions() const 
{
	return mRegions;
}

bool Pitch::isGameOn() const 
{
	return mGameOn;
}

void Pitch::setGameOn(bool flag)
{
	mGameOn = flag;
}

void Pitch::setTeamToKickOff(Team* team)
{
	mTeamToKickOff = team;
}

bool Pitch::isGoingForKickingOff(Team* team)
{
	return mTeamToKickOff == team;
}

bool Pitch::isGoalKeeperHasBall() const 
{
	return mGoalKeeperHasBall;
}

void Pitch::setGoalKeeperHasBall(bool flag)
{
	mGoalKeeperHasBall = flag;
}

Ogre::SceneNode* Pitch::getSceneNode() const 
{
	return mSceneNode;
}

const std::vector<Ogre::Vector3>& Pitch::getPassSafePolygon()
{
	return mPassSafePolygon;
}