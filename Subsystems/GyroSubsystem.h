#ifndef GYROSUBSYSTEM_H
#define GYROSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 * This subsystem is the controller for the gyro on the robot.
 * All methods for accessing and initializing the gyro
 * should go here. Call these methods with commands.
 *
 * @author arthurlockman
 */
class GyroSubsystem: public Subsystem {
private:
	
public:
	GyroSubsystem();
	void InitDefaultCommand();
};

#endif
