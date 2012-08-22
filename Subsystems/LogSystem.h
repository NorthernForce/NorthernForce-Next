#ifndef LOGSYSTEM_H
#define LOGSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../Robotmap.h"

/**
 * @brief A logging system for the Robot. This log will log anything
 * to the netconsole, as well as save all logs to a logfile. What this
 * log system outputs depends on which log level is set at its initialization.
 * In addition, every log message that is passed in must have a log level 
 * attached to it. This way, the console doesn't get clogged up with 
 * non-critical messages unless testing is going on.
 *
 * @author arthurlockman
 */
class LogSystem: public Subsystem 
{
private:
	void Print(string* message);
	void PrintToFile(string* message);
	LogLevel m_logLevel;
public:
	LogSystem(LogLevel level);
	void InitDefaultCommand();
	void LogMessage(string* message, LogLevel level);
};

#endif