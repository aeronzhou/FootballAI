#ifndef FOOTBALL_AI_FIELD_PLAYER
#define FOOTBALL_AI_FIELD_PLAYER

#include "Player.h"

class FieldPlayer : public Player
{
public:

	FieldPlayer(QString name,
		float bounding_radius,
		float max_speed,
		Ogre::Vector3 heading,
		float max_force,
		float mass,
		float turn_rate,
		QString mesh_handle, 
		QString material_handle, 
		Team* team);
};

#endif