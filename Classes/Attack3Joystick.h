#ifndef ATTACK3JOYSTICK_H
#define ATTACK3JOYSTICK_H

#include <WPILib.h>
#include "../Robotmap.h"
#include "Joystick.h"

/**
 * @brief This class is the driver for the Logitech
 * Attack 3 Joystick. This joystick is often used at
 * competition to control the robot. This joystick 
 * is not deadband adjusted, as these joysticks do
 * not seem to need deadband calibration.
 *
 * This class also contains JoystickButtons for all of the 
 * buttons that are available on the XBox joystick itself. 
 * These buttons can be assigned by calling 
 * <code>[stick].[button].WhenPressed()</code>.
 * 
 * @author Arthur Lockman
 */
class Attack3Joystick: public Joystick {
private:
	//Private methods.
public:
	Attack3Joystick(int port);

	float GetStickX();
	float GetStickY();
	float GetPOT();

	bool GetTrigger();
	bool GetButton2();
	bool GetButton3();
	bool GetButton4();
	bool GetButton5();
	bool GetButton6();
	bool GetButton7();
	bool GetButton8();
	bool GetButton9();
	bool GetButton10();
	bool GetButton11();
	bool GetButton12();

	JoystickButton Trigger;
	JoystickButton Button2;
	JoystickButton Button3;
	JoystickButton Button4;
	JoystickButton Button5;
	JoystickButton Button6;
	JoystickButton Button7;
	JoystickButton Button8;
	JoystickButton Button9;
	JoystickButton Button10;
	JoystickButton Button11;
	JoystickButton Button12;
};

#endif
