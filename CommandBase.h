#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include "Commands/Command.h"
#include "Subsystems/ExampleSubsystem.h"
#include "OI.h"


/**
 * @brief The base for all commands. All atomic commands should subclass CommandBase.
 * CommandBase stores creates and stores each control system. To access a
 * subsystem elsewhere in your code in the code use CommandBase.examplesubsystem.
 * 
 * @author WPILib, modified by Arthur Lockman
 */
class CommandBase: public Command {
public:
	CommandBase(const char *name);
	CommandBase();
	static void init();
	
	// Create a single static instance of all subsystems.
	static ExampleSubsystem *examplesubsystem;
	static OI *oi;
};

#endif
