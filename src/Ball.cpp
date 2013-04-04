#include "Ball.h"
#include "ParamLoader.h"
#include "Utils.h"

#include <Graphics/MeshComponent.hpp>
#include <Physics/PhysicsBodyComponent.hpp>

#include <math.h>

Ball::Ball(QString name, QString mesh_handle, QString material_handle)
	: MovingEntity(name, 12.f, 12.f, Prm.BallMass, 10.f, mesh_handle, material_handle) {}

void Ball::onInitialize() 
{
	MovingEntity::onInitialize();

	addComponent(new dt::MeshComponent(mMeshHandle, mMaterialHandle, MESH_COMPONENT));
	mPhysicsBody = addComponent(new dt::PhysicsBodyComponent(MESH_COMPONENT, PHYSICS_BODY_COMPONENT, 
		dt::PhysicsBodyComponent::CONVEX, mMass));
	mPhysicsBody->getRigidBody()->setFriction(Prm.BallFriction);

	mResistanceCoolTime = addComponent(new CoolingTimeComponent(Prm.BallResistanceInterval));
}

void Ball::onUpdate(double time_diff)
{
	this->mIsUpdatingAfterChange = (time_diff == 0);

	// Update every frame

	Ogre::Vector3 velocity = getVelocity();
	Ogre::Vector3 vground = Vector3To2(velocity);

	// 模拟一个阻力
	if (!vground.isZeroLength() && mResistanceCoolTime->ready())
	{
		kick(-vground.normalisedCopy(), Prm.BallResistance);
	}

	MovingEntity::onUpdate(time_diff);
}

void Ball::kick(Ogre::Vector3 direction, float force)
{
	direction = Vector3To2Normalise(direction) * force;
	
	// Give it a momentary force
	mPhysicsBody->applyCentralImpulse(BtOgre::Convert::toBullet(direction));
}

float Ball::getProperForceToKick(float distance)
{
	static const float KICK_REAL_FACTOR = 1.0f;

	float force = sqrt(double(2 * Prm.BallDeceleration * distance)) * mMass;
	
	return std::min(Prm.PlayerMaxPassingForce, force * KICK_REAL_FACTOR);
}

Ogre::Vector3 Ball::getVelocity() const
{
	return BtOgre::Convert::toOgre(mPhysicsBody->getRigidBody()->getLinearVelocity());
}

void Ball::setVelocity(Ogre::Vector3 velocity) 
{
	mPhysicsBody->getRigidBody()->setLinearVelocity(BtOgre::Convert::toBullet(velocity));
}

Ogre::Vector3 Ball::getHeading() const 
{
	return getVelocity().normalisedCopy();
}

float Ball::getTimeToGoThroughDistance(float length, float force)
{
	float u = force / mMass;

	// v^2 - u^2 = 2 * a * s
	float g = 2 * (-Prm.BallDeceleration) * length + u * u;

	if (g < 0)
	{
		return -1;
	}	
	float v = sqrt(double(g));

	return (v - u) / (-Prm.BallDeceleration);
}

/************************************************************************/
/* Function for debug                                                   */
/************************************************************************/
void Ball::testTimeSpentByInitialForce(float length, float force)
{
	static bool flag = 0;
	static bool start = 1;
	static bool end = 0;
	static double start_time = 0;
	static float initial_speed = 0;
	static Ogre::Vector3 pre_pos = getPosition();

	start_time += TIME_DIFF;

	if (start)
	{
		start = 0;
		start_time = clock();
		this->kick(Ogre::Vector3(1, 0, 0), force);
		std::cout << "Initial Velocity = " << (initial_speed = getVelocity().length() ) << std::endl;
	}

	if (!flag && getPosition().distance(pre_pos) > length)
	{
		flag = 1;
		std::cout << "Test Real Time Spent: " << (clock() - start_time) / CLOCKS_PER_SEC << std::endl;
	}

	if (!end && getVelocity().length() < 0.05)
	{
		end = 1;
		double time_spent = (clock() - start_time) / CLOCKS_PER_SEC;
		float all_length = getPosition().distance(pre_pos);
		std::cout << "All Time Spent: " << time_spent << std::endl;
		std::cout << "Distance Gone Througth: " << all_length << std::endl;
		std::cout << "Deceleration: " << -initial_speed / time_spent << std::endl;
	}
}

void Ball::stop()
{
	setVelocity(Ogre::Vector3::ZERO); 
}

Ogre::Vector3 Ball::getOldPos() const 
{ 
	return mOldPos;
}