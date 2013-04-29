#ifndef FOOTBALL_AI_GA_POPULATION
#define FOOTBALL_AI_GA_POPULATION


#include "GAChromosome.h"


class Population
{
public:
	Population() {}

	~Population();

	void release();

	void Initial(unsigned int colone_size, double intercross_rate, 
		double agamogenesis_rate, double mutant_rate);

	void nextGeneration();

	void keepColonySize(unsigned int size = 100);

	unsigned int getPopulationSize();

	const std::vector<Chromosome*>& getAllPopulation() const;

	void setGeneScoreByID(int id, int score);

	const std::vector<Genetype> getBestGeneme() const;

	


private:
	void onIntercross();
	void onAgamogenesis();
	void onMutant();


private:
	std::vector<Chromosome*> mColony;
	unsigned int mColonySize;
	double mIntercrossRate, mAgamogenesisRate, mMutantRate;
	std::vector<Genetype> mBestGeneme;

};


#endif