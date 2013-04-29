#include "GAEnvironment.h"
#include "ParamLoader.h"
#include "Pitch.h"
#include "Team.h"
#include "Player.h"


Environment::Environment(const QString& name, Team* team, Pitch* pitch)
	: Node(name), mTeam(team), mPitch(pitch)
{
}

void Environment::onInitialize()
{
	mCoolingTime = addComponent(new CoolingTimeComponent(1.0f));
	mPopulatin;
	mOppGeneme;
}

void Environment::onDeinitialize()
{

}

void Environment::onUpdate(double time_diff)
{
	if(mCoolingTime->ready())
	{
		mOppGeneme;
		getBestGeneme();
	}
}


const std::vector<Genetype> Environment::getBestGeneme()
{
	for(unsigned int i = 0; i < Prm.GAGeneration; ++i)
	{
		mPopulatin.nextGeneration();
		unsigned int population_size = mPopulatin.getPopulationSize();
		for(unsigned int i = 0; i < population_size; ++i)
		{
			int score = Evaluate(mPopulatin.getAllPopulation()[i]->getGeneme());
			mPopulatin.setGeneScoreByID(i,score);
		}
		mPopulatin.keepColonySize(Prm.GAColonySize);
	}
	return mPopulatin.getBestGeneme();
}


int Environment::Evaluate(const std::vector<Genetype>& candidate)
{
	int result_value = 0;
	unsigned int gene_length = candidate.size();
	for(unsigned int i = 0; i < gene_length; ++i)
	{
		result_value -= mPitch->getAllRegions()[candidate[i]]->getCenter()
			.distance((mTeam->getPlayers()[i])->getPosition()) * Prm.GACrossCostPerRgn;
		result_value += getDefendValue(candidate[i],mOppGeneme);
		result_value += getAttackValue(candidate[i], mOppGeneme);
		if(mTeam->isInControl() && 
			mPitch->getRegionIndexByPosition(mPitch->getBall()->getPosition()) == candidate[i])
			result_value += Prm.GAPlayerKeepBallValue;
		else if (!mTeam->isInControl() &&
			mPitch->getRegionIndexByPosition(mPitch->getBall()->getPosition()) == candidate[i])
			result_value += Prm.GAPlayerChaseBallValue;
	}
	return result_value;
}

int Environment::getDefendValue(const int player_idx, const std::vector<Genetype>& opp_geneme)
{
	int result_value = 0;
	int opp_in_my_ground = 0;
	std::vector<Genetype>::const_iterator it = opp_geneme.begin();
	for(;it != opp_geneme.end(); ++it)
		if(isInMyGround(*it))
			++opp_in_my_ground;
	
	if(opp_in_my_ground > 1)
	{
		if(isInMyGround(player_idx))
			result_value += Prm.GAPlayerDefendValue;
		else
			result_value += Prm.GAPlayerDefendValue * 0.5;
	}
	else
		result_value += Prm.GAPlayerDefendValue * 0.8;
	if(mTeam->isInControl())
		result_value *= 1.2;
	else
		result_value *= 0.8;

	return result_value;
}

int Environment::getAttackValue(const int player_idx, const std::vector<Genetype>& opp_geneme)
{
	int result_value = 0;
	int opp_notin_my_ground = 0;
	std::vector<Genetype>::const_iterator it = opp_geneme.begin();
	for(;it != opp_geneme.end(); ++it)
		if(!isInMyGround(*it))
			++opp_notin_my_ground;

	if(opp_notin_my_ground > 2)
	{
		if(isInMyGround(player_idx))
			result_value += Prm.GAPlayerAttackValue * 0.5;
		else
			result_value += Prm.GAPlayerAttackValue;
	}
	if(mTeam->isInControl())
		result_value *= 1.2;
	else
		result_value *= 0.8;

	return result_value;
}

bool Environment::isInMyGround(unsigned int regin_idx)
{
	int tmp_idx = regin_idx % Prm.NumRegionsHorizontal;
	int diff = tmp_idx - Prm.NumRegionsHorizontal * 0.5;
	if(diff == 0)
		return true;
	else if(diff > 0)
	{
		if(mTeam->getTeamColor() == Team::RED)
			return false;
		else
			return true;
	}
	else
	{
		if(mTeam->getTeamColor() == Team::RED)
			return true;
		else
			return false;
	}
}