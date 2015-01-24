#include "Leap.h"
#include "boost/signal.hpp"
#include <functional>

using namespace Leap;

enum VirtualLeapMotionKeyEnum
{
	KEY_VIRTUAL_SPACE = 20,
	KEY_VIRTUAL_BACKSPACE = 8,
	KEY_VIRTUAL_SHIFT_LEFT = 0x0070,
	KEY_VIRTUAL_SHIFT_RIGHT = 0x0071,
	KEY_VIRTUAL_ALT_LEFT = 0x0074,
	KEY_VIRTUAL_ALT_RIGHT = 0x0075,
	KEY_VIRTUAL_ESCAPE = 27,
	KEY_VIRTUAL_W = (int) 'w',
	KEY_VIRTUAL_S = (int) 's',
	KEY_VIRTUAL_A = (int) 'a',
	KEY_VIRTUAL_D = (int) 'd',
	KEY_VIRTUAL_E = (int) 'e',
	KEY_VIRTUAL_LEFT_MOUSE_BUTTON = 455,
	KEY_VIRTUAL_RIGHT_MOUSE_BUTTON = 456,
	KEY_VIRTUAL_MOUSE_MOVE_LEFT = 457,
	KEY_VIRTUAL_MOUSE_MOVE_RIGHT = 458,
	KEY_VIRTUAL_MOUSE_MOVE_FORWARD = 459,
	KEY_VIRTUAL_MOUSE_MOVE_BACKWARD = 460,
	KEY_VIRTUAL_MOUSE_MOVE_UP = 461,
	KEY_VIRTUAL_MOUSE_MOVE_DOWN = 462,
	KEY_VIRTUAL_I = 463,
	KEY_VIRTUAL_O = 464,
	KEY_VIRTUAL_Z = 465,
	KEY_VIRTUAL_X = 466,
	KEY_VIRTUAL_C = 467
};

class LeapMotionManager : public Listener {
protected:
	//Hand *leftHand, *rightHand;
	boost::signal<void(LeapMotionManager*)> motionListeners;
	std::map<VirtualLeapMotionKeyEnum, bool> keyMap;

public:
	bool autoFireMotionListeners;
	virtual void onConnect(const Controller&);
	virtual void onFrame(const Controller&);
	virtual void fireMotionListeners();
	virtual void addMotionListener(std::function<void(LeapMotionManager*)> listener);
	bool isKeyActive(VirtualLeapMotionKeyEnum key);
	LeapMotionManager();
	~LeapMotionManager();
};