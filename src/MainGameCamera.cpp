#include "MainGameCamera.h"
#include "ParamLoader.h"
#include "Constant.h"

#include <Graphics/CameraComponent.hpp>

MainGameCamera::MainGameCamera(const QString& name): dt::Node(name), mMove(Ogre::Vector3::ZERO) {}

void MainGameCamera::onInitialize()
{
	if(!QObject::connect(dt::InputManager::get(), SIGNAL(sPressed(dt::InputManager::InputCode, const OIS::EventArg&)),
		this,                SLOT(_handleButtonDown(dt::InputManager::InputCode, const OIS::EventArg&)))) {
			dt::Logger::get().error("Cannot connect signal sPressed with " + getName()
				+ "'s input handling slot.");
	}

	if(!QObject::connect(dt::InputManager::get(), SIGNAL(sReleased(dt::InputManager::InputCode, const OIS::EventArg&)),
		this,                SLOT(_handleButtonUp(dt::InputManager::InputCode, const OIS::EventArg&)))) {
			dt::Logger::get().error("Cannot connect signal sReleased with " + getName()
				+ "'s input handling slot.");
	}

	if(!QObject::connect(dt::InputManager::get(), SIGNAL(sMouseMoved(const OIS::MouseEvent&)),
		this,                SLOT(_handleMouseMove(const OIS::MouseEvent&)))) {
			dt::Logger::get().error("Cannot connect signal sMouseMoved with " + getName()
				+ "'s input handling slot.");
	}

	mSpeed = Prm.CameraSpeed;
	mMouseSensitivity = Prm.MouseSensitivity;
	
	addComponent(new dt::CameraComponent(CAMERA_COMPONENT));
}

void MainGameCamera::onDeinitialize()
{
	if(!QObject::disconnect(this, SLOT(_handleButtonDown(dt::InputManager::InputCode, const OIS::EventArg&)))) {
		dt::Logger::get().error("Cannot disconnect signal sPressed with " + getName()
			+ "'s input handling slot.");
	}

	if(!QObject::disconnect(this, SLOT(_handleButtonUp(dt::InputManager::InputCode, const OIS::EventArg&)))) {
		dt::Logger::get().error("Cannot disconnect signal sReleased with " + getName()
			+ "'s input handling slot.");
	}

	if(!QObject::disconnect(this, SLOT(_handleMouseMove(const OIS::MouseEvent&)))) {
		dt::Logger::get().error("Cannot disconnect signal sMouseMoved with " + getName()
			+ "'s input handling slot.");
	}
}

void MainGameCamera::onUpdate(double time_diff)
{
	mIsUpdatingAfterChange = (time_diff == 0);

	Ogre::Vector3 move = Ogre::Quaternion(getRotation().getYaw(), Ogre::Vector3(0, 1, 0)) * mMove.normalisedCopy();
	
	move *= mSpeed;

	setPosition(getPosition() + move);

	dt::Node::onUpdate(time_diff);
}

void MainGameCamera::_handleButtonDown(dt::InputManager::InputCode input_code, const OIS::EventArg& event)
{
	if (input_code == dt::InputManager::KC_W || input_code == dt::InputManager::KC_UP) {
		mMove.z -= 1.f;
	}
	if (input_code == dt::InputManager::KC_S || input_code == dt::InputManager::KC_DOWN) {
		mMove.z += 1.f;
	}
	if (input_code == dt::InputManager::KC_A || input_code == dt::InputManager::KC_LEFT) {
		mMove.x -= 1.f;
	}
	if (input_code == dt::InputManager::KC_D || input_code == dt::InputManager::KC_RIGHT) {
		mMove.x += 1.f;
	}
	if (input_code == dt::InputManager::KC_SPACE) {
		mMove.y += 1.f;
	}
	if (input_code == dt::InputManager::KC_LSHIFT) {
		mMove.y -= 1.f;
	}
}

void MainGameCamera::_handleButtonUp(dt::InputManager::InputCode input_code, const OIS::EventArg& event)
{
	if (input_code == dt::InputManager::KC_W || input_code == dt::InputManager::KC_UP) {
		mMove.z += 1.f;
	}
	if (input_code == dt::InputManager::KC_S || input_code == dt::InputManager::KC_DOWN) {
		mMove.z -= 1.f;
	}
	if (input_code == dt::InputManager::KC_A || input_code == dt::InputManager::KC_LEFT) {
		mMove.x += 1.f;
	}
	if (input_code == dt::InputManager::KC_D || input_code == dt::InputManager::KC_RIGHT) {
		mMove.x -= 1.f;
	}
	if (input_code == dt::InputManager::KC_SPACE) {
		mMove.y -= 1.f;
	}
	if (input_code == dt::InputManager::KC_LSHIFT) {
		mMove.y += 1.f;
	}
}

void MainGameCamera::_handleMouseMove(const OIS::MouseEvent& event)
{
	float factor = mMouseSensitivity * -0.01;

	float dx = event.state.X.rel * factor;
	float dy = event.state.Y.rel * factor * (1); //(mMouseYInversed ? -1 : 1);

	if(dx != 0 || dy != 0) {
		// watch out for da gimbal lock !!

		Ogre::Matrix3 orientMatrix;
		getRotation().ToRotationMatrix(orientMatrix);

		Ogre::Radian yaw, pitch, roll;
		orientMatrix.ToEulerAnglesYXZ(yaw, pitch, roll);

		pitch += Ogre::Radian(dy);
		yaw += Ogre::Radian(dx);

		// do not let it look completely vertical, or the yaw will break
		if(pitch > Ogre::Degree(89.9))
			pitch = Ogre::Degree(89.9);

		if(pitch < Ogre::Degree(-89.9))
			pitch = Ogre::Degree(-89.9);

		orientMatrix.FromEulerAnglesYXZ(yaw, pitch, roll);

		Ogre::Quaternion rot;
		rot.FromRotationMatrix(orientMatrix);
		setRotation(rot);
	}
}
