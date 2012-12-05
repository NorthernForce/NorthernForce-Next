#include "CommandBase.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(const char *name) : Command(name) 
{
	
}

CommandBase::CommandBase() : Command() 
{

}

// Initialize a single static instance of all subsystems to NULL.
OperatorInterface* CommandBase::oi = NULL;
DriveSubsystem* CommandBase::s_Drive = NULL;
LogSystem* CommandBase::s_Log = NULL;

/**
 * @brief This is where all of the instances of subsystems will be created. 
 * Each of them should have a unique name, so that they are clearly identifiable
 * from others.
 */
void CommandBase::init() 
{
	oi = new OperatorInterface();
	s_Drive = new DriveSubsystem(kBSBotDrive);
	s_Log = new LogSystem(kLogPrioritySystem);
}
