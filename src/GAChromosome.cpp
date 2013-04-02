#include "GAChromosome.h"

Chromosome::Chromosome() 
{
}

const std::vector<Genetype>& Chromosome::getGeneme() const
{
	return mGeneme;
}

void Chromosome::setScore(int score)
{
	mScore = score;
}

void getIntercross(const Chromosome& parent1, const Chromosome& parent2,
	Chromosome& child1, Chromosome& child2)
{
	unsigned int geneme_len = parent1.mGeneme.size();
	unsigned int intercross_point = rand() % geneme_len;
	unsigned i = 0;
	for(;i < intercross_point; ++i)
	{
		child1.mGeneme[i] = parent1.mGeneme[i];
		child2.mGeneme[i] = parent2.mGeneme[i];
	}
	for(;i < geneme_len; ++i)
	{
		child1.mGeneme[i] = parent2.mGeneme[i];
		child2.mGeneme[i] = parent1.mGeneme[i];
	}
}

void getAgamogenesis(const Chromosome& parent, Chromosome& child)
{
	child.mGeneme = parent.mGeneme;
}

void getMutant(const Chromosome& parent, Chromosome& child)
{
	unsigned int geneme_len = parent.mGeneme.size();
	unsigned int mutant_point = rand() % geneme_len;
	Genetype new_geneme = rand() % 18;
	child.mGeneme = parent.mGeneme;
	child.mGeneme[mutant_point] = new_geneme;
}


bool Chromosome::operator>(const Chromosome& ch2) const
{
	return mScore > ch2.mScore;
}

bool Chromosome::operator<(const Chromosome& ch2) const
{
	return mScore < ch2.mScore;
}

