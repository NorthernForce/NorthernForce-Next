#ifndef OPERATORINTERFACE_H
#define OPERATORINTERFACE_H 

#include <WPILib.h>
#include "Classes/FRCXboxJoystick.h"
#include "Classes/Attack3Joystick.h"
#include "CommandBase.h"

/**
 * @brief This class is used to handle all operator input, hence its name, OI. Any
 * classes for interacting with the operator (joysticks, input devices, dashboards)
 * should go in this class. 
 *
 * @author WPILib
 */
class OperatorInterface 
{
private:
	FRCXboxJoystick m_driverStick;
	Attack3Joystick m_manipulatorStick;
public:
	OperatorInterface();
	FRCXboxJoystick& GetDriverStick();
	Attack3Joystick& GetManipulatorStick();
};

#endif
