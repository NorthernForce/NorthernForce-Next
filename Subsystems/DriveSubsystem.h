#ifndef DRIVESUBSYSTEM_H
#define DRIVESUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../Classes/AdvancedRobotDrive.h"

/**
 * @brief This class is the drive subsystem for the robot. Call the methods 
 * that are in this subsystem from Commands.
 *
 * @author Arthur Lockman
 */
class DriveSubsystem: public Subsystem 
{
private:
	AdvancedRobotDrive *m_drive;
public:
	DriveSubsystem();
	void InitDefaultCommand();
};

#endif
