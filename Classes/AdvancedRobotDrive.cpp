#include "AdvancedRobotDrive.h"
#include "../CommandBase.h"
#include <Math.h>
#include "../Robotmap.h"


namespace 
{
	const float tolerance = 0.2;
	const float thereTolerance = 0.1;
	const float rotateReduce = 1.5;
	
	//! The robot wheel base
	const float wheelBase = 25.0;
	
	//! The robot track (assumes front and rear track is the same)
	const float wheelTrack = 22.25;
	
	//! The ratio of wheelBase to wheelTrack
	const float wheelRatio = wheelBase / wheelTrack;
	
	//! The diameter of the Big Wheels on the BS Bot.
	const float bigWheelDiameter = 12.5;
	
	//! The diameter of the BS bot's Mecanum wheels.
	const float mecanumWheelDiameter = 5.5;
};

/** @brief Initializes the drive motors.
 *
 * Note the use of the comma operator (see http://en.wikipedia.org/wiki/Comma_operator)
 * which is used to print the initialization prior to the CANJaguar construction
 * which can be helpful when a device on the can bus does not respond
 *
 * @author Stephen Nutt
 */
DriveMotors::DriveMotors() try :
	m_frontLeftMotor ((printf("Initializing front left jaguar. \n"), kFrontLeftJaguar), 
		kDriveRamp, kDriveVelocityLimit, tolerance, thereTolerance),
	m_frontRightMotor((printf("Initializing front right jaguar. \n"), kFrontRightJaguar), 
		kDriveRamp, kDriveVelocityLimit, tolerance, thereTolerance),
	m_rearLeftMotor  ((printf("Initializing rear left jaguar. \n"), kRearLeftJaguar), 
		kDriveRamp, kDriveVelocityLimit, tolerance, thereTolerance),
	m_rearRightMotor ((printf("Initializing rear right jaguar. \n"), kRearRightJaguar), 
		kDriveRamp, kDriveVelocityLimit, tolerance, thereTolerance)
{
	printf("Drive jaguars successfully created. \n\r");

	DriveMotors::m_frontLeftMotor.ConfigMaxOutputVoltage(kDriveOutputVoltageLimit);
	DriveMotors::m_frontLeftMotor.ConfigNeutralMode(CANJaguar::kNeutralMode_Brake);

	DriveMotors::m_frontRightMotor.ConfigMaxOutputVoltage(kDriveOutputVoltageLimit);
	DriveMotors::m_frontRightMotor.ConfigNeutralMode(CANJaguar::kNeutralMode_Brake);

	DriveMotors::m_rearLeftMotor.ConfigMaxOutputVoltage(kDriveOutputVoltageLimit);
	DriveMotors::m_rearLeftMotor.ConfigNeutralMode(CANJaguar::kNeutralMode_Brake);

	DriveMotors::m_rearRightMotor.ConfigMaxOutputVoltage(kDriveOutputVoltageLimit);
	DriveMotors::m_rearRightMotor.ConfigNeutralMode(CANJaguar::kNeutralMode_Brake);

	printf("Drive jaguars successfully instantiated\n\r");
}
catch (exception e)
{
	printf("Error creating jaguars.");
	printf(e.what());
}

/**
 * @brief Initializes the AdvancedRobotDrive class. This class can handle
 * any kind of drive system. This class will initalize AdvancedRobotDrive to 
 * the drive mode that is specified in the constructor.
 *
 * @param mode The drive mode to drive the robot in.
 */
AdvancedRobotDrive::AdvancedRobotDrive(DriveMode mode):
    DriveMotors(),
    RobotDrive(DriveMotors::m_rearRightMotor, DriveMotors::m_rearLeftMotor,
		DriveMotors::m_frontRightMotor, DriveMotors::m_frontLeftMotor),
    m_driveMode (mode)
{

}

void AdvancedRobotDrive::DriveRobot(FRCXboxJoystick &joystick)
{
	switch (m_driveMode)
	{
		case kMecanumDrive:
			this->DriveMecanum(joystick);
			break;
		case kBSBotDrive:
			this->DriveBSBot(joystick);
			break;
		case kSkidSteer:
			this->DriveSkidSteer(joystick);
			break;
		case kSwivelSteer:
			this->DriveSwivelSteer(joystick);
			break;
	}
}

/**
 * @brief Drives the robot in Mecanum drive mode. 
 */
void AdvancedRobotDrive::DriveMecanum(FRCXboxJoystick& joystick)
{
	RobotDrive::MecanumDrive_Polar(joystick.GetLeftStickY(),joystick.GetLeftStickX(),joystick.GetRightStickX());
}

/**
 * @brief Drives the robot in BSBot drive mode. 
 */
void AdvancedRobotDrive::DriveBSBot(FRCXboxJoystick& joystick)
{
	float rotateValue = joystick.GetRightStickX();
	float moveValue = -joystick.GetLeftStickY();
	
	float frontLeft;
	float frontRight;
	float limit;
	
	moveValue   = Limit (moveValue, limit);
	rotateValue = Limit (rotateValue, limit) / rotateReduce;

	if (moveValue >= 0.0)
	{
		if (rotateValue > 0.0)
		{
			frontLeft = moveValue - rotateValue;
			frontRight = max (moveValue, rotateValue);
		}
		else
		{
			frontLeft = max (moveValue, -rotateValue);
			frontRight = moveValue + rotateValue;
		}
	}
	else
	{
		if (rotateValue > 0.0)
		{
			frontLeft = -max (-moveValue, rotateValue);
			frontRight = moveValue + rotateValue;
		}
		else
		{
			frontLeft = moveValue - rotateValue;
			frontRight = -max (-moveValue, -rotateValue);
		}
	}
	
	// Calculate the desired rear mecanum speeds.
	float rearLeft  = frontLeft  * (0.5 + wheelRatio) + frontRight * (0.5 - wheelRatio);
	float rearRight = frontRight * (0.5 + wheelRatio) + frontLeft  * (0.5 - wheelRatio);

	// Scale the rear speeds down if either of them exceed 1
	const float maxSpeed = max (fabs (rearLeft), fabs (rearRight));
	if (maxSpeed > 1.0)
	{
		rearLeft /= maxSpeed;
		rearRight /= maxSpeed;
	}

	this->PowerMotors (frontLeft, rearLeft, frontRight, rearRight);
}

/**
 * @brief Drives the robot in Skid Steer drive mode. 
 */
void AdvancedRobotDrive::DriveSkidSteer(FRCXboxJoystick& joystick)
{
	//@TODO Derive math for SkidSteer.
}

/**
 * @brief Drives the robot in Swivel Steer drive mode. 
 */
void AdvancedRobotDrive::DriveSwivelSteer(FRCXboxJoystick& joystick)
{
	//@TODO Derive math for SwivelSteer. (Do we even need this?)
}

/**
 * @brief Limits a value to a maximum amount.
 * 
 * @param input The input value to have the limit applied to.
 * @param max The limit for the input.
 */
float AdvancedRobotDrive::Limit(float input, float max)
{
    if (input > max)
    {
        return max;
    } else if (input < -max)
    {
        return -max;
    }
    return input;
}

/**
 * @brief Powers the motors on the drive train. All values
 * are taken literally. No transormations are done on the
 * values fed into this class. 
 *
 * @param frontLeft The speed of the front left motor.
 * @param frontRight The speed of the front right motor.
 * @param rearLeft The speed of the rear left motor.
 * @param rearRight The speed of the rear right motor.
 */
void AdvancedRobotDrive::PowerMotors (
		float frontLeft,
		float rearLeft,
		float frontRight,
		float rearRight)
{
	//I added this switch so that we can change what the power motors does for each drive mode. Sometimes
	//values need to be reversed for a certain chassis. This would allow for that to happen.
	switch (m_driveMode)
	{
		case kMecanumDrive:
			DriveMotors::m_rearRightMotor.SetOutput(rearRight);
			DriveMotors::m_rearLeftMotor.SetOutput(rearLeft);
			DriveMotors::m_frontRightMotor.SetOutput(frontRight);
			DriveMotors::m_frontLeftMotor.SetOutput(frontLeft);
			break;
		case kBSBotDrive:
			DriveMotors::m_rearRightMotor.SetOutput(-rearRight);
			DriveMotors::m_rearLeftMotor.SetOutput(rearLeft);
			DriveMotors::m_frontRightMotor.SetOutput(-frontRight);
			DriveMotors::m_frontLeftMotor.SetOutput(frontLeft);
			break;
		case kSkidSteer:
			DriveMotors::m_rearRightMotor.SetOutput(-rearRight);
			DriveMotors::m_rearLeftMotor.SetOutput(rearLeft);
			DriveMotors::m_frontRightMotor.SetOutput(-frontRight);
			DriveMotors::m_frontLeftMotor.SetOutput(frontLeft);
			break;
		case kSwivelSteer:
			DriveMotors::m_rearRightMotor.SetOutput(-rearRight);
			DriveMotors::m_rearLeftMotor.SetOutput(rearLeft);
			DriveMotors::m_frontRightMotor.SetOutput(-frontRight);
			DriveMotors::m_frontLeftMotor.SetOutput(frontLeft);
			break;
		default:
			DriveMotors::m_rearRightMotor.SetOutput(rearRight);
			DriveMotors::m_rearLeftMotor.SetOutput(rearLeft);
			DriveMotors::m_frontRightMotor.SetOutput(frontRight);
			DriveMotors::m_frontLeftMotor.SetOutput(frontLeft);
			break;
	}
	
	m_safetyHelper->Feed();
}
