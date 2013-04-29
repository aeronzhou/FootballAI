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

	// 如果这个时候球员背对着控球者，那么
	if (player->isAskedToTurnAround())
	{
		player->setIsAskedToTurnAround(false);
		Ogre::Vector3 target = player->getAskedTurnAroundTarget();
		// 踢一个角度
		Player* ctrPly = player->getTeam()->getControllingPlayer();
		Ogre::Radian angle = player->getHeading().getRotationTo(target - player->getPosition()).getYaw();
		if (angle > Ogre::Radian(0) || fabs(angle.valueRadians()) < 1e-3)
		{
			angle = std::min(PI / 3, angle.valueRadians());
		}
		else 
		{
			angle = std::min(-PI / 3, angle.valueRadians());
		}
	}

	// If the goal is behind this player
	if (dot < 0)
	{
		Ogre::Radian angle = player->getHeading().getRotationTo(player->getTeam()->getGoal()->getFacing()).getYaw();

		if (angle > Ogre::Radian(0) || fabs(angle.valueRadians()) < 1e-3)
		{
			angle = PI / 3;
		}
		else 
		{
			angle = -PI / 3;
		}

		Ogre::Vector3 direction = player->getRotation() * Ogre::Quaternion(angle, Ogre::Vector3(0, 1, 0)) * Ogre::Vector3(0, 0, 1);

		player->getBall()->kick(direction, Prm.PlayerTurnAroundForce);
	}
	else 
	{
		// Detect if player in dangerous situation
		Ogre::Vector3 towards_goal = player->getTeam()->getOpponent()->getGoal()->getCenter() - player->getPosition();
		player->getBall()->kick(towards_goal, Prm.PlayerDribblingForce);

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