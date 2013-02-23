#include "BattleState.h"
#include "Pitch.h"
#include "ParamLoader.h"

#include <Graphics/DisplayManager.hpp>


//#include <Graphics/MeshComponent.hpp>

#include <Graphics/LightComponent.hpp>

#include <Core/ResourceManager.hpp>


#include <OgreProcedural.h>

#include <iostream>


void BattleState::onInitialize() 
{
	auto scene = addScene(new dt::Scene("scene_01"));
	// This one is very important
	OgreProcedural::Root::getInstance()->sceneManager = scene->getSceneManager();

	scene->getPhysicsWorld()->setShowDebug(true);

	dt::Node::NodeSP camnode = scene->addChildNode(new dt::Node("camnode"));
	camnode->setPosition(Ogre::Vector3(0.0f, 15.f, 10.f));
	camnode->addComponent(new dt::CameraComponent("camera"));
	camnode->findComponent<dt::CameraComponent>("camera")->lookAt(0, 0, 0);

	// Initialize light
	auto light_node = scene->addChildNode(new dt::Node("lightnode"));
	light_node->setPosition(Ogre::Vector3(-2000.0f, 2000.0f, 1000.0f));
	light_node->addComponent(new dt::LightComponent("light"));

	auto pitch = scene->addChildNode(new Pitch());	
}

void BattleState::onDeinitialize() 
{

}

void BattleState::updateStateFrame(double simulation_frame_time) 
{

}