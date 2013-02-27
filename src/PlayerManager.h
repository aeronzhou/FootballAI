#ifndef FOOTBALL_AI_PLAYER_MANAGER
#define FOOTBALL_AI_PLAYER_MANAGER

#include "ParamLoaderBase.h"
#include "FieldPlayer.h"
#include "GoalKeeper.h"

class Team;

/** 
  * This is a class to manage players
  * include FieldPlayers and GoalKeepers
  */
class PlayerManager : public ParamLoaderBase
{
public:

	static PlayerManager get();

	/** 
	  * Constructor
	  * Initialize FieldPlayer and GoalKeeper param table
	  */
	PlayerManager();

	/** 
	  * Create a field player
	  * @name Name of this player
	  * @team Team this player belongs to
	  * @role Attacker of defender
	  * @home_region Home region this player belongs to
	  */
	FieldPlayer* createFieldPlayer(const QString& name, 
								   Team* team,
								   FieldPlayer::PlayerRole role,
								   int home_region);

	/** 
	  * Create a goal keeper
	  * @name Name of this player
	  * @team Team this player belongs to
	  * @home_region Home region this player belongs to
	  */
	GoalKeeper* createGoalKeeper(const QString& name,
								 Team* team,
								 int home_region);

protected:

	MSS mFieldPlayer;
	MSS mGoalKeeper;
	MSS mFootball;
};

#endif