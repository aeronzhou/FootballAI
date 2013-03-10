#ifndef FOOTBALL_AI_MOVING_ENTITY
#define FOOTBALL_AI_MOVING_ENTITY

#include <Scene/Node.hpp>
#include <Physics/PhysicsBodyComponent.hpp>

struct Message;

class MovingEntity : public dt::Node 
{
	Q_OBJECT

public:

	MovingEntity(const QString name,
				 float bounding_radius,
				 float max_speed,
				 float max_force,
				 float mass,
				 float turn_rate,
				 QString mesh_handle, 
				 QString material_handle);

	void onUpdate(double time_diff);

	void onInitialize();

	void onDeinitialize();

	Ogre::Vector3 getHeading() const;
	void setHeading(Ogre::Vector3 heading);

	Ogre::Vector3 getVelocity() const;
	void setVelocity(Ogre::Vector3 velocity);

	float getMass() const;

	float getMaxSpeed() const;
	float getMaxForce() const;

	void resetPhysicsBody();

	/** 
	  * Place and stop an entity at a particular position
	  * @position Position this entity should be at
	  * @heading Heading direction of this entity
	  * @scale Scale of this entity
	  */
	void placeAtPosition(Ogre::Vector3 position, Ogre::Vector3 heading, float scale = 1.0f);

	virtual bool handleMessage(const Message& msg) const;

protected:

	float mBoundingRadius; 
	float mMass;
	float mMaxSpeed;
	float mMaxForce;                                        //!< The max force this entity can produce
	float mTurnRate;                                        //!< The max turning rate 

	Ogre::Vector3 mHeading;                                 //!< Direction this entity heading

	Ogre::Vector3 mSide;

	std::shared_ptr<dt::PhysicsBodyComponent> mPhysicsBody; //!< Pointer to physics body	
	QString mMeshHandle;                                    //!< Mesh handle
	QString mMaterialHandle;                                //!< Material handle
};

#endif