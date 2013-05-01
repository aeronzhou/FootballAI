#ifndef FOOTBALL_AI_GA_ENVIRONMENT
#define FOOTBALL_AI_GA_ENVIRONMENT

#include "ParamLoader.h"
#include "GAPopulation.h"
#include "GAChromosome.h"
#include "CoolingTimeComponent.h"
#include <Scene/Node.hpp>

class Team;
class Pitch;

class Environment : public dt::Node
{
public:

	Environment(const QString& name, Team* team, Pitch* pitch);

	void onInitialize();

	void onDeinitialize();

	void onUpdate(double time_diff);

	const std::vector<Genetype> getBestGeneme();



protected:
	int Evaluate(const std::vector<Genetype>& candidate);

	int getDefendValue(const int player_idx, const std::vector<Genetype>& opp_geneme);

	int getAttackValue(const int player_idx, const std::vector<Genetype>& opp_geneme);

	int getDistanceValue(const int player_idx, const std::vector<Genetype>& candidate);

	bool isInMyGround(unsigned int regin_idx);


protected:
	Population mPopulatin;
	std::shared_ptr<CoolingTimeComponent> mCoolingTime;  //!< We should not calculate every single frame, so...
	std::vector<Genetype> mOppGeneme; 
	bool mIfInit;

	Team* mTeam;
	Pitch* mPitch;
};


#endif