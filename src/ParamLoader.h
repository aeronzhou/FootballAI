#ifndef FOOTBALL_AI_PARAMS
#define FOOTBALL_AI_PARAMS

#include "ParamLoaderBase.h"

#define Prm (*ParamLoader::get())

#include <iostream>

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
		BallDeceleration = mParamTables["BallDeceleration"].toFloat();
		BallResistance = mParamTables["BallResistance"].toFloat();
		BallResistanceInterval = mParamTables["BallResistanceInterval"].toFloat();
		BallRadius = mParamTables["BallRadius"].toFloat();
		BallMass = mParamTables["BallMass"].toFloat(); 
		BallPosX = mParamTables["BallPosX"].toFloat();
		BallPosZ = mParamTables["BallPosZ"].toFloat();

		NumRegionsHorizontal = mParamTables["NumRegionsHorizontal"].toInt();
		NumRegionsVertical = mParamTables["NumRegionsVertical"].toInt();

		HalfPitchWidth = mParamTables["HalfPitchWidth"].toFloat();
		HalfPitchHeight = mParamTables["HalfPitchHeight"].toFloat(); 
		PitchMargin = mParamTables["PitchMargin"].toFloat();

		HalfGoalWidth = mParamTables["HalfGoalWidth"].toFloat();
		HalfGoalHeight = mParamTables["HalfGoalHeight"].toFloat();
		GoalCylinderRadius = mParamTables["GoalCylinderRadius"].toFloat();

		CameraPosX = mParamTables["CameraPosX"].toFloat();
		CameraPosY = mParamTables["CameraPosY"].toFloat();
		CameraPosZ = mParamTables["CameraPosZ"].toFloat();
		CameraSpeed = mParamTables["CameraSpeed"].toFloat();
		MouseSensitivity = mParamTables["MouseSensitivity"].toFloat();

		VelocityToForceCoefficient = mParamTables["VelocityToForceCoefficient"].toFloat();
		DecelerationTweaker = mParamTables["DecelerationTweaker"].toFloat();
		VisibleRange = mParamTables["VisibleRange"].toFloat();
		SeperationCoefficient = mParamTables["SeperationCoefficient"].toFloat();
		DistAtTarget = mParamTables["DistAtTarget"].toFloat();

		TotalGameTime = mParamTables["TotalGameTime"].toDouble();
		LastCriticalMinutes = mParamTables["LastCriticalMinutes"].toDouble();

		PlayerScale = mParamTables["PlayerScale"].toFloat();
		PlayerInitPositionY = mParamTables["PlayerInitPositionY"].toFloat();
		PlayerKickCoolingTime = mParamTables["PlayerKickCoolingTime"].toFloat();
		PlayerDribblingForce = mParamTables["PlayerDribblingForce"].toFloat();
		PlayerTurnAroundForce = mParamTables["PlayerTurnAroundForce"].toFloat();
		PlayerMaxPassingForce = mParamTables["PlayerMaxPassingForce"].toFloat();
		PlayerMaxShootingForce = mParamTables["PlayerMaxShootingForce"].toFloat();
		PlayerThreatenedRange = mParamTables["PlayerThreatenedRange"].toFloat();
		PlayerShootingRange = mParamTables["PlayerShootingRange"].toFloat();
		PlayerShootingTryNum = mParamTables["PlayerShootingTryNum"].toFloat();
		PlayerReceivingRange = mParamTables["PlayerReceivingRange"].toFloat();

		PlayerRangeRadius = mParamTables["PlayerRangeRadius"].toFloat();
		PlayerRangeThickness = mParamTables["PlayerRangeThickness"].toFloat();
		PlayerRangeMateiral = mParamTables["PlayerRangeMateiral"];

		GoalKeeperInterceptRange = mParamTables["GoalKeeperInterceptRange"].toFloat();
		GoalKeeperControlRange = mParamTables["GoalKeeperControlRange"].toFloat();

		SpotPassSafeScore = mParamTables["SpotPassSafeScore"].toFloat();
		SpotCanShootScore = mParamTables["SpotCanShootScore"].toFloat();

		PhysicsShowDebug = mParamTables["PhysicsShowDebug"].toInt();
		ShowDebugText = mParamTables["ShowDebugText"].toInt();

		GAGeneration = mParamTables["GAGeneration"].toInt();
		GACrossCostPerRgn = mParamTables["GACrossCostPerRgn"].toInt();
		GAPlayerKeepBallValue = mParamTables["GAPlayerKeepBallValue"].toInt();
		GAPlayerChaseBallValue = mParamTables["GAPlayerChaseBallValue"].toInt();
		GAPlayerDefendValue = mParamTables["GAPlayerDefendValue"].toInt();
		GAPlayerAttackValue = mParamTables["GAPlayerAttackValue"].toInt();
		GAColonySize = mParamTables["GAColonySize"].toInt();

	}

private:

	MSS mParamTables;

public:

	// Ball
	float BallMaxSpeed;
	float BallFriction;
	float BallDeceleration;
	float BallResistance;
	float BallResistanceInterval;
	float BallRadius;
	float BallMass;
	float BallPosX;
	float BallPosZ;

	// Regions
	int NumRegionsHorizontal;
	int NumRegionsVertical;

	// Pitch
	float HalfPitchWidth;
	float HalfPitchHeight;
	float PitchMargin;

	// Goal
	float HalfGoalWidth;
	float HalfGoalHeight;
	float GoalCylinderRadius;

	// Camera
	float CameraPosX;
	float CameraPosY;
	float CameraPosZ;
	float CameraSpeed;
	float MouseSensitivity;

	// SteeringBehaviors 
	float VelocityToForceCoefficient;
	float DecelerationTweaker;
	float VisibleRange;
	float SeperationCoefficient;
	float DistAtTarget;

	// Timer
	double TotalGameTime;
	double LastCriticalMinutes;

	// Players
	float PlayerScale;
	float PlayerInitPositionY;
	float PlayerKickCoolingTime;
	float PlayerDribblingForce;
	float PlayerTurnAroundForce;
	float PlayerMaxPassingForce;
	float PlayerMaxShootingForce;
	float PlayerThreatenedRange;
	float PlayerShootingRange;
	float PlayerShootingTryNum;
	float PlayerReceivingRange;
	
	// PlayerRange
	float PlayerRangeRadius;
	float PlayerRangeThickness;
	QString PlayerRangeMateiral;

	// GoalKeeper
	float GoalKeeperInterceptRange;
	float GoalKeeperControlRange;

	// Spot
	float SpotPassSafeScore;
	float SpotCanShootScore;

	// Others
	int PhysicsShowDebug;
	int ShowDebugText;   

	//GA
	int GAGeneration;
	int GACrossCostPerRgn;
	int GAPlayerKeepBallValue;
	int GAPlayerChaseBallValue;
	int GAPlayerDefendValue;
	int GAPlayerAttackValue;
	int GAColonySize;

};

#endif