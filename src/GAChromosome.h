#ifndef FOOTBALL_AI_GA_CHROMOSOME
#define FOOTBALL_AI_GA_CHROMOSOME

#include <vector>


typedef int Genetype;

#define GENEMESIZE 6

class Chromosome
{
public:

	Chromosome();

	Chromosome(const std::vector<Genetype>& geneme);

	const std::vector<Genetype>& getGeneme() const;

	void setGeneme(const std::vector<Genetype>& geneme);

	void setScore(int score);

	int getScore() const;

	/** 
	  * two parents intercross to make two new children
	  * @param p1 parent geneme 1
	  * @param p2 parent geneme 2
	  * @param c1 child geneme 1
	  * @param c2 child geneme 2
	  */
	friend void getIntercross(const Chromosome& parent1, const Chromosome& parent2,
		Chromosome& child1, Chromosome& child2);

	friend void getAgamogenesis(const Chromosome& parent, Chromosome& child);

	friend void getMutant(const Chromosome& parent, Chromosome& child);

/*
	bool operator>(const Chromosome& ch2) const;
	bool operator<(const Chromosome& ch2) const;*/
/*
	friend bool operator>(Chromosome* ch1, Chromosome* ch2);
	friend bool operator<(Chromosome* ch1, Chromosome* ch2);*/
	friend class GT;


protected:

	std::vector<Genetype> mGeneme;						//!< geneme made of a list of unsigned int
	int mScore;	

};

class GT
{
public:
	inline bool operator()(const Chromosome* c1, const Chromosome* c2) const
	{
		return c1->mScore > c2->mScore;
	}
};


#endif