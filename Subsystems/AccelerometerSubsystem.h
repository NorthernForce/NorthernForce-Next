#ifndef ACCELEROMETERSUBSYSTEM_H
#define ACCELEROMETERSUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 * This subsystem is the controller for the accelerometer on the robot.
 * All methods for accessing and initializing the Accelerometer
 * should go here. Call these methods with commands.
 *
 * @author arthurlockman
 */
class AccelerometerSubsystem: public Subsystem {
private:
	
public:
	AccelerometerSubsystem();
	void InitDefaultCommand();
};

#endif
