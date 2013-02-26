#include "FieldPlayer.h"

FieldPlayer::FieldPlayer(QString name,
	float bounding_radius,
	float max_speed,
	Ogre::Vector3 heading,
	float max_force,
	float mass,
	float turn_rate,
	QString mesh_handle, 
	QString material_handle, 
	Team* team)
: Player(name, bounding_radius, max_speed, heading, max_force, mass, turn_rate,
         mesh_handle, material_handle, team) {}