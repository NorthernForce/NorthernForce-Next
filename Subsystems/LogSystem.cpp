#include "LogSystem.h"
#include "../Robotmap.h"
#include <stdio.h>

/** 
 * @brief Private NI function needed to write to the VxWorks target 
 */
IMAQ_FUNC int Priv_SetWriteFileAllowed(UINT32 enable); 

/**
 * @brief Constructs the Logging subsystem.
 * @param level The level of logs to save to the logfile and print to
 * the console. 
 * 
 * @author Arthur Lockman
 */
LogSystem::LogSystem(LogPriority level) : 
	Subsystem("LogSystem") , 
	m_logLevel(level)
{
	this->SetDirectory("/tmp/log");
	this->PrintToFile("-----System Boot: Starting New Log-----");
	this->Print("-----System Boot: Starting New Log-----");
}
    
/**
 * @brief Handles the creation of the default command for this subsystem.
 * 
 * @author WPILib
 */
void LogSystem::InitDefaultCommand() 
{
	
}

/**
 * @brief Sets the directory in which to save the logfile.
 * @param directory The directory to save logs in.
 * 
 * @author Arthur Lockman
 */
void LogSystem::SetDirectory(const char* directory)
{
	strcpy(m_logDirectory, directory);
	Priv_SetWriteFileAllowed(1);
}

/**
 * @brief Logs a message to the logfile and to the console.
 * @param message The message to be logged.
 * @param level The level of log that this message has attached to it.
 * 
 * @author Arthur Lockman
 */
void LogSystem::LogMessage(const char* message, LogPriority level)
{
	if (level >= m_logLevel)
	{
		this->Print(message);
		this->PrintToFile(message);
	}
}

/**
 * @brief Logs a message to the console.
 * @param message The message to log. 
 * 
 * @author Arthur Lockman
 */
void LogSystem::Print(const char* message)
{
	printf("%i:  %s\n",GetFPGATime(),message);
}

/**
 * @brief Logs a message to the logfile.
 * @param message The message to log.
 * 
 * @author Arthur Lockman
 */
void LogSystem::PrintToFile(const char* message)
{
	//@TODO Log message to the logfile.
	FILE* logFile = fopen("logfile.txt","a"); 
	fprintf(logFile, "%i:  %s\n",GetFPGATime(),message);
	fclose(logFile);
}
