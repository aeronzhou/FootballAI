#include "CoolingTimeComponent.h"

const double CoolingTimeComponent::EPS = 1e-9;

CoolingTimeComponent::CoolingTimeComponent(double cooling_time, QString name /* = "CoolingTimeComponent" */)
	: Component(name), mCoolingTime(cooling_time), mCurTime(0) {}

void CoolingTimeComponent::onInitialize() {}

void CoolingTimeComponent::onUpdate(double time_diff)
{
	if (isEnabled())
	{
		mCurTime += time_diff;

		if (mCurTime > mCoolingTime + EPS)
		{
			mCurTime = mCoolingTime;	
		}
	}
}

bool CoolingTimeComponent::ready()
{
	if (mCurTime + EPS > mCoolingTime)
	{
		mCurTime = 0;
		return true;
	}

	return false;
}

void CoolingTimeComponent::reset()
{
	mCurTime = 0;
}