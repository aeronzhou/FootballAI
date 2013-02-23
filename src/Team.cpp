#include "Team.h"
#include "Ball.h"
#include "Pitch.h"
#include "Player.h"

Team::Team(Ball* ball, Pitch* pitch, TeamColor color)
	: mBall(ball), mPitch(pitch), mColor(color),
	  mOpponent(nullptr), mControllingPlayer(nullptr), mSupportingPlayer(nullptr), 
	  mReceivingPlayer(nullptr), mPlayerClosestToBall(nullptr), mPlayers(std::vector<Player*>()) {}


void Team::onInitialize() 
{
	// Setup state machine
	//////////////////////////////////////////////////////////////////////////

	// Initialize players
	createPlayers();

	for (auto it = mPlayers.begin(); it != mPlayers.end(); ++it)
	{
		addChildNode(*it);
		
		// Set position by region
		(*it)->setPosition(5, 4, 0);
		(*it)->setScale(0.2);
		(*it)->resetPhysicsBody();
	}

}

void Team::onUpdate(double time_diff)
{
	this->mIsUpdatingAfterChange = (time_diff == 0);

	dt::Node::onUpdate(time_diff);
}

void Team::createPlayers()
{
	if (getTeamColor() == RED)
	{
		mPlayers.push_back(new Player("blue_attack_01", 
			1.0f, 
			10.0f, 
			Ogre::Vector3(1.f, 0.f, 0.f), 
			20.f, 
			50.f, 
			0.1f, 
			"Sinbad.mesh", 
			"",
			this));
	}
	else 
	{

	}
}