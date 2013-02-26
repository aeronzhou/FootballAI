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
		BallRadius = mParamTables["BallRadius"].toFloat();
		NumRegionsHorizontal = mParamTables["NumRegionsHorizontal"].toInt();
		NumRegionsVertical = mParamTables["NumRegionsVertical"].toInt();
		HalfPitchWidth = mParamTables["HalfPitchWidth"].toFloat();
		HalfPitchHeight = mParamTables["HalfPitchHeight"].toFloat();
		HalfGoalWidth = mParamTables["HalfGoalWidth"].toFloat();
	}

public:

	// Ball
	float BallMaxSpeed;
	float BallFriction;
	float BallRadius;

	// Playing Area
	int NumRegionsHorizontal;
	int NumRegionsVertical;

	// Pitch
	float HalfPitchWidth;
	float HalfPitchHeight;

	// Goal
	float HalfGoalWidth;
	
};
#endif