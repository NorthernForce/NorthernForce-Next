#include "CommandBase.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(const char *name) : Command(name) 
{
	
}

CommandBase::CommandBase() : Command() 
{

}

// Initialize a single static instance of all subsystems to NULL.
OI* CommandBase::oi = NULL;
DriveSubsystem* CommandBase::s_Drive = NULL;

/**
 * @brief This is where all of the instances of subsystems will be created. 
 * Each of them should have a unique name, so that they are clearly identifiable
 * from others.
 */
void CommandBase::init() 
{
	oi = new OI();
	s_Drive = new DriveSubsystem();
}
