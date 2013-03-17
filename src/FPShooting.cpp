#include "FieldPlayerState.h"
#include "FieldPlayer.h"
#include "MessageDeliverer.h"
#include "Constant.h"

// Shooting
Shooting* Shooting::get()
{
	static Shooting instance;
	return &instance;
}

void Shooting::enter(FieldPlayer*)
{
	dt::Logger::get().debug("Enter to Shooting state...");
}

void Shooting::execute(FieldPlayer*)
{

}

void Shooting::exit(FieldPlayer*)
{

}

bool Shooting::onMessage(FieldPlayer*, const Message&)
{
	return false;
}