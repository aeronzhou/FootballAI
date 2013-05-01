#include "GAPopulation.h"
#include "GAChromosome.h"
#include "ParamLoader.h"
#include  <algorithm>


Population::~Population()
{
	release();
}

void Population::release()
{
	for(unsigned int i = 0; i < mColonySize; ++i)
		delete (mColony[i]);
	mBestGeneme.clear();
}

void Population::Initial(unsigned int colony_size, double intercross_rate, 
	double agamogenesis_rate, double mutant_rate)
{
	mColonySize			= colony_size;
	mIntercrossRate		= intercross_rate;
	mAgamogenesisRate	= agamogenesis_rate;
	mMutantRate			= mutant_rate;

	std::vector<Genetype> init_geneme;
	init_geneme.resize(GENEMESIZE);
	unsigned int resign_size = Prm.NumRegionsHorizontal * Prm.NumRegionsVertical;
	mColony.resize(mColonySize);
	for(unsigned int i = 0; i < mColonySize; ++i)
	{
		for(unsigned int j = 0; j < GENEMESIZE; ++j)
			init_geneme[j] = rand() % resign_size;
		Chromosome* p_new_gene = new Chromosome(init_geneme);
		mColony[i] = p_new_gene;
	}
}

void Population::nextGeneration()
{
	onIntercross();
	std::cout << "\nAfter Intercrose Popu Size: " << getPopulationSize() << "\n";
	onAgamogenesis();
	std::cout << "\nAfter Agamogene Popu Size: " << getPopulationSize() << "\n";
	onMutant();
	std::cout << "\nAfter Mutant Popu Size: " << getPopulationSize() << "\n";
}

void Population::keepColonySize(unsigned int size)
{
	sort(mColony.begin(), mColony.end(),GT());
	std::vector<Chromosome*> new_colony;
	new_colony.insert(new_colony.end(), mColony.begin(), mColony.begin()+100);
	mColony.clear();
	mColony = new_colony;;
	mBestGeneme = mColony[0]->getGeneme();
}

unsigned int Population::getPopulationSize()
{
	return mColony.size();
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
void Population::onIntercross()
{
	unsigned int intercross_times = mColony.size() * mIntercrossRate;
	unsigned int population_size = 0;
	for (unsigned int i = 0; i < intercross_times; ++i)
	{
		population_size = mColony.size();
		unsigned int chromo_idx1 = rand() % population_size;
		unsigned int chromo_idx2 = rand() % population_size;
		if(chromo_idx1 == chromo_idx2)
		{
			++chromo_idx2;
			chromo_idx2 = (chromo_idx2 + 1) % population_size;
		}
		Chromosome* chromo1 = new Chromosome();
		Chromosome* chromo2 = new Chromosome();
		getIntercross(*mColony[chromo_idx2], *mColony[chromo_idx2], *chromo1, *chromo2);
		mColony.push_back(chromo1);
		mColony.push_back(chromo2);
	}
}

void Population::onAgamogenesis()
{
	unsigned int agamogenesis_times = mColony.size() * mAgamogenesisRate;
	for (unsigned int i = 0; i < agamogenesis_times; ++i)
	{
		unsigned int chromo_idx = rand() % mColony.size();
		Chromosome* new_chromo = new Chromosome();
		getAgamogenesis(*mColony[chromo_idx], *new_chromo);
		mColony.push_back(new_chromo);

	}
}

void Population::onMutant()
{
	unsigned int mutant_times = mColony.size() * mMutantRate;
	for (unsigned int i = 0; i < mutant_times; ++i)
	{
		unsigned int chromo_idx = rand() % mColony.size();
		Chromosome* new_chromo = new Chromosome;
		getMutant(*mColony[chromo_idx], *new_chromo);
		mColony.push_back(new_chromo);
	}
}