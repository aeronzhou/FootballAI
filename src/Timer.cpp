#include "Timer.h"
#include "ParamLoader.h"

Timer& Timer::get()
{
	static Timer singleton(Prm.TotalGameTime);
	return singleton;
}

Timer::Timer(double total_minutes): 
	mTotalGameTime(total_minutes * 60), mCurrentTime(0), mGameStopped(true), mCriticalMinutes(Prm.LastCriticalMinutes) {}

double Timer::getCurrentTime() const 
{
	return mCurrentTime;
}

bool Timer::isGameStopped() const 
{
	return mGameStopped;
}

void Timer::onUpdate(double time_diff)
{
	if (!mGameStopped)
	{
		mCurrentTime += time_diff;
	}
}

bool Timer::isGameOver()
{
	if (mCurrentTime > mTotalGameTime)
	{
		stop();
		return true;
	}

	return false;
}

void Timer::stop()
{
	mGameStopped = true;
}

void Timer::reset()
{
	mCurrentTime = 0;
	mGameStopped = true;
}

void Timer::start()
{
	mGameStopped = false;
}