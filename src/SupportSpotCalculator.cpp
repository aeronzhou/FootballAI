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

	// Initialize support spots' positions
	float pitch_width = mTeam->getPitch()->getPlayingArea()->getWidth();
	float pitch_height = mTeam->getPitch()->getPlayingArea()->getHeight();
	float scale = 0.8;
	float px = pitch_width * 0.6 * (1 - scale) / 2;
	float py = pitch_height * (1 - scale) / 2;
	float dx = (pitch_width * 0.55 - px * 2) / (Prm.NumSupportSpotX - 1);
	float dy = (pitch_height - py * 2) / (Prm.NumSupportSpotY - 1);

	float left = mTeam->getPitch()->getPlayingArea()->getLeft();
	float right = mTeam->getPitch()->getPlayingArea()->getRight();
	float top = mTeam->getPitch()->getPlayingArea()->getTop();
	Ogre::SceneNode* scene_node = mTeam->getPitch()->getSceneNode();

	for (int i = 0; i < Prm.NumSupportSpotX; ++i)
	{
		for (int j = 0; j < Prm.NumSupportSpotY; ++j)
		{
			if (mTeam->getTeamColor() == Team::BLUE)
			{
				mSpots.push_back(SupportSpot(Ogre::Vector3(left + px + i * dx, 0, top + py + j * dy), 0.f));
				mSpots.back().drawer = std::shared_ptr<CircleDrawer>(new CircleDrawer(
					"Blue" + dt::Utils::toString(i * Prm.NumSupportSpotX + j), scene_node, 0.08f, "PlayerFlagBlue"));
				mSpots.back().drawer->setPos(mSpots.back().position);
			}
			else 
			{
				mSpots.push_back(SupportSpot(Ogre::Vector3(right - px - i * dx, 0, top + py + j * dy), 0.f));
				mSpots.back().drawer = std::shared_ptr<CircleDrawer>(new CircleDrawer(
					"Red" + dt::Utils::toString(i * Prm.NumSupportSpotX + j), scene_node, 0.08f, "PlayerFlagRed"));
				mSpots.back().drawer->setPos(mSpots.back().position);
			}
		}
	}
}

void SupportSpotCalculator::onDeinitialize() 
{
}

const float TOTAL_SCORE = 5.f;
const float BIGGEST_RADIUS = 0.5f;

void SupportSpotCalculator::onUpdate(double time_diff)
{
	mIsUpdatingAfterChange = (time_diff == 0);

	if (mTeam->isInControl())
	{
		if (mCoolingTime->ready())
		{
			determineBestSupportSpot();
		}

		if (Prm.ShowSupportSpot)
		{
			for (auto it = mSpots.begin(); it != mSpots.end(); ++it)
			{
				it->drawer->draw(it->score / TOTAL_SCORE * BIGGEST_RADIUS);
			}		
			
			if (mBestSupportSpot)
			{
				if (mTeam->getTeamColor() == Team::BLUE)
				{
					mBestSupportSpot->drawer->highlight(mBestSupportSpot->score * 1.2 / TOTAL_SCORE * BIGGEST_RADIUS, "PlayerFlagRed");
				}
				else 
				{
					mBestSupportSpot->drawer->highlight(mBestSupportSpot->score * 1.2 / TOTAL_SCORE * BIGGEST_RADIUS, "PlayerFlagBlue");
				}
			}
		}
	}
	else
	{
		for (auto it = mSpots.begin(); it != mSpots.end(); ++it)
		{
			it->drawer->clear();
		}
	}

	dt::Node::onUpdate(time_diff);
}

void SupportSpotCalculator::determineBestSupportSpot()
{
	float best_score = -1;

	for (auto it = mSpots.begin(); it != mSpots.end(); ++it)
	{
		it->score = 1.f;

		// Can pass
		if (mTeam->isSafeGoingThroughAllOpponents(mTeam->getControllingPlayer()->getPosition(), 
			it->position, Prm.PlayerMaxPassingForce))
		{
			it->score += Prm.SpotPassSafeScore;
		}

		// Can shoot
		if (mTeam->isSafeGoingThroughAllOpponents(it->position,
			mTeam->getOpponent()->getGoal()->getCenter(), Prm.PlayerMaxShootingForce))
		{
			it->score += Prm.SpotCanShootScore;
		}

		// Dist from controlling player
		float dist = mTeam->getControllingPlayer()->getPosition().distance(it->position);
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
}

Ogre::Vector3 SupportSpotCalculator::getBestSupportSpot() 
{
	if (mBestSupportSpot == nullptr)
	{
		determineBestSupportSpot();
	}
	return mBestSupportSpot->position;
}