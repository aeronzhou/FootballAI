#include "Team.h"
#include "Ball.h"
#include "Pitch.h"
#include "Player.h"
#include "FieldPlayer.h"
#include "GoalKeeper.h"
#include "PlayerManager.h"
#include "PlayerPositionManager.h"
#include "Goal.h"
#include "TeamState.h"
#include "FieldPlayerState.h"
#include "ParamLoader.h"
#include "MessageDispatcher.h"
#include "GeometryHelper.h"
#include "Utils.h"
#include "Constant.h"

Team::Team(Ball* ball, Pitch* pitch, TeamColor color, Goal* goal)
	: mBall(ball), mPitch(pitch), mColor(color), mGoal(goal), 
	  mOpponent(nullptr), mControllingPlayer(nullptr), mPlayerClosestToBall(nullptr), mPlayers(std::vector<Player*>()),
	  mIsControllingBall(false), mSupportingPlayer(nullptr), mReceivingPlayer(nullptr) {}


void Team::onInitialize() 
{
	// Setup state machine
	mStateMachine = new StateMachine<Team>(this);
	mStateMachine->setCurrentState(WaitingForKickOff::get());	

	// Initialize players
	_createPlayers();

	//for (auto it = mPlayers.begin(); it != mPlayers.end(); ++it)
	//{
	//	(*it)->getSteering()->setSeparationOn();
	//}

	_findPlayerClosestToBall();
}

void Team::onDeinitialize()
{
	delete mStateMachine;
}

void Team::onUpdate(double time_diff)
{
	this->mIsUpdatingAfterChange = (time_diff == 0);

	// Update StateMachine
	mStateMachine->onUpdate();	

	_findPlayerClosestToBall();

	dt::Node::onUpdate(time_diff);
}

void Team::_createPlayers()
{
	std::vector<int> vec_pos = PlayerPositionManager::get().getAssignedPosition("WaitingForKickOff");

	// Generate players with PlayerManager
	if (getTeamColor() == RED)
	{
		mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Red_" + dt::Utils::toString(0), 
			this, FieldPlayer::FORWARD, vec_pos[0])).get());
		for (int i = 1; i < 3; ++i)
		{
			mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Red_" + dt::Utils::toString(i), 
				this, FieldPlayer::MIDFIELD, vec_pos[i])).get());
		}
		for (int i = 3; i < 6; ++i)
		{
			mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Red_" + dt::Utils::toString(i), 
				this, FieldPlayer::BACK, vec_pos[i])).get());
		}
		mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Red_" + dt::Utils::toString(6), 
			this, FieldPlayer::BACK, vec_pos[6])).get());

		for (int i = 0; i < mPlayers.size(); ++i)
		{
			mPlayers[i]->placeAtPosition(mPlayers[i]->getPositionWithRegion(), RED_TEAM_HEADING, Prm.PlayerScale);
		}
	}
	else 
	{
		mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Blue_" + dt::Utils::toString(0), 
			this, FieldPlayer::FORWARD, vec_pos[7])).get());
		for (int i = 8; i < 10; ++i)
		{
			mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Blue_" + dt::Utils::toString(i - 7), 
				this, FieldPlayer::MIDFIELD, vec_pos[i])).get());
		}
		for (int i = 10; i < 13; ++i)
		{
			mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Blue_" + dt::Utils::toString(i - 7), 
				this, FieldPlayer::BACK, vec_pos[i])).get());
		}
		mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Blue_" + dt::Utils::toString(6), 
			this, FieldPlayer::MIDFIELD, vec_pos[13])).get());

		for (int i = 0; i < mPlayers.size(); ++i)
		{
			mPlayers[i]->placeAtPosition(mPlayers[i]->getPositionWithRegion(), BLUE_TEAM_HEADING, Prm.PlayerScale);
		}
	}
}

Team::TeamColor Team::getTeamColor() const 
{ 
	return mColor; 
}

Pitch* Team::getPitch() const 
{ 
	return mPitch; 
}

Team* Team::getOpponent() const 
{ 
	return mOpponent; 
}

void Team::setOpponent(Team* opponent)
{
	mOpponent = opponent;
}

Ball* Team::getBall() const
{
	return mBall;
}

Goal* Team::getGoal() const 
{
	return mGoal;
}

void Team::playersBackForKickOff()
{
	for (int i = mPlayers.size() - 1; i >= 0; --i)
	{
		MessageDispatcher::get().dispatchMessage(DELIVER_IMMEDIATELY,
			NULL, 
			mPlayers[i],
			MSG_BACK_TO_ORIGIN,
			NULL);
	}
}

bool Team::allPlayersInAssignedRegions() const 
{
	for (auto player = mPlayers.begin(); player != mPlayers.end(); ++player)
	{
		if (!(*player)->withinAssignedRegion())
		{
			return false;
		}
	}
	return true;
}

void Team::setAssignedRegion(const std::vector<int>& vec_pos)
{
	if (getTeamColor() == RED)
	{
		for (int i = mPlayers.size() - 1; i >= 0; --i)
		{
			mPlayers[i]->setAssignedRegion(vec_pos[i]);
		}
	}
	else 
	{
		for (int i = mPlayers.size() - 1; i >= 0; --i)
		{
			mPlayers[i]->setAssignedRegion(vec_pos[i + 7]);
		}
	}
}

StateMachine<Team>* Team::getStateMachine() const 
{
	return mStateMachine;
}

void Team::sendPlayersToAssignedRegion()
{
	for (std::vector<Player*>::iterator it = mPlayers.begin(); it != mPlayers.end(); ++it)
	{
		MessageDispatcher::get().dispatchMessage(
			0, 
			nullptr,
			*it,
			MSG_BACK_TO_ORIGIN,
			nullptr);
	}
}

void Team::_findPlayerClosestToBall()
{
	float min_value = MAX_VALUE;
	for (auto it = mPlayers.begin(); it != mPlayers.end(); ++it)
	{
		float dist = (*it)->getPosition().distance(mBall->getPosition());
		if ((*it)->getPosition().squaredDistance(mBall->getPosition()) < min_value)
		{
			min_value = dist;
			mPlayerClosestToBall = (*it);
		}
	}
}

Player* Team::getPlayerClosestToBall() const 
{
	return mPlayerClosestToBall;
}

float Team::getClosestDistToBall() const 
{
	return mPlayerClosestToBall->getDistToBall();
}

bool Team::isInControl() const 
{
	return mIsControllingBall;
}

Player* Team::getControllingPlayer() const 
{
	return mControllingPlayer;
}

void Team::setControllingPlayer(Player* player)
{
	mIsControllingBall = (player != nullptr);

	mControllingPlayer = player;
}

Player* Team::getSupportingPlayer() const 
{
	return mSupportingPlayer;
}

void Team::setSupportingPlayer(Player* player)
{
	mSupportingPlayer = player;
}

Player* Team::getReceivingPlayer() const 
{
	return mReceivingPlayer;
}

void Team::setReceivingPlayer(Player* player)
{
	mReceivingPlayer = player;
}

bool Team::canPass(Player* passer, Player*& receiver, Ogre::Vector3& proper_target, float passing_force)
{
	float best_score = 0;
	Ogre::Vector3 target;

	for (auto it = mPlayers.begin(); it != mPlayers.end(); ++it)
	{
		if (*it != passer)
		{
			float score = _getBestSpotOfReceiving(*it, passing_force, target);
			if (score > best_score)
			{
				best_score = score;	
				proper_target = target;
				receiver = *it;
			}
		}
	}

	return (receiver != nullptr);
}

bool Team::canShoot(Player* player, Ogre::Vector3& proper_target, float shooting_force)
{
	Goal* goal = getOpponent()->getGoal();

	// You cannot shoot when your back is facing to the goal
	if (player->getHeading().dotProduct(mGoal->getFacing()) < 0)
	{
		return false;
	}

	float dist_to_goal = Vector3To2(player->getPosition()).distance(goal->getCenter());

	// If too far from goal, it may be not a good chance to shoot
	if (dist_to_goal > Prm.PlayerShootingRange)
	{
		return false;
	}

	// If shooting angle is too narrow, drop it
	float theta = fabs(player->getPosition().x - goal->getCenter().x) / dist_to_goal;
	if (asin(theta) < PI / 6)
	{
		return false;
	}

	int tot = Prm.PlayerShootingTryNum;
	Ogre::Vector3 left_to_right = goal->getRightPost() - goal->getLeftPost();

	while (tot--)
	{
		Ogre::Vector3 target = 	goal->getLeftPost() + left_to_right * dt::Random::get(0.f, 1.f);
		
		// If safe to shot
		// or with some possibility
		if (isSafeGoingThroughAllOpponents(mBall->getPosition(), target, shooting_force) ||
			WithPossibility(0.05))
		{
			proper_target = target;
			return true;
		}
	}

	return false;
}

std::vector<Player*>& Team::getPlayers()
{
	return mPlayers;
}

bool Team::isSafeGoingThroughAllOpponents(const Ogre::Vector3& from, const Ogre::Vector3& target, float force)
{
	std::vector<Player*>& opponents = getOpponent()->getPlayers();

	for (auto it = opponents.begin(); it != opponents.end(); ++it)
	{
		if (!isSafeGoingThroughOpponent(from, target, force, *it))
		{
			return false;
		}
	}
	return true;
}

bool Team::isSafeGoingThroughOpponent(const Ogre::Vector3& from, const Ogre::Vector3& target, float force, Player* opponent)
{
	Ogre::Vector3 to_target = target - from;
	Ogre::Vector3 to_opponent = Vector3To2(opponent->getPosition() - from);

	// If opponent if behind this player
	if (to_target.dotProduct(to_opponent) < 0)
	{
		return true;
	}

	// If Distance(opponent, from) > Distance(from, target), pass
	if (opponent->getPosition().distance(from) > from.distance(target))
	{
		return true;
	}

	// If the opponent can intercept the ball
	float x = to_target.z;
	float z = -to_target.x;
	Ogre::Vector3 oppo_pos = Vector3To2(opponent->getPosition());
	Ogre::Vector3 oppo_pos_away = oppo_pos + Ogre::Vector3(x, 0, z).normalisedCopy() * 300.f;
	Ogre::Vector3 intersect_point;
	if (GeometryHelper::get().lineSegmentIntersect(from, target, oppo_pos, oppo_pos_away, intersect_point))
	{
		float oppo_to_intersect = oppo_pos.distance(intersect_point);
		float ball_to_intersect = from.distance(intersect_point);
		float time = mBall->getTimeToGoThroughDistance(ball_to_intersect, force);
		if (time <= 0 || oppo_to_intersect / opponent->getMaxSpeed() < time)
		{
			return false;
		}
	}

	return true;
}

float Team::_getScoreOfPosition(const Ogre::Vector3& position)
{
	// Closer to opponent's goal
	float score = 10.f * fabs((position - mGoal->getCenter()).x);

	return score;
}

float Team::_getBestSpotOfReceiving(Player* receiver, float passing_force, Ogre::Vector3& target)
{
	float best_score = -1;
	Ogre::Vector3 ball_pos = mBall->getPosition();
	Ogre::Vector3 to_reciver = Vector3To2(receiver->getPosition() - ball_pos);
	float dist_to_receiver = to_reciver.length();
	float length = receiver->getMaxSpeed() * mBall->getTimeToGoThroughDistance(dist_to_receiver, passing_force) * 0.8;
	float theta = asin(length / dist_to_receiver);
	int try_pass_times = 4;

	for (int i = 0; i <= try_pass_times; ++i)
	{
		Ogre::Radian angle(-theta + i * (2 * theta / try_pass_times));
		Ogre::Quaternion rotation = GetRotationThroughHeading(to_reciver) * Ogre::Quaternion(angle, Ogre::Vector3(0, 1, 0));
		Ogre::Vector3 aim_target = ball_pos + rotation * Ogre::Vector3(0, 0, dist_to_receiver);

		if (isSafeGoingThroughAllOpponents(ball_pos, aim_target, passing_force))
		{
			float score = _getScoreOfPosition(aim_target);
			if (score > best_score)
			{
				best_score = score;
				target = aim_target;
			}
		}
	}

	return best_score;
}

void Team::requestPass(Player* player, double delay_time /* = 0 */)
{
	// With a possibility to execute
	if (WithPossibility(0.3))
	{
		if (isSafeGoingThroughAllOpponents(
			getControllingPlayer()->getPosition(), 
			player->getPosition(), 
			Prm.PlayerMaxPassingForce))
		{
			MessageDispatcher::get().dispatchMessage(
				0,
				player,
				getControllingPlayer(),
				MSG_REQUEST_PASS,
				player);	
		}
	}
}

// Send back to home region
void Team::updateTargetsOfWaitingPlayers()
{
	for (auto it = mPlayers.begin(); it != mPlayers.end(); ++it)
	{
		if ((*it)->getPlayerRole() != Player::GOAL_KEEPER)
		{
			FieldPlayer* player = static_cast<FieldPlayer*>(*it);

			if (player->getStateMachine()->isInState(*Waiting::get()) ||
				player->getStateMachine()->isInState(*BackToOrigin::get()))
			{
				player->setTarget(player->getAssignedRegion()->getCenter());
			}
		}
	}
}
