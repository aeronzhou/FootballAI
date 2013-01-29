#ifndef FOOTBALL_AI_INITIAL_STATE
#define FOOTBALL_AI_INITIAL_STATE

#include <Scene/State.hpp>

/**
  * A state to initialize resource
  */
class InitialState : public dt::State
{
	Q_OBJECT

public:

	InitialState() {}

    void onInitialize();

    void onDeinitialize();

    void updateStateFrame(double simulation_frame_time);
};

#endif