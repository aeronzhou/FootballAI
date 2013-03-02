#include "BattleState.h"
#include "Pitch.h"
#include "ParamLoader.h"
#include "Constant.h"

#include <Graphics/DisplayManager.hpp>

#include <Graphics/LightComponent.hpp>

#include <Core/ResourceManager.hpp>


#include <OgreProcedural.h>

#include <iostream>


void BattleState::onInitialize() 
{
	auto scene = addScene(new dt::Scene("scene_01"));
	// This one is very important
	OgreProcedural::Root::getInstance()->sceneManager = scene->getSceneManager();

	// Enable debug mode
	//scene->getPhysicsWorld()->setShowDebug(true);

	dt::Node::NodeSP camnode = scene->addChildNode(new dt::Node("CameraNode"));
	camnode->setPosition(Ogre::Vector3(Prm.CameraPosX, Prm.CameraPosY, Prm.CameraPosZ));
	camnode->addComponent(new dt::CameraComponent(CAMERA_COMPONENT));
	camnode->findComponent<dt::CameraComponent>(CAMERA_COMPONENT)->lookAt(Prm.CameraLookAtX, 
		Prm.CameraLookAtY, Prm.CameraLookAtZ);

	// Initialize light
	auto light_node = scene->addChildNode(new dt::Node("LightNode"));
	light_node->setPosition(Ogre::Vector3(-20.0f, 200.0f, 10.0f));
	light_node->addComponent(new dt::LightComponent("light"));

	auto pitch = scene->addChildNode(new Pitch());	
}

void BattleState::onDeinitialize() 
{

}

void BattleState::updateStateFrame(double simulation_frame_time) 
{

}