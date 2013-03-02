#ifndef FOOTBALL_AI_ILIST
#define FOOTBALL_AI_ILIST

#include <vector>

/** 
  * A list interface
  */
template <class T>
class IList
{
public:
	
	std::vector<T>& getAllMembers()
	{
		return mMembers;
	}

	void push_back(const T& t)
	{
		mMembers.push_back(t);
	}

private:

	static std::vector<T> mMembers;	
};

template <class T>
std::vector<T> IList<T>::mMembers;

#endif