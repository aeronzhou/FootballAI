#include "FieldPlayerState.h"
#include "FieldPlayer.h"
#include "MessageDeliverer.h"
#include "Constant.h"


// Dribbling
Dribbling* Dribbling::get()
{
	static Dribbling instance;
	return &instance;
}

void Dribbling::enter(FieldPlayer*)
{
	dt::Logger::get().debug("Enter to Dribbling state...");
}

void Dribbling::execute(FieldPlayer*)
{

}

void Dribbling::exit(FieldPlayer*)
{

}

bool Dribbling::onMessage(FieldPlayer*, const Message&)
{
	return false;
}