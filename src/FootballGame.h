#ifndef FOOTBALL_AI_FOOTBALL_GAME
#define FOOTBALL_AI_FOOTBALL_GAME

#include <Scene/State.hpp>

/**
  * A state to show soccer pitch and all players
  */
class FootballGame : public dt::State 
{
	Q_OBJECT

public:

	FootballGame() {}

    void onInitialize();

    void onDeinitialize();

    void updateStateFrame(double simulation_frame_time);
};

#endif