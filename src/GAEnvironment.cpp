#include "GAEnvironment.h"
#include "ParamLoader.h"
#include "Pitch.h"
#include "Team.h"
#include "Goal.h"
#include "Player.h"
#include "FieldPlayer.h"
#include "FieldPlayerState.h"
#include "MessageDispatcher.h"
#include <iostream>

Environment::Environment(const QString& name, Team* team, Pitch* pitch)
	: Node(name), mTeam(team), mPitch(pitch), mIfInit(false)
{
}

void Environment::onInitialize()
{
	mCoolingTime = addComponent(new CoolingTimeComponent(1.5f));
}

void Environment::onDeinitialize()
{

}

void Environment::onUpdate(double time_diff)
{
	if(mCoolingTime->ready() && (mTeam->getTeamColor() == Team::RED))
	{
/*
		if(!mIfInit)
		{*/
		mPopulatin.Initial(Prm.GAColonySize, Prm.GAIntercrossRate, 
			Prm.GAAgamogenesisRate, Prm.GAMutantRate);
/*
			mIfInit = true;
		}*/
		std::cout<<"GA begin!\n";
		std::vector<Genetype> tmp_gene = mTeam->getOpponent()->getAssignedRegionIDs();
		mOppGeneme.assign(tmp_gene.begin(),tmp_gene.end()-1);
		unsigned int FPlayer_size = mOppGeneme.size();
		for(unsigned int i = 0; i < FPlayer_size; ++i)
			std::cout<<"\nmOppgeneme: "<<mOppGeneme[i]<<"\n";
		getBestGeneme();
		std::cout<<"GA finish"<<"\n";


		std::vector<int> assigned_ids(mTeam->getAssignedRegionIDs());
		for(unsigned int i = 0; i < FPlayer_size; ++i)
			std::cout << "\n--assignedID: " << assigned_ids[i] << "\n";

		unsigned int population_size = mPopulatin.getPopulationSize();
		for(unsigned int i = 0; i < population_size; ++i)
		{
			std::cout << "\n score: [" << i <<"] "<< mPopulatin.getAllPopulation()[i]->getScore() << "\n";
		}

		for(unsigned int i = 0; i < FPlayer_size; ++i)
			std::cout << "\nbestgene: " << mPopulatin.getBestGeneme()[i] << "\n";
		std::cout<<"--------------------------\n";

		for(unsigned int i = 0; i < FPlayer_size; ++i)
		{
			FieldPlayer* receiver = (FieldPlayer*)(mTeam->getPlayers()[i]);
			if (receiver->getStateMachine()->isInState(*Waiting::get()) ||
				receiver->getStateMachine()->isInState(*Positioning::get()) )
			{
				if(i == FPlayer_size-1)
				{
					if(mTeam->getOpponent()->isInControl() && isInMyGround(mPitch->getRegionIndexByPosition(mTeam->getOpponent()->
						getControllingPlayer()->getPosition())))
					{

						receiver->setAssignedRegion(mPopulatin.getBestGeneme()[i]);
						receiver->getStateMachine()->changeState(ChasingBall::get());
						continue;
					}
				}
				receiver->setAssignedRegion(mPopulatin.getBestGeneme()[i]);
				receiver->getStateMachine()->changeState(Positioning::get());
			}
		}
	}

	dt::Node::onUpdate(time_diff);
}


const std::vector<Genetype> Environment::getBestGeneme()
{
	for(unsigned int i = 0; i < Prm.GAGeneration; ++i)
	{
		mPopulatin.nextGeneration();
		unsigned int population_size = mPopulatin.getPopulationSize();
		std::cout << "\n populationSize: " << population_size << "\n";
		for(unsigned int i = 0; i < population_size; ++i)
		{
			int score = Evaluate(mPopulatin.getAllPopulation()[i]->getGeneme());
			mPopulatin.setGeneScoreByID(i,score);
		}
		mPopulatin.keepColonySize(Prm.GAColonySize);
		std::cout << "\n populationSize: " << mPopulatin.getPopulationSize() << "\n";
	}
	return mPopulatin.getBestGeneme();
}


int Environment::Evaluate(const std::vector<Genetype>& candidate)
{
	int result_value = 0;

	int tmp_distance1 = 0, tmp_distance2 = 0, tmp_distance3 = 0;
	Ogre::Vector3 tmp_center, tmp_postition;
	Ogre::Vector3 tmp_ballpos = mPitch->getBall()->getPosition();
	unsigned int gene_length = candidate.size();
	bool tmp_control = mTeam->isInControl();
	Ogre::Vector3 tmp_goalpos;

	if(tmp_control)
		tmp_goalpos = mTeam->getOpponent()->getGoal()->getPosition();
	else
		tmp_goalpos = mTeam->getGoal()->getPosition();

	for(unsigned int i = 0; i < gene_length; ++i)
	{
/*
		result_value -= mPitch->getAllRegions()[candidate[i]]->getCenter()
			.distance((mTeam->getPlayers()[i])->getPosition()) * Prm.GACrossCostPerRgn;
*/
		tmp_center = mPitch->getAllRegions()[candidate[i]]->getCenter();
		tmp_postition = (mTeam->getPlayers()[i])->getPosition();
		tmp_distance1 = tmp_center.squaredDistance(tmp_postition) * Prm.GACrossCostPerRgn;
		result_value -= tmp_distance1;

		if(i == gene_length-1)
			tmp_goalpos = mTeam->getGoal()->getPosition();
		tmp_distance2 = tmp_center.squaredDistance(tmp_ballpos);
		tmp_distance3 = tmp_center.squaredDistance(tmp_goalpos);
		if(i == gene_length-1)
			tmp_distance3 *= 3;
/*
		if(!tmp_control)
		{
			tmp_distance3 *= 1.2;
			tmp_distance2 *= 0.8;
		}*/

		
		result_value -= tmp_distance2 * Prm.GACrossCostPerRgn;
		result_value -= tmp_distance3 * Prm.GACrossCostPerRgn;
		/*std::cout<<"\nd1, d2,d3 "<<tmp_distance1<<"  "<<tmp_distance2<<" "<<tmp_distance3<<"\n";*/
		result_value += getDefendValue(candidate[i],mOppGeneme);
		result_value += getAttackValue(candidate[i], mOppGeneme);
		
/*
		if(mTeam->isInControl() && 
			mPitch->getRegionIndexByPosition(mPitch->getBall()->getPosition()) == candidate[i])
			result_value += Prm.GAPlayerKeepBallValue;

		else if (!mTeam->isInControl() &&
			mPitch->getRegionIndexByPosition(mPitch->getBall()->getPosition()) == candidate[i])
			result_value += Prm.GAPlayerChaseBallValue;*/
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
	if(opp_in_my_ground > 0)
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

	if(opp_notin_my_ground > 1)
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

int Environment::getDistanceValue(const int player_idx, const std::vector<Genetype>& candidate)
{
/*
	int result_value = 0;
	int opp_notin_my_ground = 0;
	std::vector<Genetype>::const_iterator it = candidate.begin();
	for(;it != candidate.end(); ++it)
		if(!isInMyGround(*it))
			++opp_notin_my_ground;

	tmp_center = mPitch->getAllRegions()[candidate[i]]->getCenter();
	tmp_postition = (mTeam->getPlayers()[i])->getPosition();
	tmp_distance1 = tmp_center.distance(tmp_postition) * Prm.GACrossCostPerRgn;
	result_value -= tmp_distance1;

	tmp_distance2 = tmp_center.distance(tmp_ballpos);
	tmp_distance3 = tmp_center.distance(tmp_goalpos);
	if(!tmp_control)
	{
		tmp_distance3 *= 1.3;
		tmp_distance2 *= 0.6;
	}

	result_value -= tmp_distance2 * Prm.GACrossCostPerRgn;
	result_value -= tmp_distance3 * Prm.GACrossCostPerRgn;*/

	return 0;
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