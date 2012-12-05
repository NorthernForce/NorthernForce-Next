#include "DriveSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/TeleopDriveCommand.h"

/**
 * @brief Initializes the drive subsystem.
 * 
 * @author Arthur Lockman
 */
DriveSubsystem::DriveSubsystem(DriveMode mode) : Subsystem("DriveSubsystem") 
{
	m_drive = new AdvancedRobotDrive(mode);
	CommandBase::s_Log->LogMessage("Drive system initiated.",kLogPriorityDebug);
}

/**
 * @brief Sets up the default command for the subsystem.
 * 
 * @author WPILib
 */
void DriveSubsystem::InitDefaultCommand() 
{
}

/**
 * @brief Drive the robot in teleop mode.
 * 
 * @author Arthur Lockman
 */
void DriveSubsystem::DriveTeleop(FRCXboxJoystick &stick)
{
	m_drive->DriveRobot(stick);
}

/**
 * @brief Drive the robot in autonomous.
 */
void DriveSubsystem::DriveAutonomous()
{
	//@TODO: Complete this method.
}
