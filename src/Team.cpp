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
#include "ParamLoader.h"
#include "MessageDeliverer.h"
#include "Utils.h"
#include "Constant.h"

Team::Team(Ball* ball, Pitch* pitch, TeamColor color, Goal* goal)
	: mBall(ball), mPitch(pitch), mColor(color), mGoal(goal), 
	  mOpponent(nullptr), mControllingPlayer(nullptr), mPlayerClosestToBall(nullptr), mPlayers(std::vector<Player*>()),
	  mIsControllingBall(false) {}


void Team::onInitialize() 
{
	// Setup state machine
	mStateMachine = new StateMachine<Team>(this);
	mStateMachine->setCurrentState(WaitingForKickOff::get());	

	// Initialize players
	_createPlayers();

	for (auto it = mPlayers.begin(); it != mPlayers.end(); ++it)
	{
		(*it)->getMotionAider()->setSeparationOn();
	}
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

	findPlayerClosestToBall();

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
		//for (int i = 3; i < 6; ++i)
		//{
		//	mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Red_" + dt::Utils::toString(i), 
		//		this, FieldPlayer::BACK, vec_pos[i])).get());
		//}
		//mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Red_" + dt::Utils::toString(6), 
		//	this, FieldPlayer::BACK, vec_pos[6])).get());

		for (int i = 0; i < mPlayers.size(); ++i)
		{
			mPlayers[i]->placeAtPosition(mPlayers[i]->getPositionWithRegion(), RED_TEAM_HEADING, Prm.PlayerScale);
		}
	}
	else 
	{
		//mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Blue_" + dt::Utils::toString(0), 
		//	this, FieldPlayer::FORWARD, vec_pos[7])).get());
		//for (int i = 8; i < 10; ++i)
		//{
		//	mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Blue_" + dt::Utils::toString(i - 7), 
		//		this, FieldPlayer::MIDFIELD, vec_pos[i])).get());
		//}
		//for (int i = 10; i < 13; ++i)
		//{
		//	mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Blue_" + dt::Utils::toString(i - 7), 
		//		this, FieldPlayer::MIDFIELD, vec_pos[i])).get());
		//}
		//mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Blue_" + dt::Utils::toString(6), 
		//	this, FieldPlayer::MIDFIELD, vec_pos[13])).get());

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
		MessageDeliverer::get().deliverMessage(DELIVER_IMMEDIATELY,
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
		(*it)->getMotionAider()->setArriveOn();
		(*it)->setTarget((*it)->getAssignedRegion()->getCenter());
	}
}

void Team::findPlayerClosestToBall()
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

bool Team::isControllingBall() const 
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
		if (_isSafeGoingThroughAllOpponents(mBall->getPosition(), target, shooting_force) ||
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

bool Team::_isSafeGoingThroughAllOpponents(const Ogre::Vector3& from, const Ogre::Vector3& target, float force)
{
	std::vector<Player*>& opponents = getOpponent()->getPlayers();

	for (auto it = opponents.begin(); it != opponents.end(); ++it)
	{
		if (!_isSafeGoingThroughOpponent(from, target, force, *it))
		{
			return false;
		}
	}
	return true;
}

#define CONST_VECTOR3 const Ogre::Vector3& 

// Function to find intersection of two line-segement                   
float _xmult(CONST_VECTOR3 p1, CONST_VECTOR3 p2, CONST_VECTOR3 p0);
int _dot_online_in(CONST_VECTOR3 p, CONST_VECTOR3 l1, CONST_VECTOR3 l2);
int _same_side(CONST_VECTOR3 p1, CONST_VECTOR3 p2, CONST_VECTOR3 l1, CONST_VECTOR3 l2);
int _parallel(CONST_VECTOR3 u1, CONST_VECTOR3 u2, CONST_VECTOR3 v1, CONST_VECTOR3 v2);
int _dots_inline(CONST_VECTOR3 p1, CONST_VECTOR3 p2, CONST_VECTOR3 p3);
int _intersect_in(CONST_VECTOR3 u1, CONST_VECTOR3 u2, CONST_VECTOR3 v1, CONST_VECTOR3 v2);
bool IntersectionPoint(CONST_VECTOR3 u1, CONST_VECTOR3 u2, CONST_VECTOR3 v1, CONST_VECTOR3 v2, Ogre::Vector3 &ret);

bool Team::_isSafeGoingThroughOpponent(const Ogre::Vector3& from, const Ogre::Vector3& target, float force, Player* opponent)
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
	if (IntersectionPoint(from, target, oppo_pos, oppo_pos_away, intersect_point))
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

#define zero(x) (((x)>0?(x):-(x))<EPS)

float _xmult(CONST_VECTOR3 p1, CONST_VECTOR3 p2, CONST_VECTOR3 p0)
{
	return (p1.x - p0.x) * (p2.z - p0.z) - (p2.x - p0.x) * (p1.z - p0.z);
}

int _dot_online_in(CONST_VECTOR3 p, CONST_VECTOR3 l1, CONST_VECTOR3 l2)
{
	return zero(_xmult(p, l1, l2)) && (l1.x - p.x) * (l2.x - p.x) < EPS && (l1.z - p.z) * (l2.z - p.z) < EPS;
}

int _same_side(CONST_VECTOR3 p1, CONST_VECTOR3 p2, CONST_VECTOR3 l1, CONST_VECTOR3 l2)
{
	return _xmult(l1, p1, l2) * _xmult(l1, p2, l2) > EPS;
}

int _parallel(CONST_VECTOR3 u1, CONST_VECTOR3 u2, CONST_VECTOR3 v1, CONST_VECTOR3 v2)
{
	return zero((u1.x - u2.x) * (v1.z - v2.z) - (v1.x - v2.x) * (u1.z - u2.z));
}

int _dots_inline(CONST_VECTOR3 p1, CONST_VECTOR3 p2, CONST_VECTOR3 p3)
{
	return zero(_xmult(p1, p2, p3));
}

int _intersect_in(CONST_VECTOR3 u1, CONST_VECTOR3 u2, CONST_VECTOR3 v1, CONST_VECTOR3 v2)
{
	if (!_dots_inline(u1, u2, v1) || !_dots_inline(u1, u2, v2))
		return !_same_side(u1, u2, v1, v2) && !_same_side(v1, v2, u1, u2);
	return _dot_online_in(u1, v1, v2) || _dot_online_in(u2, v1, v2) || _dot_online_in(v1, u1, u2) || _dot_online_in(v2, u1, u2);
}


bool IntersectionPoint(CONST_VECTOR3 u1, CONST_VECTOR3 u2,
	CONST_VECTOR3 v1, CONST_VECTOR3 v2, Ogre::Vector3 &ret)
{
	if (_parallel(u1, u2, v1, v2) || !_intersect_in(u1, u2, v1, v2))
		return false;

	ret = u1;
	float t = ((u1.x - v1.x) * (v1.z - v2.z) - (u1.z - v1.z) * (v1.x - v2.x))
		/ ((u1.x - u2.x) * (v1.z - v2.z) - (u1.z - u2.z) * (v1.x - v2.x));
	ret.x += (u2.x - u1.x) * t;
	ret.z += (u2.z - u1.z) * t;
	ret.y = 0.f;

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

		if (_isSafeGoingThroughAllOpponents(ball_pos, aim_target, passing_force))
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


