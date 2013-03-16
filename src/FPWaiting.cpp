#include "FieldPlayerState.h"
#include "FieldPlayer.h"
#include "MessageDeliverer.h"
#include "Constant.h"

// Waiting
Waiting* Waiting::get()
{
	static Waiting instance;
	return &instance;
}

void Waiting::enter(FieldPlayer*)
{
	dt::Logger::get().debug("Enter to Back To Origin...");
}

void Waiting::execute(FieldPlayer*)
{

}

void Waiting::exit(FieldPlayer*)
{

}

bool Waiting::onMessage(FieldPlayer*, const Message&)
{
	return false;
}