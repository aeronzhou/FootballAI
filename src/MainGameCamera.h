#ifndef FOOTBALL_AI_MAIN_GAME_CAMERA
#define FOOTBALL_AI_MAIN_GAME_CAMERA

#include <Scene/Node.hpp>

#include <Input/InputManager.hpp>

#include <OIS.h>

class MainGameCamera : public dt::Node
{
	Q_OBJECT

public:

	MainGameCamera(const QString& name);

	void onInitialize();

	void onDeinitialize();

	void onUpdate(double time_diff);

private slots:
    /**
      * Handles the events triggered by pressing a key or a mouse button.
      * @param input_code The input code.
      * @param event The event argument.
      */
    void _handleButtonDown(dt::InputManager::InputCode input_code, const OIS::EventArg& event);

    /**
      * Handles the events triggered by moving the mouse.
      * @param event The mouse-moving event.
      */
    void _handleMouseMove(const OIS::MouseEvent& event);

    /**
      * Handles the events triggered by releasing a key or a mouse button.
      * @param input_code The input code.
      * @param event The event argument.
      */
    void _handleButtonUp(dt::InputManager::InputCode input_code, const OIS::EventArg& event);


private:

	Ogre::Vector3 mMove;               //!< Moving vector
	float mSpeed;                      //!< Speed
	float mMouseSensitivity;           //!< MouseSensitivity
};
#endif