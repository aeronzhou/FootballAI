#ifndef FOOTBALL_AI_ENTITY_MANAGER
#define FOOTBALL_AI_ENTITY_MANAGER

#include "ParamLoaderBase.h"
#include "FieldPlayer.h"
#include "GoalKeeper.h"

class Team;

/** 
  * This is a class to manage players
  * include FieldPlayers and GoalKeepers
  */
class EntityManager : public ParamLoaderBase
{
public:

	static EntityManager get();

	/** 
	  * Constructor
	  * Initialize FieldPlayer and GoalKeeper param table
	  */
	EntityManager();

	/** 
	  * Create a field player
	  * @name Name of this player
	  */
	FieldPlayer* createFieldPlayer(const QString& name, 
								   Team* team,
								   FieldPlayer::PlayerRole role,
								   int home_region);

	/** 
	  * Create a goal keeper
	  */
	GoalKeeper* createGoalKeeper(const QString& name);

protected:

	MSS mFieldPlayer;
	MSS mGoalKeeper;
	MSS mFootball;
};

#endif