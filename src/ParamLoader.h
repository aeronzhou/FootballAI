#ifndef FOOTBALL_AI_PARAMS
#define FOOTBALL_AI_PARAMS

#include "ParamLoaderBase.h"

#define Prm (*ParamLoader::get())

/** 
  * Class to fetch global parameters
  */
class ParamLoader : public ParamLoaderBase
{
public:

	static ParamLoader* get() 
	{
		static ParamLoader instance;
		return &instance;
	}

	ParamLoader(): ParamLoaderBase("Params.xml")
	{
		// Initialize all global params
		if (!mIsGoodFile) 
			return;

		//Height = mParamTables["Height"].toFloat();
		BallMaxSpeed = mParamTables["BallMaxSpeed"].toFloat();
		BallFriction = mParamTables["BallFriction"].toFloat();
	}

public:

	// Ball
	float BallMaxSpeed;
	float BallFriction;

	// Player

	
};
#endif