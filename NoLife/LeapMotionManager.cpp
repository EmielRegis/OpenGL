#include "LeapMotionManager.h"

LeapMotionManager::LeapMotionManager()
{
	keyMap.insert(std::pair<VirtualLeapMotionKeyEnum, bool>(KEY_VIRTUAL_A, false));
	keyMap.insert(std::pair<VirtualLeapMotionKeyEnum, bool>(KEY_VIRTUAL_ALT_LEFT, false));
	keyMap.insert(std::pair<VirtualLeapMotionKeyEnum, bool>(KEY_VIRTUAL_ALT_RIGHT, false));
	keyMap.insert(std::pair<VirtualLeapMotionKeyEnum, bool>(KEY_VIRTUAL_BACKSPACE, false));
	keyMap.insert(std::pair<VirtualLeapMotionKeyEnum, bool>(KEY_VIRTUAL_D, false));
	keyMap.insert(std::pair<VirtualLeapMotionKeyEnum, bool>(KEY_VIRTUAL_E, false));
	keyMap.insert(std::pair<VirtualLeapMotionKeyEnum, bool>(KEY_VIRTUAL_ESCAPE, false));
	keyMap.insert(std::pair<VirtualLeapMotionKeyEnum, bool>(KEY_VIRTUAL_S, false));
	keyMap.insert(std::pair<VirtualLeapMotionKeyEnum, bool>(KEY_VIRTUAL_SHIFT_LEFT, false));
	keyMap.insert(std::pair<VirtualLeapMotionKeyEnum, bool>(KEY_VIRTUAL_SHIFT_RIGHT, false));
	keyMap.insert(std::pair<VirtualLeapMotionKeyEnum, bool>(KEY_VIRTUAL_SPACE, false));
	keyMap.insert(std::pair<VirtualLeapMotionKeyEnum, bool>(KEY_VIRTUAL_W, false));
	keyMap.insert(std::pair<VirtualLeapMotionKeyEnum, bool>(KEY_VIRTUAL_LEFT_MOUSE_BUTTON, false));
	keyMap.insert(std::pair<VirtualLeapMotionKeyEnum, bool>(KEY_VIRTUAL_RIGHT_MOUSE_BUTTON, false));
	keyMap.insert(std::pair<VirtualLeapMotionKeyEnum, bool>(KEY_VIRTUAL_MOUSE_MOVE_BACKWARD, false));
	keyMap.insert(std::pair<VirtualLeapMotionKeyEnum, bool>(KEY_VIRTUAL_MOUSE_MOVE_DOWN, false));
	keyMap.insert(std::pair<VirtualLeapMotionKeyEnum, bool>(KEY_VIRTUAL_MOUSE_MOVE_FORWARD, false));
	keyMap.insert(std::pair<VirtualLeapMotionKeyEnum, bool>(KEY_VIRTUAL_MOUSE_MOVE_LEFT, false));
	keyMap.insert(std::pair<VirtualLeapMotionKeyEnum, bool>(KEY_VIRTUAL_MOUSE_MOVE_RIGHT, false));
	keyMap.insert(std::pair<VirtualLeapMotionKeyEnum, bool>(KEY_VIRTUAL_MOUSE_MOVE_UP, false));
}

LeapMotionManager::~LeapMotionManager()
{

}

void LeapMotionManager::onConnect(const Controller& controller)
{
	autoFireMotionListeners = false;
	controller.enableGesture(Gesture::TYPE_CIRCLE);
	controller.enableGesture(Gesture::TYPE_SWIPE);
	controller.enableGesture(Gesture::TYPE_KEY_TAP);
	controller.enableGesture(Gesture::TYPE_SCREEN_TAP);

	std::cout << "LeapMotion Manager Connected" << std::endl;
}

void LeapMotionManager::onFrame(const Controller& controller)
{
	for each (Hand hand in controller.frame().hands())
	{
		/*if (hand.isLeft())
			leftHand = hand;
		else if (hand.isRight())
			rightHand = hand;*/

	}

	if (controller.frame().hands().count() > 1)
	{
		Hand leftHand = controller.frame().hands().leftmost();
		Hand rightHand = controller.frame().hands().rightmost();

			keyMap[KEY_VIRTUAL_W] = (leftHand.palmPosition().z < -30);
			keyMap[KEY_VIRTUAL_S] = (leftHand.palmPosition().z > 30);
			keyMap[KEY_VIRTUAL_A] = (leftHand.palmPosition().x < -120);
			keyMap[KEY_VIRTUAL_D] = (leftHand.palmPosition().x > -70);

			keyMap[KEY_VIRTUAL_E] = (leftHand.grabStrength() > 0.7f);

			keyMap[KEY_VIRTUAL_LEFT_MOUSE_BUTTON] = (rightHand.grabStrength() > 0.75f);

			if (rightHand.pinchStrength() < 0.75f)
			{
				keyMap[KEY_VIRTUAL_MOUSE_MOVE_DOWN] = (rightHand.palmVelocity().y > 200);
				keyMap[KEY_VIRTUAL_MOUSE_MOVE_UP] = (rightHand.palmVelocity().y < -200);
				keyMap[KEY_VIRTUAL_MOUSE_MOVE_LEFT] = (rightHand.palmVelocity().x < -200);
				keyMap[KEY_VIRTUAL_MOUSE_MOVE_RIGHT] = (rightHand.palmVelocity().x > 200);
				keyMap[KEY_VIRTUAL_MOUSE_MOVE_FORWARD] = (rightHand.palmVelocity().z < -200);
				keyMap[KEY_VIRTUAL_MOUSE_MOVE_BACKWARD] = (rightHand.palmVelocity().z > 200);
			}

			//keyMap[KEY_VIRTUAL_MOUSE_MOVE_BACKWARD] = controller.frame().gesture(Gesture::TYPE_SWIPE).
	}
	else
	{
		keyMap[KEY_VIRTUAL_W] = keyMap[KEY_VIRTUAL_S] = keyMap[KEY_VIRTUAL_A] = keyMap[KEY_VIRTUAL_D] = false;
		keyMap[KEY_VIRTUAL_LEFT_MOUSE_BUTTON] = keyMap[KEY_VIRTUAL_RIGHT_MOUSE_BUTTON] = false;
		keyMap[KEY_VIRTUAL_MOUSE_MOVE_BACKWARD] = keyMap[KEY_VIRTUAL_MOUSE_MOVE_DOWN] = keyMap[KEY_VIRTUAL_MOUSE_MOVE_FORWARD] =
			keyMap[KEY_VIRTUAL_MOUSE_MOVE_LEFT] = keyMap[KEY_VIRTUAL_MOUSE_MOVE_RIGHT] = keyMap[KEY_VIRTUAL_MOUSE_MOVE_UP] = false;
	}

	if (autoFireMotionListeners)
		motionListeners(this);
}

void LeapMotionManager::fireMotionListeners()
{
	motionListeners(this);
}

void LeapMotionManager::addMotionListener(std::function<void(LeapMotionManager*)> listener)
{
	motionListeners.connect(listener);
}

bool LeapMotionManager::isKeyActive(VirtualLeapMotionKeyEnum key)
{
	return keyMap[key];
}

