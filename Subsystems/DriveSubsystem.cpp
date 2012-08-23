#include "DriveSubsystem.h"
#include "../Robotmap.h"

/**
 * @brief Initializes the drive subsystem.
 * 
 * @author Arthur Lockman
 */
DriveSubsystem::DriveSubsystem() : Subsystem("DriveSubsystem") 
{
	m_drive = new AdvancedRobotDrive(kBSBotDrive);
}

/**
 * @brief Sets up the default command for the subsystem.
 * 
 * @author WPILib
 */
void DriveSubsystem::InitDefaultCommand() 
{
	
}
