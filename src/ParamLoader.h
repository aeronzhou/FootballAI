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

	ParamLoader()
	{
		// Initialize all global params
		if (!readFile("./../data/xml/Params.xml", mParamTables)) 
			return;

		BallMaxSpeed = mParamTables["BallMaxSpeed"].toFloat();
		BallFriction = mParamTables["BallFriction"].toFloat();
		BallRadius = mParamTables["BallRadius"].toFloat();
		BallMass = mParamTables["BallMass"].toFloat(); 

		NumRegionsHorizontal = mParamTables["NumRegionsHorizontal"].toInt();
		NumRegionsVertical = mParamTables["NumRegionsVertical"].toInt();

		HalfPitchWidth = mParamTables["HalfPitchWidth"].toFloat();
		HalfPitchHeight = mParamTables["HalfPitchHeight"].toFloat(); 

		HalfGoalWidth = mParamTables["HalfGoalWidth"].toFloat();
		HalfGoalHeight = mParamTables["HalfGoalHeight"].toFloat();
		GoalCylinderRadius = mParamTables["GoalCylinderRadius"].toFloat();

		CameraPosX = mParamTables["CameraPosX"].toFloat();
		CameraPosY = mParamTables["CameraPosY"].toFloat();
		CameraPosZ = mParamTables["CameraPosZ"].toFloat();
		CameraLookAtX = mParamTables["CameraLookAtX"].toFloat();
		CameraLookAtY = mParamTables["CameraLookAtY"].toFloat();
		CameraLookAtZ = mParamTables["CameraLookAtZ"].toFloat();

		VelocityToForceCoefficient = mParamTables["VelocityToForceCoefficient"].toFloat();
		DecelerationTweaker = mParamTables["DecelerationTweaker"].toFloat();
		VisibleRangeSqr = mParamTables["VisibleRange"].toFloat() * mParamTables["VisibleRange"].toFloat();

		TotalGameTime = mParamTables["TotalGameTime"].toDouble();
		LastCriticalMinutes = mParamTables["LastCriticalMinutes"].toDouble();
	}

private:

	MSS mParamTables;

public:

	// Ball
	float BallMaxSpeed;
	float BallFriction;
	float BallRadius;
	float BallMass;

	// Playing Area
	int NumRegionsHorizontal;
	int NumRegionsVertical;

	// Pitch
	float HalfPitchWidth;
	float HalfPitchHeight;

	// Goal
	float HalfGoalWidth;
	float HalfGoalHeight;
	float GoalCylinderRadius;

	// Camera
	float CameraPosX;
	float CameraPosY;
	float CameraPosZ;
	float CameraLookAtX;
	float CameraLookAtY;
	float CameraLookAtZ;

	// Steering
	float VelocityToForceCoefficient;
	float DecelerationTweaker;
	float VisibleRangeSqr;
	float SeperationCoefficient;

	// Timer
	double TotalGameTime;
	double LastCriticalMinutes;
	
};

#endif