#ifndef FOOTBALL_AI_GA_CHROMOSOME
#define FOOTBALL_AI_GA_CHROMOSOME

#include <vector>


typedef unsigned int Genetype;

class Chromosome
{
public:

	Chromosome();

	void onInitialize();

	void onDeinitialize();

	void onUpdate(double time_diff);

	const std::vector<Genetype>& getGeneme() const;

	void setScore(int score);

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

	bool operator>(const Chromosome& ch2) const;
	bool operator<(const Chromosome& ch2) const;



protected:

	std::vector<Genetype> mGeneme;						//!< geneme made of a list of unsigned int
	int mScore;	

};


#endif