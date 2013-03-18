#include "FieldPlayerState.h"
#include "FieldPlayer.h"
#include "MessageDeliverer.h"
#include "Constant.h"

// Passing
Passing* Passing::get()
{
	static Passing instance;
	return &instance;
}

void Passing::enter(FieldPlayer* player)
{
	dt::Logger::get().debug("Enter to Passing state...");
}

void Passing::execute(FieldPlayer*)
{

}

void Passing::exit(FieldPlayer*)
{

}

bool Passing::onMessage(FieldPlayer*, const Message&)
{
	return false;
}