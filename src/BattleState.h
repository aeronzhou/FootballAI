#ifndef FOOTBALL_AI_BATTLE_STATE
#define FOOTBALL_AI_BATTLE_STATE

#include <Scene/State.hpp>

/**
  * A state to show soccer pitch and all players
  */
class BattleState : public dt::State 
{
	Q_OBJECT

public:

	BattleState() {}

    void onInitialize();

    void onDeinitialize();

    void updateStateFrame(double simulation_frame_time);
};

#endif