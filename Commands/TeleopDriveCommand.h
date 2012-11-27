#ifndef TELEOPDRIVECOMMAND_H
#define TELEOPDRIVECOMMAND_H

#include "../CommandBase.h"

/**
 * Drives the robot in Teleop mode.
 *
 * @author arthurlockman
 */
class TeleopDriveCommand: public CommandBase {
public:
	TeleopDriveCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
