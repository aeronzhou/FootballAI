#ifndef FOOTBALL_AI_FIELD_PLAYER_STATE
#define FOOTBALL_AI_FIELD_PLAYER_STATE

#include "State.h"

class FieldPlayer;

// FieldPlayerGlobalState
class FieldPlayerGlobalState: public State<FieldPlayer>
{
public:
	static FieldPlayerGlobalState* get();

	void enter(FieldPlayer*) {}

	void execute(FieldPlayer*) {}

	void exit(FieldPlayer*) {}

	bool onMessage(FieldPlayer*, const Message&);
};

// BackToOrigin
class BackToOrigin: public State<FieldPlayer>
{
public:
	static BackToOrigin* get();

	void enter(FieldPlayer*);

	void execute(FieldPlayer*);

	void exit(FieldPlayer*);

	bool onMessage(FieldPlayer*, const Message&);
};

// Waiting
class Waiting: public State<FieldPlayer>
{
public:
	static Waiting* get();

	void enter(FieldPlayer*);

	void execute(FieldPlayer*);

	void exit(FieldPlayer*);

	bool onMessage(FieldPlayer*, const Message&);
};

#endif