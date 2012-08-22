#include "LogSystem.h"
#include "../Robotmap.h"

/**
 * @brief Constructs the Logging subsystem.
 * 
 * @param level The level of logs to save to the logfile and print to
 * the console. 
 */
LogSystem::LogSystem(LogLevel level) : 
	Subsystem("LogSystem") , 
	m_logLevel(level)
{
	//@TODO Create or continue an existing log file for logging.
}
    
/**
 * @brief Handles the creation of the default command for this subsystem.
 */
void LogSystem::InitDefaultCommand() 
{
	
}

/**
 * @brief Logs a message to the logfile and to the console.
 * 
 * @param message The message to be logged.
 * @param level The level of log that this message has attached to it.
 */
void LogSystem::LogMessage(string* message, LogLevel level)
{
	if (level >= m_logLevel)
	{
		this->Print(message);
	}
}

/**
 * @brief Logs a message to the console.
 * 
 * @param message The message to log. 
 */
void LogSystem::Print(string* message)
{
	printf("%s\n",message);
}

/**
 * @brief Logs a message to the logfile.
 * 
 * @param message The message to log.
 */
void LogSystem::PrintToFile(string* message)
{
	//@TODO Log message to the logfile.
}
