#include "FootballGame.h"
#include "Pitch.h"
#include "MainGameCamera.h"
#include "ParamLoader.h"
#include "Constant.h"

#include <Graphics/DisplayManager.hpp>

#include <Graphics/LightComponent.hpp>

#include <Core/ResourceManager.hpp>

#include <OgreProcedural.h> 

#include <iostream>


void FootballGame::onInitialize() 
{
	auto scene = addScene(new dt::Scene("scene_01"));
	// This one is very important
	OgreProcedural::Root::getInstance()->sceneManager = scene->getSceneManager();

	// Enable debug mode
	if (Prm.PhysicsShowDebug) 
	{
		scene->getPhysicsWorld()->setShowDebug(true);
	}

	MainGameCamera* camnode = (MainGameCamera*)scene->addChildNode(new MainGameCamera("MainGameCamera")).get();
	camnode->setPosition(Prm.CameraPosX, Prm.CameraPosY, Prm.CameraPosZ);

	// Initialize light
	auto light_node = scene->addChildNode(new dt::Node("LightNode"));
	light_node->setPosition(Ogre::Vector3(-20.0f, 200.0f, 10.0f));
	light_node->addComponent(new dt::LightComponent("light"));

	auto pitch = scene->addChildNode(new Pitch());	
}

void FootballGame::onDeinitialize() 
{

}

void FootballGame::updateStateFrame(double simulation_frame_time) 
{

}