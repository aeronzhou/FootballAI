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
		CameraSpeed = mParamTables["CameraSpeed"].toFloat();
		MouseSensitivity = mParamTables["MouseSensitivity"].toFloat();

		VelocityToForceCoefficient = mParamTables["VelocityToForceCoefficient"].toFloat();
		DecelerationTweaker = mParamTables["DecelerationTweaker"].toFloat();
		VisibleRangeSqr = mParamTables["VisibleRange"].toFloat() * mParamTables["VisibleRange"].toFloat();
		SeperationCoefficient = mParamTables["SeperationCoefficient"].toFloat();
		DistAtTarget = mParamTables["DistAtTarget"].toFloat();

		TotalGameTime = mParamTables["TotalGameTime"].toDouble();
		LastCriticalMinutes = mParamTables["LastCriticalMinutes"].toDouble();

		PlayerScale = mParamTables["PlayerScale"].toFloat();
		PlayerInitPositionY = mParamTables["PlayerInitPositionY"].toFloat();
		PlayerKickCoolingTime = mParamTables["PlayerKickCoolingTime"].toFloat();

		PhysicsShowDebug = mParamTables["PhysicsShowDebug"].toInt();
		ShowDebugText = mParamTables["ShowDebugText"].toInt();
	}

private:

	MSS mParamTables;

public:

	// Ball
	float BallMaxSpeed;
	float BallFriction;
	float BallRadius;
	float BallMass;

	// Regions
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
	float CameraSpeed;
	float MouseSensitivity;

	// Motion Aider 
	float VelocityToForceCoefficient;
	float DecelerationTweaker;
	float VisibleRangeSqr;
	float SeperationCoefficient;
	float DistAtTarget;

	// Timer
	double TotalGameTime;
	double LastCriticalMinutes;

	// Players
	float PlayerScale;
	float PlayerInitPositionY;
	float PlayerKickCoolingTime;

	// Others
	int PhysicsShowDebug;
	int ShowDebugText;                       
	
};

#endif