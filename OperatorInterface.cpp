#include "OperatorInterface.h"
#include "Robotmap.h"

/**
 * @brief Initialize the operator interface.
 */
OperatorInterface::OperatorInterface() try :
	m_driverStick(1),
	m_manipulatorStick(2)
{
	//Create joystick buttons for each joystick here, using
	//stick.button.WhenPressed(new Command()); or stick.button.WhileHeld(new Command());
    
	CommandBase::s_Log->LogMessage("All OI elements created successfully.",kLogPriorityDebug);
}
catch (exception e)
{
	CommandBase::s_Log->LogMessage("Operator interface failed to initialize.",kLogPriorityError);
}

/**
 * @brief Returns the drive joystick.
 * @return The drive joystick.
 */
FRCXboxJoystick& OperatorInterface::GetDriverStick()
{
	return m_driverStick;
}

/**
 * @brief Returns the manipulator joystick.
 * @return The manipulator joystick.
 */
Attack3Joystick& OperatorInterface::GetManipulatorStick()
{
	return m_manipulatorStick;
}
