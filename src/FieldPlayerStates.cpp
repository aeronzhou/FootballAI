#include "FieldPlayerStates.h"
#include "Pitch.h"
#include "FieldPlayer.h"
#include "getSteeringBehaviors.h"
#include "Team.h"
#include "Goal.h"
//#include "2D/geometry.h"
#include "Ball.h"
#include "ParamLoader.h"
#include "Telegram.h"
#include "MessageDispatcher.h"
//#include "SoccerMessages.h"

//#include "time/Regulator.h"


#define PLAYER_STATE_INFO_ON


/** 
  * Global state
  */
GlobalPlayerState* GlobalPlayerState::Instance()
{
	static GlobalPlayerState instance;
	return &instance;
}


void GlobalPlayerState::Execute(FieldPlayer* player)                                     
{
	//if a player is in possession and close to the ball reduce his max speed
	if((player->isBallWithinReceivingRange()) && (player->isControllingPlayer()))
	{
		player->SetMaxSpeed(Prm.FieldPlayerMaxSpeed);
	}
	else
	{
		player->SetMaxSpeed(Prm.FieldPlayerMaxSpeed);
	}
}


bool GlobalPlayerState::OnMessage(FieldPlayer* player, const Telegram& telegram)
{
	switch(telegram.Msg)
	{
		case Msg_ReceiveBall:
		{
			player->getgetSteering()->setTarget(*(static_cast<Ogre::Vector3*>(telegram.ExtraInfo)));
			player->getFSM()->changeState(ReceiveBall::Instance());
			return true;
		}
		break;

		case Msg_SupportAttacker:
		{
			if (player->getFSM()->isInState(*SupportAttacker::Instance()))
			{
				return true;
			}

			player->getgetSteering()->setTarget(player->getTeam()->getSupportSpot());
			player->getFSM()->changeState(SupportAttacker::Instance());
			return true;
		}
		break;

		case Msg_Wait:
		{
			player->getFSM()->changeState(Wait::Instance());
			return true;
		}
		break;

		case Msg_GoHome:
		{
			player->setDefaultHomeRegion();
			player->getFSM()->changeState(ReturnToHomeRegion::Instance());
			return true;
		}
		break;

		case Msg_PassToMe:
		{  
			FieldPlayer* receiver = static_cast<FieldPlayer*>(telegram.ExtraInfo);

			#ifdef PLAYER_STATE_INFO_ON
			debug_con << "Player " << player->getName() << " received request from " <<
						receiver->getName() << " to make pass" << "";
			#endif

			if (player->getTeam()->getReceiver() != NULL ||
				!player->isBallWithinKickingRange() )
			{
				#ifdef PLAYER_STATE_INFO_ON
				debug_con << "Player " << player->getName() << " cannot make requested pass <cannot kick ball>" << "";
				#endif

				return true;
			}
      
			//make the pass   
			player->getBall()->kick(receiver->getPosition() - player->getBall()->getPosition(),
							   Prm.MaxPassingForce);

			#ifdef PLAYER_STATE_INFO_ON
			debug_con << "Player " << player->getName() << " Passed ball to requesting player" << "";
			#endif
        
			//let the receiver know a pass is coming 
			Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
									player,
									receiver,
									Msg_ReceiveBall,
									&receiver->getPosition());

			player->getFSM()->changeState(Wait::Instance());
			player->findSupport();

			return true;
		}
		break;

	}//end switch

	return false;
}
                                

       

/** 
  * ChaseBall state
  */
ChaseBall* ChaseBall::Instance()
{
	static ChaseBall instance;
	return &instance;
}


void ChaseBall::Enter(FieldPlayer* player)
{
	player->getgetSteering()->seekOn();

	#ifdef PLAYER_STATE_INFO_ON
	debug_con << "Player " << player->getName() << " enters chase state" << "";
	#endif
}

void ChaseBall::Execute(FieldPlayer* player)                                     
{
	if (player->isBallWithinKickingRange())
	{
		player->getFSM()->changeState(KickBall::Instance());
		return;
	}
                                                                              
	if (player->isClosestTeamMemberToBall())
	{
		player->getSteering()->setTarget(player->getBall()->getPosition());
		return;
	}
  
	player->getFSM()->changeState(ReturnToHomeRegion::Instance());
}


void ChaseBall::Exit(FieldPlayer* player)
{
	player->getSteering()->SeekOff();
}



//*****************************************************************************SUPPORT ATTACKING PLAYER

SupportAttacker* SupportAttacker::Instance()
{
  static SupportAttacker instance;

  return &instance;
}


void SupportAttacker::Enter(FieldPlayer* player)
{
  player->getSteering()->ArriveOn();

  player->getSteering()->SetTarget(player->Team()->GetSupportSpot());
  
  #ifdef PLAYER_STATE_INFO_ON
  debug_con << "Player " << player->ID() << " enters support state" << "";
  #endif
}

void SupportAttacker::Execute(FieldPlayer* player)                                     
{
  //if his team loses control go back home
  if (!player->Team()->InControl())
  {
    player->getFSM()->changeState(ReturnToHomeRegion::Instance()); return;
  } 


  //if the best supporting spot changes, change the getSteering target
  if (player->Team()->GetSupportSpot() != player->getSteering()->Target())
  {    
    player->getSteering()->SetTarget(player->Team()->GetSupportSpot());

    player->getSteering()->ArriveOn();
  }

  //if this player has a shot at the goal AND the attacker can pass
  //the ball to him the attacker should pass the ball to this player
  if( player->Team()->CanShoot(player->Pos(),
                               Prm.MaxShootingForce))
  {
    player->Team()->RequestPass(player);
  }


  //if this player is located at the support spot and his team still have
  //possession, he should remain still and turn to face the ball
  if (player->AtTarget())
  {
    player->getSteering()->ArriveOff();
        
    //the player should keep his eyes on the ball!
    player->TrackBall();

    player->SetVelocity(Vector2D(0,0));

    //if not threatened by another player request a pass
    if (!player->isThreatened())
    {
      player->Team()->RequestPass(player);
    }
  }
}


void SupportAttacker::Exit(FieldPlayer* player)
{
  //set supporting player to null so that the team knows it has to 
  //determine a new one.
  player->Team()->SetSupportingPlayer(NULL);

  player->getSteering()->ArriveOff();
}




//************************************************************************ RETURN TO HOME REGION

ReturnToHomeRegion* ReturnToHomeRegion::Instance()
{
  static ReturnToHomeRegion instance;

  return &instance;
}


void ReturnToHomeRegion::Enter(FieldPlayer* player)
{
  player->getSteering()->ArriveOn();

  if (!player->HomeRegion()->Inside(player->getSteering()->Target(), Region::halfsize))
  {
    player->getSteering()->SetTarget(player->HomeRegion()->Center());
  }

  #ifdef PLAYER_STATE_INFO_ON
  debug_con << "Player " << player->ID() << " enters ReturnToHome state" << "";
  #endif
}

void ReturnToHomeRegion::Execute(FieldPlayer* player)
{
  if (player->Pitch()->GameOn())
  {
    //if the ball is nearer this player than any other team member  &&
    //there is not an assigned receiver && the goalkeeper does not gave
    //the ball, go chase it
    if ( player->isClosestTeamMemberToBall() &&
         (player->Team()->Receiver() == NULL) &&
         !player->Pitch()->GoalKeeperHasBall())
    {
      player->getFSM()->changeState(ChaseBall::Instance());

      return;
    }
  }

  //if game is on and close enough to home, change state to wait and set the 
  //player target to his current position.(so that if he gets jostled out of 
  //position he can move back to it)
  if (player->Pitch()->GameOn() && player->HomeRegion()->Inside(player->Pos(),
                                                             Region::halfsize))
  {
    player->getSteering()->SetTarget(player->Pos());
    player->getFSM()->changeState(Wait::Instance());
  }
  //if game is not on the player must return much closer to the center of his
  //home region
  else if(!player->Pitch()->GameOn() && player->AtTarget())
  {
    player->getFSM()->changeState(Wait::Instance());
  }
}

void ReturnToHomeRegion::Exit(FieldPlayer* player)
{
  player->getSteering()->ArriveOff();
}




//***************************************************************************** WAIT

Wait* Wait::Instance()
{
  static Wait instance;

  return &instance;
}


void Wait::Enter(FieldPlayer* player)
{
  #ifdef PLAYER_STATE_INFO_ON
  debug_con << "Player " << player->ID() << " enters wait state" << "";
  #endif

  //if the game is not on make sure the target is the center of the player's
  //home region. This is ensure all the players are in the correct positions
  //ready for kick off
  if (!player->Pitch()->GameOn())
  {
    player->getSteering()->SetTarget(player->HomeRegion()->Center());
  }
}

void Wait::Execute(FieldPlayer* player)
{    
  //if the player has been jostled out of position, get back in position  
  if (!player->AtTarget())
  {
    player->getSteering()->ArriveOn();

    return;
  }

  else
  {
    player->getSteering()->ArriveOff();

    player->SetVelocity(Vector2D(0,0));

    //the player should keep his eyes on the ball!
    player->TrackBall();
  }

  //if this player's team is controlling AND this player is not the attacker
  //AND is further up the field than the attacker he should request a pass.
  if ( player->Team()->InControl()    &&
     (!player->isControllingPlayer()) &&
       player->isAheadOfAttacker() )
  {
    player->Team()->RequestPass(player);

    return;
  }

  if (player->Pitch()->GameOn())
  {
   //if the ball is nearer this player than any other team member  AND
    //there is not an assigned receiver AND neither goalkeeper has
    //the ball, go chase it
   if (player->isClosestTeamMemberToBall() &&
       player->Team()->Receiver() == NULL  &&
       !player->Pitch()->GoalKeeperHasBall())
   {
     player->getFSM()->changeState(ChaseBall::Instance());

     return;
   }
  } 
}

void Wait::Exit(FieldPlayer* player){}




//************************************************************************ KICK BALL

KickBall* KickBall::Instance()
{
  static KickBall instance;

  return &instance;
}


void KickBall::Enter(FieldPlayer* player)
{
  //let the team know this player is controlling
   player->Team()->SetControllingPlayer(player);
   
   //the player can only make so many kick attempts per second.
   if (!player->isReadyForNextKick()) 
   {
     player->getFSM()->changeState(ChaseBall::Instance());
   }

   
  #ifdef PLAYER_STATE_INFO_ON
  debug_con << "Player " << player->ID() << " enters kick state" << "";
  #endif
}

void KickBall::Execute(FieldPlayer* player)
{ 
  //calculate the dot product of the vector pointing to the ball
  //and the player's heading
  Vector2D ToBall = player->Ball()->Pos() - player->Pos();
  double   dot    = player->Heading().Dot(Vec2DNormalize(ToBall)); 

  //cannot kick the ball if the goalkeeper is in possession or if it is 
  //behind the player or if there is already an assigned receiver. So just
  //continue chasing the ball
  if (player->Team()->Receiver() != NULL   ||
      player->Pitch()->GoalKeeperHasBall() ||
      (dot < 0) ) 
  {
    #ifdef PLAYER_STATE_INFO_ON
    debug_con << "Goaly has ball / ball behind player" << "";
    #endif
    
    player->getFSM()->changeState(ChaseBall::Instance());

    return;
  }

  /* Attempt a shot at the goal */

  //if a shot is possible, this vector will hold the position along the 
  //opponent's goal line the player should aim for.
  Vector2D    BallTarget;

  //the dot product is used to adjust the shooting force. The more
  //directly the ball is ahead, the more forceful the kick
  double power = Prm.MaxShootingForce * dot;

  //if it is determined that the player could score a goal from this position
  //OR if he should just kick the ball anyway, the player will attempt
  //to make the shot
  if (player->Team()->CanShoot(player->Ball()->Pos(),
                               power,
                               BallTarget)                   || 
     (RandFloat() < Prm.ChancePlayerAttemptsPotShot))
  {
   #ifdef PLAYER_STATE_INFO_ON
   debug_con << "Player " << player->ID() << " attempts a shot at " << BallTarget << "";
   #endif

   //add some noise to the kick. We don't want players who are 
   //too accurate! The amount of noise can be adjusted by altering
   //Prm.PlayerKickingAccuracy
   BallTarget = AddNoiseToKick(player->Ball()->Pos(), BallTarget);

   //this is the direction the ball will be kicked in
   Vector2D KickDirection = BallTarget - player->Ball()->Pos();
   
   player->Ball()->Kick(KickDirection, power);
    
   //change state   
   player->getFSM()->changeState(Wait::Instance());
   
   player->FindSupport();
  
   return;
 }


  /* Attempt a pass to a player */

  //if a receiver is found this will point to it
  PlayerBase* receiver = NULL;

  power = Prm.MaxPassingForce * dot;
  
  //test if there are any potential candidates available to receive a pass
  if (player->isThreatened()  &&
      player->Team()->FindPass(player,
                              receiver,
                              BallTarget,
                              power,
                              Prm.MinPassDist))
  {     
    //add some noise to the kick
    BallTarget = AddNoiseToKick(player->Ball()->Pos(), BallTarget);

    Vector2D KickDirection = BallTarget - player->Ball()->Pos();
   
    player->Ball()->Kick(KickDirection, power);

    #ifdef PLAYER_STATE_INFO_ON
    debug_con << "Player " << player->ID() << " passes the ball with force " << power << "  to player " 
              << receiver->ID() << "  Target is " << BallTarget << "";
    #endif

    Dispatcher->DispatchMsg(SEND_MSG_IMMEDIATELY,
                            player->ID(),
                            receiver->ID(),
                            Msg_ReceiveBall,
                            &BallTarget);                            

	player->getFSM()->changeState(Wait::Instance());
    player->findSupport();

    return;
  }

  //cannot shoot or pass, so dribble the ball upfield
  else
  {   
    player->FindSupport();

    player->getFSM()->changeState(Dribble::Instance());
  }   
}


//*************************************************************************** DRIBBLE

Dribble* Dribble::Instance()
{
  static Dribble instance;

  return &instance;
}


void Dribble::Enter(FieldPlayer* player)
{
  //let the team know this player is controlling
  player->Team()->SetControllingPlayer(player);

#ifdef PLAYER_STATE_INFO_ON
  debug_con << "Player " << player->ID() << " enters dribble state" << "";
  #endif
}

void Dribble::Execute(FieldPlayer* player)
{
  double dot = player->Team()->HomeGoal()->Facing().Dot(player->Heading());

  //if the ball is between the player and the home goal, it needs to swivel
  // the ball around by doing multiple small kicks and turns until the player 
  //is facing in the correct direction
  if (dot < 0)
  {
    //the player's heading is going to be rotated by a small amount (Pi/4) 
    //and then the ball will be kicked in that direction
    Vector2D direction = player->Heading();

    //calculate the sign (+/-) of the angle between the player heading and the 
    //facing direction of the goal so that the player rotates around in the 
    //correct direction
    double angle = QuarterPi * -1 *
                 player->Team()->HomeGoal()->Facing().Sign(player->Heading());

    Vec2DRotateAroundOrigin(direction, angle);

    //this value works well whjen the player is attempting to control the
    //ball and turn at the same time
    const double KickingForce = 0.8;

    player->Ball()->Kick(direction, KickingForce);
  }

  //kick the ball down the field
  else
  {
    player->Ball()->Kick(player->Team()->HomeGoal()->Facing(),
                         Prm.MaxDribbleForce);  
  }

  //the player has kicked the ball so he must now change state to follow it
  player->getFSM()->changeState(ChaseBall::Instance());
    
  return;  
}



//************************************************************************     RECEIVEBALL

ReceiveBall* ReceiveBall::Instance()
{
  static ReceiveBall instance;

  return &instance;
}


void ReceiveBall::Enter(FieldPlayer* player)
{
  //let the team know this player is receiving the ball
  player->Team()->SetReceiver(player);
  
  //this player is also now the controlling player
  player->Team()->SetControllingPlayer(player);

  //there are two types of receive behavior. One uses arrive to direct
  //the receiver to the position sent by the passer in its telegram. The
  //other uses the pursuit behavior to pursue the ball. 
  //This statement selects between them dependent on the probability
  //ChanceOfUsingArriveTypeReceiveBehavior, whether or not an opposing
  //player is close to the receiving player, and whether or not the receiving
  //player is in the opponents 'hot region' (the third of the pitch closest
  //to the opponent's goal
  const double PassThreatRadius = 70.0;

  if (( player->InHotRegion() ||
        RandFloat() < Prm.ChanceOfUsingArriveTypeReceiveBehavior) &&
     !player->Team()->isOpponentWithinRadius(player->Pos(), PassThreatRadius))
  {
    player->getSteering()->ArriveOn();
    
    #ifdef PLAYER_STATE_INFO_ON
    debug_con << "Player " << player->ID() << " enters receive state (Using Arrive)" << "";
    #endif
  }
  else
  {
    player->getSteering()->PursuitOn();

    #ifdef PLAYER_STATE_INFO_ON
    debug_con << "Player " << player->ID() << " enters receive state (Using Pursuit)" << "";
    #endif
  }
}

void ReceiveBall::Execute(FieldPlayer* player)
{
  //if the ball comes close enough to the player or if his team lose control
  //he should change state to chase the ball
  if (player->BallWithinReceivingRange() || !player->Team()->InControl())
  {
    player->getFSM()->changeState(ChaseBall::Instance());

    return;
  }  

  if (player->getSteering()->PursuitIsOn())
  {
    player->getSteering()->SetTarget(player->Ball()->Pos());
  }

  //if the player has 'arrived' at the getSteering target he should wait and
  //turn to face the ball
  if (player->AtTarget())
  {
    player->getSteering()->ArriveOff();
    player->getSteering()->PursuitOff();
    player->TrackBall();    
    player->SetVelocity(Vector2D(0,0));
  } 
}

void ReceiveBall::Exit(FieldPlayer* player)
{
  player->getSteering()->ArriveOff();
  player->getSteering()->PursuitOff();

  player->Team()->SetReceiver(NULL);
}




 



