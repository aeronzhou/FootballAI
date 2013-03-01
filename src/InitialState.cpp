#include "InitialState.h"
#include "BattleState.h"

#include <Graphics/DisplayManager.hpp>
#include <Scene/StateManager.hpp>
#include <Core/ResourceManager.hpp>


void InitialState::onInitialize() 
{
	dt::ResourceManager::get()->addResourceLocation("model", "FileSystem");
	dt::ResourceManager::get()->addResourceLocation("model/Sinbad.zip", "Zip", true);

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	dt::DisplayManager::get()->setWindowSize(800, 600);

}

void InitialState::onDeinitialize() {}

void InitialState::updateStateFrame(double simulation_frame_time) 
{
	dt::StateManager::get()->setNewState(new BattleState());	
}