#include "TeleopDriveCommand.h"

TeleopDriveCommand::TeleopDriveCommand() :
	CommandBase("TeleopDriveCommand")
{
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(s_Drive);
}

// Called just before this Command runs the first time
void TeleopDriveCommand::Initialize() 
{
	CommandBase::s_Log->LogMessage("Starting teleop drive command.",kLogPrioritySystem);
}

// Called repeatedly when this Command is scheduled to run
void TeleopDriveCommand::Execute() 
{
	s_Drive->DriveTeleop(oi->GetDriverStick());
}

// Make this return true when this Command no longer needs to run execute()
bool TeleopDriveCommand::IsFinished() 
{
	return false;
}

// Called once after isFinished returns true
void TeleopDriveCommand::End() 
{
	CommandBase::s_Log->LogMessage("Stopping teleop drive command.",kLogPrioritySystem);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TeleopDriveCommand::Interrupted() 
{
	CommandBase::s_Log->LogMessage("Teleop drive command interrupted!.",kLogPriorityError);
}
