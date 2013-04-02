#include "CoolingTimeComponent.h"

CoolingTimeComponent::CoolingTimeComponent(double cooling_time, QString name /* = "CoolingTimeComponent" */)
	: Component(name), mCoolingTime(cooling_time), mCurTime(0) {}

void CoolingTimeComponent::onInitialize() {}

void CoolingTimeComponent::onUpdate(double time_diff)
{
	mCurTime += time_diff;
}

bool CoolingTimeComponent::ready()
{
	if (mCurTime > mCoolingTime)
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