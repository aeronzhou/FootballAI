#include "GoalKeeperState.h"
#include "GoalKeeper.h"
#include "Team.h"
#include "MessageDispatcher.h"
#include "Constant.h"
#include "ParamLoader.h"

// PutBallBackInPlayState
PutBallBackInPlayState* PutBallBackInPlayState::get()
{
	static PutBallBackInPlayState instance;
	return &instance;
}

void PutBallBackInPlayState::enter(GoalKeeper* keeper)
{
	keeper->getTeam()->setControllingPlayer(keeper);
	keeper->getTeam()->getOpponent()->allPlayersInAssignedRegions();
	keeper->getTeam()->allPlayersInAssignedRegions();
}

void PutBallBackInPlayState::execute(GoalKeeper* keeper)
{
	Player* receiver = NULL;
	Ogre::Vector3 ballTarget;

	if(keeper->getTeam()->canPass(keeper,
								  receiver,
								  ballTarget,
								  Prm.PlayerMaxPassingForce))
	{
		keeper->getBall()->kick(ballTarget - keeper->getBall()->getPosition().normalisedCopy(),
			Prm.PlayerMaxPassingForce);
		keeper->getPitch()->setGoalKeeperHasBall(false);
		MessageDispatcher::get().dispatchMessage(DELIVER_IMMEDIATELY,
												keeper,
												receiver,
												MSG_RECEIVE_BALL,
												&ballTarget);
		keeper->getStateMachine()->changeState(TendGoal::get());
		return;
	}
	keeper->setVelocity(Ogre::Vector3::ZERO);
}

void PutBallBackInPlayState::exit(GoalKeeper* keeper)
{
}

bool PutBallBackInPlayState::onMessage(GoalKeeper*, const Message&)
{
	return false;
}

