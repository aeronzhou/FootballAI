#include "FieldPlayerState.h"

FindRightPlace* FindRightPlace::get()
{
	static FindRightPlace instance;
	return &instance;
}

void FindRightPlace::enter(FieldPlayer* player)
{
	
}

void FindRightPlace::execute(FieldPlayer* player)
{

}

void FindRightPlace::exit(FieldPlayer*)
{

}

bool FindRightPlace::onMessage(FieldPlayer*, const Message&)
{
	return false;
}