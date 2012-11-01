#include "GyroSubsystem.h"
#include "../Robotmap.h"

/**
 * @brief Initialize the Gyro.
 */
GyroSubsystem::GyroSubsystem() : Subsystem("GyroSubsystem") 
{
	
}
    
/**
 * @brief Initialize the default command for the subsystem. Required by WPI.
 * @author WPILib
 */
void GyroSubsystem::InitDefaultCommand() 
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}
