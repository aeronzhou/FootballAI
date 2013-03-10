#ifndef FOOTBALL_AI_PLAYER_POSITION_MANAGER
#define FOOTBALL_AI_PLAYER_POSITION_MANAGER

#include <QString>

#include <vector>
#include <map>

class PlayerPositionManager
{
public:

	static PlayerPositionManager& get();

	std::vector<int> getOriginPosition(const QString& state_name);	

	PlayerPositionManager();

private:

	void printRegions();

	std::map<QString, std::vector<int> > mPositionMap;
};


#endif