#ifndef ADVANCEDROBOTDRIVE_H
#define ADVANCEDROBOTDRIVE_H
#include <WPILib.h>
#include "../Robotmap.h"
#include "FRCXboxJoystick.h"
#include "RampedCanJaguar.h"

/** @brief Initializes the drive motors
 *
 * @author Stephen Nutt
 */
class DriveMotors
{
public:
	DriveMotors();
	mutable RampedCANJaguar m_frontLeftMotor;
	mutable RampedCANJaguar m_frontRightMotor;
	mutable RampedCANJaguar m_rearLeftMotor;
	mutable RampedCANJaguar m_rearRightMotor;
};

class AdvancedRobotDrive:
	private DriveMotors,
	private RobotDrive
{
public:
	AdvancedRobotDrive(DriveMode mode);
	void DriveRobot(FRCXboxJoystick &joystick);
	void DriveAutonomous();

	void Stop();

	/**
	 * @brief Returns whether or not the drive system is alive.
	 */
	inline bool IsAlive() const
    { 
    	return m_safetyHelper->IsAlive(); 
    }

private:
	void DriveMecanum(FRCXboxJoystick& joystick);
	void DriveBSBot(FRCXboxJoystick& joystick);
	void DriveSkidSteer(FRCXboxJoystick& joystick);
	void DriveSwivelSteer(FRCXboxJoystick& joystick);

	void PowerMotors(float frontLeft, float rearLeft, float frontRight, float rearRight);
	float Limit(float input, float max);

	DriveMode m_driveMode;

	/**
	 * @brief Returns the square of the val preserving the sign of val
	 *
	 * @example SignedSquare (2) == 4 and SignedSquare (-2) == -4
	 */
	inline float SignedSquare (float val)
	{
		return val < 0 ? - (val * val) : (val * val);
	}

};

#endif
