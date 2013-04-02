#include "GAPopulation.h"
#include  <algorithm>


Population::Population(unsigned int colony_size, double intercross_rate,
	double agamogenesis_rate, double mutant_rate):
		mColonySize(colony_size),mIntercrossRate(intercross_rate),
		mAgamogenesisRate(agamogenesis_rate), mMutantRate(mutant_rate)
{
}

void Population::release()
{
	mColony.clear();
	mBestGeneme.clear();
}

void Population::nextGeneration()
{
	onIntercross();
	onAgamogenesis();
	onMutant();
}

void Population::keepColonySize(unsigned int size)
{
	sort(mColony.begin(), mColony.end(),std::greater<Chromosome*>());
	std::vector<Chromosome*> new_colony;
	new_colony.insert(new_colony.end(), mColony.begin(), mColony.begin()+100);
	mColony.clear();
	mColony = new_colony;
	mBestGeneme = mColony[0]->getGeneme();
}

unsigned int Population::getPopulationSize()
{
	return mColonySize;
}

void Population::onIntercross()
{
	unsigned int intercross_times = mColonySize * mIntercrossRate;
	for (unsigned int i = 0; i < intercross_times; ++i)
	{
		unsigned int chromo_idx1 = rand() % mColonySize;
		unsigned int chromo_idx2 = rand() % mColonySize;
		if(chromo_idx1 == chromo_idx2)
		{
			++chromo_idx2;
			chromo_idx2 = (chromo_idx2 + 1) % mColonySize;
		}
		Chromosome* chromo1 = new Chromosome;
		Chromosome* chromo2 = new Chromosome;
		getIntercross(*mColony[chromo_idx2], *mColony[chromo_idx2], *chromo1, *chromo2);
		mColony.push_back(chromo1);
		mColony.push_back(chromo2);
	}
}

const std::vector<Chromosome*>& Population::getAllPopulation() const
{
	return mColony;
}

void Population::setGeneScoreByID(int id, int score)
{
	mColony[id]->setScore(score);
}

const std::vector<Genetype> Population::getBestGeneme() const
{
	return mBestGeneme;
}



/*friend function*/
void Population::onAgamogenesis()
{
	unsigned int agamogenesis_times = mColonySize * mAgamogenesisRate;
	for (unsigned int i = 0; i < agamogenesis_times; ++i)
	{
		std::vector<Chromosome*> new_colony = mColony;
		mColony.insert(mColony.end(), new_colony.begin(), new_colony.end());
	}
}

void Population::onMutant()
{
	unsigned int mutant_times = mColonySize * mMutantRate;
	for (unsigned int i = 0; i < mutant_times; ++i)
	{
		unsigned int chromo_idx = rand() % mColonySize;
		Chromosome* new_chromo = new Chromosome;
		getMutant(*mColony[chromo_idx], *new_chromo);
		mColony.push_back(new_chromo);
	}
}