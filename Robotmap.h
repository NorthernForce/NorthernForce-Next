#ifndef ROBOTMAP_H
#define ROBOTMAP_H

/**
 * @brief The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around. All global variables should be stored here. This file should also
 * be included in every header file that is created, so that it is accessible anywhere.
 */

/**
 * @brief The addresses of the CAN Jaguars on the CAN bus.
 */
enum JaguarAddress
{
	kFrontLeftJaguar = 2,
	kFrontRightJaguar = 4,
	kRearLeftJaguar = 3,
	kRearRightJaguar = 5,
};

 /*
  * @brief The button ports on the XBox Joystick, as interpreted by the cRIO.
  */
enum XBoxJoystickButtonPort
{
	kXBoxButtonA = 1,
	kXBoxButtonB = 2,
	kXBoxButtonX = 3,
	kXBoxButtonY = 4,
	kXBoxButtonLeft = 5,
	kXBoxButtonRight = 6,
	kXBoxButtonBack = 7,
	kXBoxButtonStart = 8,
	kXBoxButtonLeftJoystick = 9,
	kXBoxButtonRightJoystick = 10,
};

/*
 * @brief The button ports on the Attack 3 Joystick.
 */
 enum Attack3JoystickPort
 {
 	kAttackJoystickButtonTrigger = 1,
 	kAttackJoystickButton2 = 2,
 	kAttackJoystickButton3 = 3,
 	kAttackJoystickButton4 = 4,
 	kAttackJoystickButton5 = 5,
 	kAttackJoystickButton6 = 6,
 	kAttackJoystickButton7 = 7,
 	kAttackJoystickButton8 = 8,
 	kAttackJoystickButton9 = 9,
 	kAttackJoystickButton10 = 10,
 	kAttackJoystickButton11 = 11,
 	kAttackJoystickButton12 = 12,
 };

/**
 * @brief The port numbers of the analog sticks on the XBox Joystick.
 */
enum XBoxJoystickAnalogStickPort
{
	kLeftStickX = 1,
	kLeftStickY = 2,
	kRightStickX = 3,
	kRightStickY = 4,
	kTriggers = 5,
};


/**
 * @brief The different possible drive modes that the robot can use.
 */
enum DriveMode
{
	kMecanumDrive = 1,
	kBSBotDrive = 2,
	kSkidSteer = 3,
	kSwivelSteer = 4,
};

/**
 * @brief The different possible levels of debug logging.
 */
enum LogPriority
{
	kLogPriorityCritical = 1,
	kLogPriorityMedium = 2,
	kLogPriorityDebug = 3,
};

//Variables that concern driving the robot.
static const float kDriveP = 0.0;
static const float kDriveI = 0.0;
static const float kDriveD = 0.0;
static const int kDriveOutputVoltageLimit = 12;
static const int kDriveEncoderLines = 256;
static const bool kUseEncoders = false;
static const float kDriveRamp = 0.4;
static const float kDriveVelocityLimit = 1.0;

#endif
