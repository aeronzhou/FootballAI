#include "FieldPlayerState.h"

// KickingBall
KickingBall* KickingBall::get()
{
	static KickingBall instance;
	return &instance;
}

void KickingBall::enter(FieldPlayer*)
{
}

void KickingBall::execute(FieldPlayer* player)
{

}

void KickingBall::exit(FieldPlayer*)
{

}

bool KickingBall::onMessage(FieldPlayer*, const Message&)
{
	return false;
}