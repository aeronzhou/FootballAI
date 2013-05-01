#include "GAChromosome.h"

Chromosome::Chromosome() : mScore(0)
{
	mGeneme.resize(GENEMESIZE);
}

Chromosome::Chromosome(const std::vector<Genetype>& geneme) : mScore(0), mGeneme(geneme)
{
}

const std::vector<Genetype>& Chromosome::getGeneme() const
{
	return mGeneme;
}

void Chromosome::setGeneme(const std::vector<Genetype>& geneme)
{
	mGeneme = geneme;
}

void Chromosome::setScore(int score)
{
	mScore = score;
}

int Chromosome::getScore() const
{
	return mScore;
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


/*
bool Chromosome::operator>(const Chromosome& ch2) const
{
	return mScore > ch2.mScore;
}

bool Chromosome::operator<(const Chromosome& ch2) const
{
	return mScore < ch2.mScore;
}*/

/*
bool operator>(Chromosome* ch1, Chromosome* ch2)
{
	return ch1->getScore() > ch2->getScore();
}

bool operator<(Chromosome* ch1, Chromosome* ch2)
{
	return ch1->getScore() < ch2->getScore();
}*/


