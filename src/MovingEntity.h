#ifndef FOOTBALL_AI_MOVING_ENTITY
#define FOOTBALL_AI_MOVING_ENTITY

#include <Scene/Node.hpp>
#include <Physics/PhysicsBodyComponent.hpp>

class MovingEntity : public dt::Node 
{
	Q_OBJECT

public:

	MovingEntity(QString name,
				 float bounding_radius,
				 float max_speed,
				 Ogre::Vector3 heading,
				 float max_force,
				 float mass,
				 float turn_rate,
				 QString mesh_handle, 
				 QString material_handle);

	void onUpdate(double time_diff);

	void onInitialize();

	Ogre::Vector3 getHeading() const;
	void setHeading(Ogre::Vector3 heading);

	Ogre::Vector3 getVelocity() const;
	void setVelocity(Ogre::Vector3 velocity);

	float getMaxSpeed() const;

	void resetPhysicsBody();

protected:

	float mBoundingRadius; 

	float mMass;

	float mMaxSpeed;

	float mMaxForce;           //!< The max force this entity can produce

	float mTurnRate;           //!< The max turning rate 

	Ogre::Vector3 mVelocity;   //!< The current velocity of this entity 

	Ogre::Vector3 mHeading;    //!< A normalized vector pointing in the direction the entity is heading.

	Ogre::Vector3 mSide;

	std::shared_ptr<dt::PhysicsBodyComponent> mPhysicsBody; //!< Pointer to physics body	
	QString mMeshHandle;                                    //!< Mesh handle
	QString mMaterialHandle;                                //!< Material handle

	const static QString MESH_COMPONENT;                    
	const static QString PHYSICS_BODY_COMPONENT;
};

#endif