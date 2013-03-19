#include "PlayerManager.h"
#include "FieldPlayer.h"
#include "GoalKeeper.h"
#include "Team.h"

std::vector<Player*> PlayerManager::mAllMembers;

PlayerManager PlayerManager::get()
{
	static PlayerManager instance;
	return instance;
}

PlayerManager::PlayerManager()
{
	if (!readFile("./../data/xml/FieldPlayer.xml", mFieldPlayer))
		dt::Logger::get().error("Read FieldPlayer.xml failed!!!");

	if (!readFile("./../data/xml/GoalKeeper.xml", mGoalKeeper))
		dt::Logger::get().error("Read GoalKeeper.xml failed!!!");

	mAllMembers.clear();
}

FieldPlayer* PlayerManager::createFieldPlayer(const QString& name, 
											  Team* team, 
											  FieldPlayer::PlayerRole role,
											  int assigned_region)
{
	QString mesh_handle = mFieldPlayer["RedMeshHandle"];

	if (team->getTeamColor() == Team::BLUE)
	{
		mesh_handle = mFieldPlayer["BlueMeshHandle"];
	}

	FieldPlayer* player = new FieldPlayer(name,
										  mFieldPlayer["ControlRange"].toFloat(),
										  mFieldPlayer["MaxSpeed"].toFloat(),
										  mFieldPlayer["MaxForce"].toFloat(),
										  mFieldPlayer["Mass"].toFloat(),
										  mFieldPlayer["TurnRate"].toFloat(),
										  mesh_handle,
										  mFieldPlayer["MaterialHandle"],
										  team,
										  assigned_region,
										  role
										  );

	mAllMembers.push_back((Player*)player);

	return player;
}

GoalKeeper* PlayerManager::createGoalKeeper(const QString& name, 
											Team* team, 
											int assigned_region)
{
	
	QString mesh_handle = mFieldPlayer["RedMeshHandle"];

	if (team->getTeamColor() == Team::BLUE)
	{
		mesh_handle = mFieldPlayer["BlueMeshHandle"];
	}

	GoalKeeper* player = new GoalKeeper(name,
									    mFieldPlayer["ControlRange"].toFloat(), 
										mFieldPlayer["MaxSpeed"].toFloat(), 
										mFieldPlayer["MaxForce"].toFloat(), 
										mFieldPlayer["Mass"].toFloat(), 
										mFieldPlayer["TurnRate"].toFloat(), 
										mesh_handle, 
										mFieldPlayer["MaterialHandle"], 
										team, 
										assigned_region
										);
	mAllMembers.push_back(player);

	return player;
}

std::vector<Player*>& PlayerManager::getAllMembers() 
{
	return mAllMembers;
}

