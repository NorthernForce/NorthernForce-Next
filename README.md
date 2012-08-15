NorthernForce Next
====

The next generation base code for FIRST Team 172.

The hope with this codebase is to provide a solid foundation for all future robots that are based on C++, and to provide work to be done during the pre-season. The hope is that this base is done as soon as the regular season comes around, so that we can focus on doing other tasks aside from getting the robot moving during the season, such as game specific functions.

Prefixes
---
The code will contain certain prefixes to help discern which kinds of things the variables are. Here are the different types of prefixes that will be found in the code, and what they mean.
- **k**Variable - The **k** in front of a variable will mean that this variable is a constant. These should all be defined within Robotmap.h.
- **s**Variable - The **s** in front of a variable will mean that this variable is a subsystem. Subsystems are defined within their own class files, and the variables to access them are defined within CommandBase.
- **o**Variable - The **o** in front of a variable will mean that this variable is an operator interface element. These are defined within the OI class.

Commenting
---
All methods and classes must be properly documented. This makes the code much easier to read. Documentation is added by using comments within your code. 