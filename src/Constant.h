#ifndef FOOTBALL_AI_CONSTANT
#define FOOTBALL_AI_CONSTANT

#include <QString>
#include <OgreVector3.h>

#include <math.h>

const float PI = acos(-1.f);
const float MAX_VALUE = 1e99;
const float EPS = 1e-9;

const QString PHYSICS_BODY_COMPONENT = "PhysicsBodyComponent";
const QString MESH_COMPONENT = "MeshComponent";
const QString CAMERA_COMPONENT = "CameraComponent";

const Ogre::Vector3 STANDARD_HEADING = Ogre::Vector3(0.f, 0.f, 1.f);
const Ogre::Vector3 RED_TEAM_HEADING = Ogre::Vector3(1.f, 0.f, 0.f);
const Ogre::Vector3 BLUE_TEAM_HEADING = Ogre::Vector3(-1.f, 0.f, 0.f);

const double DELIVER_IMMEDIATELY = 0.0;
const float TIME_DIFF = 0.02f;

#endif