#include "FieldPlayerState.h"
#include "Team.h"
#include "Goal.h"


// Dribbling
Dribbling* Dribbling::get()
{
	static Dribbling instance;
	return &instance;
}

void Dribbling::enter(FieldPlayer* player)
{
}

void Dribbling::execute(FieldPlayer* player)
{
	Ogre::Vector3 towards_goal = player->getTeam()->getGoal()->getCenter() - player->getPosition();
	float dot = player->getHeading().dotProduct(towards_goal);

	// If the goal is behind this player
	if (dot < 0)
	{
		Ogre::Vector3 direction = player->getRotation() * Ogre::Quaternion(Ogre::Radian(0.2), Ogre::Vector3(0, 1, 0))
			* Ogre::Vector3(0, 0, 1);

		player->getBall()->kick(towards_goal, 0.2);

		std::cout << "Turn Left!!!" << std::endl;
	}
	else 
	{
		// Detect if player in dangerous situation
		player->getBall()->kick(towards_goal, 0.5);

		std::cout << "Go ONNNNNN!!!!!" << std::endl;
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