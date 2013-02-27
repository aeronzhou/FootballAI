#include "EntityManager.h"
#include "FieldPlayer.h"
#include "GoalKeeper.h"

EntityManager EntityManager::get()
{
	static EntityManager instance;
	return instance;
}

EntityManager::EntityManager()
{
	readFile("FieldPlayer.xml", mFieldPlayer);
	readFile("GoalKeeper.xml", mGoalKeeper);
}

FieldPlayer* EntityManager::createFieldPlayer(const QString& name, 
											  Team* team, 
											  FieldPlayer::PlayerRole role,
											  int home_region)
{
	//FieldPlayer* player = new FieldPlayer(name,
	//									  mFieldPlayer["BoundingRadius"].toFloat(),
	//									  mFieldPlayer["MaxSpeed"].toFloat(),
	//									  mFieldPlayer["MaxForce"]
	//									  );
	return nullptr;
}