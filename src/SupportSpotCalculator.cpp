#include "SupportSpotCalculator.h"
#include "Team.h"
#include "Goal.h"
#include "Pitch.h"
#include "Player.h"
#include "ParamLoader.h"

#include <Graphics/MeshComponent.hpp>

#include <OgreSceneNode.h>

SupportSpotCalculator::SupportSpotCalculator(const QString& name, Team* team)
	: dt::Node(name), mTeam(team), mBestSupportSpot(nullptr) {}

void SupportSpotCalculator::onInitialize() 
{
	mCoolingTime = addComponent(new CoolingTimeComponent(0.8f, getName() + "CoolTime"));

	mSpots.clear();
	const std::vector<Region*>& regions = mTeam->getPitch()->getAllRegions();
	for (auto it = regions.begin(); it != regions.end(); ++it)
	{
		mSpots.push_back(SupportSpot(*it, 0.f));
	}

	Ogre::SceneNode* scene_node = mTeam->getPitch()->getSceneNode();

	if (mTeam->getTeamColor() == Team::RED)
		mSpotFlagDrawer = addComponent(new CircleDrawerComponent("RedSpot", "PlayerFlagRed", 1.2f, 0.3f, scene_node));
	else 
		mSpotFlagDrawer = addComponent(new CircleDrawerComponent("BlueSpot", "PlayerFlagBlue", 1.2f, 0.3f, scene_node));
}

void SupportSpotCalculator::onDeinitialize() 
{
}

void SupportSpotCalculator::onUpdate(double time_diff)
{
	mIsUpdatingAfterChange = (time_diff == 0);

	if (mTeam->isInControl() && mCoolingTime->ready())
	{
		determineBestSupportSpot();
	}

	dt::Node::onUpdate(time_diff);
}

void SupportSpotCalculator::determineBestSupportSpot()
{
	float best_score = -1;

	for (auto it = mSpots.begin(); it != mSpots.end(); ++it)
	{
		it->score = 0.f;

		// Can pass
		if (mTeam->isSafeGoingThroughAllOpponents(mTeam->getControllingPlayer()->getPosition(), 
			it->region->getCenter(), Prm.PlayerMaxPassingForce))
		{
			it->score += Prm.SpotPassSafeScore;
		}

		// Can shoot
		if (mTeam->isSafeGoingThroughAllOpponents(it->region->getCenter(),
			mTeam->getOpponent()->getGoal()->getCenter(), Prm.PlayerMaxShootingForce))
		{
			it->score += Prm.SpotCanShootScore;
		}

		// Dist from controlling player
		float dist = mTeam->getControllingPlayer()->getPosition().distance(it->region->getCenter());
		if (dist < Prm.SpotOptimalDistance)
		{
			it->score += Prm.SpotDistFromCtrlPlayerScore * (dist / Prm.SpotOptimalDistance);
		}

		if (it->score > best_score)
		{
			mBestSupportSpot = &(*it);
			best_score = it->score;
		}
	}

	mSpotFlagDrawer->setPos(mBestSupportSpot->region->getCenter());
}

Ogre::Vector3 SupportSpotCalculator::getBestSupportSpot() 
{
	if (mBestSupportSpot == nullptr)
	{
		determineBestSupportSpot();
	}
	return mBestSupportSpot->region->getCenter();
}

void SupportSpotCalculator::setShowFlag(bool flag)
{
	if (flag)
	{
		mSpotFlagDrawer->enable();
	}
	else 
	{
		mSpotFlagDrawer->disable();
	}
}
