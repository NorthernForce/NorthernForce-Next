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
	m_frontLeftMotor ((CommandBase::s_Log->LogMessage("Initializing front left jaguar."), kFrontLeftJaguar), 
		kDriveRamp, kDriveVelocityLimit, tolerance, thereTolerance),
	m_frontRightMotor((CommandBase::s_Log->LogMessage("Initializing front right jaguar."), kFrontRightJaguar), 
		kDriveRamp, kDriveVelocityLimit, tolerance, thereTolerance),
	m_rearLeftMotor  ((CommandBase::s_Log->LogMessage("Initializing rear left jaguar."), kRearLeftJaguar), 
		kDriveRamp, kDriveVelocityLimit, tolerance, thereTolerance),
	m_rearRightMotor ((CommandBase::s_Log->LogMessage("Initializing rear right jaguar."), kRearRightJaguar), 
		kDriveRamp, kDriveVelocityLimit, tolerance, thereTolerance)
{
	CommandBase::s_Log->LogMessage("Drive jaguars successfully created.",kLogPriorityDebug);

	DriveMotors::m_frontLeftMotor.ConfigMaxOutputVoltage(kDriveOutputVoltageLimit);
	DriveMotors::m_frontLeftMotor.ConfigNeutralMode(CANJaguar::kNeutralMode_Brake);

	DriveMotors::m_frontRightMotor.ConfigMaxOutputVoltage(kDriveOutputVoltageLimit);
	DriveMotors::m_frontRightMotor.ConfigNeutralMode(CANJaguar::kNeutralMode_Brake);

	DriveMotors::m_rearLeftMotor.ConfigMaxOutputVoltage(kDriveOutputVoltageLimit);
	DriveMotors::m_rearLeftMotor.ConfigNeutralMode(CANJaguar::kNeutralMode_Brake);

	DriveMotors::m_rearRightMotor.ConfigMaxOutputVoltage(kDriveOutputVoltageLimit);
	DriveMotors::m_rearRightMotor.ConfigNeutralMode(CANJaguar::kNeutralMode_Brake);

	CommandBase::s_Log->LogMessage("Drive jaguars successfully instantiated.",kLogPriorityDebug);
}
catch (exception e)
{
	CommandBase::s_Log->LogMessage("Error creating jaguars.",kLogPriorityError);
	CommandBase::s_Log->LogMessage(e.what(),kLogPriorityError);
}

/**
 * @brief Initializes the AdvancedRobotDrive class. This class can handle
 * any kind of drive system. This class will initalize AdvancedRobotDrive to 
 * the drive mode that is specified in the constructor.
 * @param mode The drive mode to drive the robot in.
 * 
 * @author Arthur Lockman
 */
AdvancedRobotDrive::AdvancedRobotDrive(DriveMode mode):
    DriveMotors(),
    RobotDrive(DriveMotors::m_rearRightMotor, DriveMotors::m_rearLeftMotor,
		DriveMotors::m_frontRightMotor, DriveMotors::m_frontLeftMotor)
{
	m_driveMode = mode;
}

/**
 * @brief Drive the robot. Call this from a command. Do not use
 * this for autonomous. See AdvancedRobotDrive::DriveAutonomous.
 * @param joystick The joystick to pull the drive commands.
 * @see AdvancedRobotDrive::DriveAutonomous
 * 
 * @author Arthur Lockman
 */
void AdvancedRobotDrive::DriveRobot(FRCXboxJoystick &joystick)
{
	CommandBase::s_Log->LogMessage("Entering AdvancedRobotDrive::DriveRobot.",kLogPrioritySystem);
	m_safetyHelper->Feed();
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
 * @brief Drives the robot in autonomous mode. Do not use this to
 * drive in teleoperated mode. See AdvancedRobotDrive::DriveRobot.
 * @see AdvancedRobotDrive::DriveRobot
 * 
 * @author Arthur Lockman
 */
void AdvancedRobotDrive::DriveAutonomous()
{
	m_safetyHelper->Feed();
	//@TODO: Develop code for driving in Autonomous mode.
}

/**
 * @brief Drives the robot in Mecanum drive mode. 
 * 
 * @author Arthur Lockman
 */
void AdvancedRobotDrive::DriveMecanum(FRCXboxJoystick& joystick)
{
	m_safetyHelper->Feed();
	RobotDrive::MecanumDrive_Polar(joystick.GetLeftStickY(),joystick.GetLeftStickX(),joystick.GetRightStickX());
}

/**
 * @brief Drives the robot in BSBot drive mode. 
 * 
 * @author Arthur Lockman, Conor McGrory
 */
void AdvancedRobotDrive::DriveBSBot(FRCXboxJoystick& joystick)
{
	m_safetyHelper->Feed();
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
	m_safetyHelper->Feed();
	//@TODO Derive math for SkidSteer.
}

/**
 * @brief Drives the robot in Swivel Steer drive mode. 
 */
void AdvancedRobotDrive::DriveSwivelSteer(FRCXboxJoystick& joystick)
{
	m_safetyHelper->Feed();
	//@TODO Derive math for SwivelSteer. (Do we even need this?)
}

/**
 * @brief Limits a value to a maximum amount.
 * @param input The input value to have the limit applied to.
 * @param max The limit for the input.
 * 
 * @author Joseph Martin
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
 * @author Arthur Lockman
 */
void AdvancedRobotDrive::PowerMotors (
		float frontLeft,
		float rearLeft,
		float frontRight,
		float rearRight)
{
	m_safetyHelper->Feed();
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
