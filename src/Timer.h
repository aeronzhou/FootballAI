#ifndef FOOTBALL_AI_TIMER
#define FOOTBALL_AI_TIMER

/** 
  * A timer class for the game
  */
class Timer 
{
public:

	static Timer& get();

	/** 
	  * Update function, called every frame manually
	  */
	void onUpdate(double time_diff);

	double getCurrentTime() const;

	bool isGameStopped() const;

	bool isGameOver();

	void stop();

	void start();

	void reset();

private:

	/** 
	  * Default Constructor
	  * @param total_minutes Minutes for game to continue
	  */
	Timer(double total_minutes);

private:

	double mTotalGameTime;          //!< Total game time, seconds as the unit

	double mCurrentTime;            //!< Current time

	bool mGameStopped;              //!< Indicate if the game is on

	double mCriticalMinutes;        //!< The last few minutes considered as critical so as to push players
	                                //!< to play more considerately
};

#endif