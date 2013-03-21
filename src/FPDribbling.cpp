#include "FieldPlayerState.h"
#include "Team.h"
#include "Goal.h"
#include "ParamLoader.h"
#include "Utils.h"


// Dribbling
Dribbling* Dribbling::get()
{
	static Dribbling instance;
	return &instance;
}

void Dribbling::enter(FieldPlayer* player)
{
}

//DEBUG_MODE_SETUP

void Dribbling::execute(FieldPlayer* player)
{
	float dot = player->getHeading().dotProduct(player->getTeam()->getGoal()->getFacing());

	// If the goal is behind this player
	if (dot < 0)
	{
		Ogre::Vector3 direction = player->getRotation() * Ogre::Quaternion(Ogre::Radian(-PI / 3), Ogre::Vector3(0, 1, 0))
			* Ogre::Vector3(0, 0, 1);

		player->getBall()->kick(direction, 3);
	}
	else 
	{
		// Detect if player in dangerous situation
		Ogre::Vector3 towards_goal = player->getTeam()->getOpponent()->getGoal()->getCenter() - player->getPosition();
		player->getBall()->kick(towards_goal, Prm.DribblingForce);
	}

	player->getStateMachine()->changeState(ChasingBall::get());
}

void Dribbling::exit(FieldPlayer*)
{

}

bool Dribbling::onMessage(FieldPlayer*, const Message&)
{
	return false;
}