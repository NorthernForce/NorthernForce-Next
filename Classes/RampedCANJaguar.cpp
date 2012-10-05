/*
 * RampedCANJaguar.cpp
 *
 *  Created on: Feb 11, 2012
 *      Author: Joseph Martin
 */

#include "RampedCANJaguar.h"
#include "../Robotmap.h"
#include <math.h>

RampedCANJaguar::RampedCANJaguar(int deviceNumber,
                                 float ramp,
                                 float maxAcceleration,
								 float tolerance = 0,
                                 float thereTolerance = 0) :
    CANJaguar(deviceNumber),
    m_maxAcceleration(maxAcceleration),
    m_maxVelocity(ramp),
    m_tolerance(tolerance),
    m_thereTolerance(thereTolerance),
    m_prevTime(0.0),
    m_prevPosition(0.0),
    m_prevVelocity(0.0),
    m_prevAccel(0.0),
    m_ramp(ramp)
{
	; // do nothing, all initialization is done above
}

// Prints out the maximun velocity and acceleration.
void RampedCANJaguar::PrintLimits()
{
    printf("max Velocity: %f",m_maxVelocity);
    printf("max Acceleration: %f",m_maxAcceleration);
}

// While using position control, if the magnitude of the difference from the
// target position to the current position is within tolerance, a 'linear' 
// ramp is used; the position is changed by a fraction of the difference.
// If the difference is within thereTolerance, the position is set to the
// target position.
void RampedCANJaguar::SetTolerance(float tolerance, float thereTolerance)
{
    m_tolerance = tolerance;
    m_thereTolerance = thereTolerance;
}

// set the max velocity
void RampedCANJaguar::SetMaxVelocity(float maxVelocity)
{
    m_maxVelocity = maxVelocity;
}

// sets the maximum acceleration
void RampedCANJaguar::SetMaxAcceleration(float maxAcceleration)
{
    m_maxAcceleration = maxAcceleration;
}

void RampedCANJaguar::DisableControl()
{
    //m_prevPosition = 0.0; // <-- Not sure why we did this last year
    CANJaguar::DisableControl();
}

void RampedCANJaguar::EnableControl(float encoderInitialPosition)
{
    CANJaguar::EnableControl(encoderInitialPosition);
    m_prevPosition = encoderInitialPosition;
}

void RampedCANJaguar::EnableControl()
{
    // we must pass m_prevPosition to the 
    // underlying CANJaguar method so that 
    // it knows where it is.
    CANJaguar::EnableControl(m_prevPosition);
}

void RampedCANJaguar::SetOutput(float outputValue)
{
    //float curTime = GetTime();
    float position = m_prevPosition;
    float velocity = m_prevVelocity;
    float accel = m_prevAccel;
    switch(GetControlMode()) 
    {
        case kPercentVbus:
        case kSpeed:
            // We are in speed mode or percent vbus mode, which is similar enough.
            //
            // When a sudden change in velocity is given, we do not actually want
            // to command the jaguar to go that fast right away. Instead, every time
            // this method is called, the velocity is increased by a fraction of the
            // difference between the current velocity (labled here m_prevVelocity, 
            // because velocity is the value that the velocity will be set to) and the
            // desired output.
        	velocity = m_prevVelocity + (outputValue-m_prevVelocity) * m_ramp;
            CANJaguar::Set(velocity);
            break;
        case kPosition:
            // deltaP is the difference from our current and desired positions.
            float deltaP = outputValue - m_prevPosition;

            if ( fabs(deltaP) <= m_thereTolerance )
            {
                // If we are within a small range of our destination,
                // set the output there.
                CANJaguar::Set(outputValue);
                break;
            }
            else if ( fabs(deltaP) <= m_tolerance )
            {
                // Otherwise, if we are close, but not too close,
                // that is, within m_tolerance of our destination, 
                // use a linear ramp; this is pretty much the same
                // as the velocity control, moving 4/10 closer to the
                // destination each time this method is called.
                CANJaguar::Set(m_prevPosition + 0.4*(deltaP));
                break;
            }

            // Otherwise, we are far enough away that we want to be careful
            // not to try to change the position too fast, or to accelerate
            // too quickly.

            // deltaT is a constant set to 0.02 (20 ms), the approximate amount
            // of time which should pass between calls to this function.

            // Limit the predicted velocity (change in position over change in time)
            // to m_maxVelocity. If the predicted velocity was negative (and greater
            // in magnitude than m_maxAcceleration), set velocity to -m_maxVelocity.
            velocity = Limit( deltaP/deltaT, m_maxVelocity );

            // Limit the predicted acceleration (change in velocity over change in time)
            // to m_maxAcceleration. If the predicted acceleration was negative (and
            // greater in magnitude than m_maxAcceleration) the acceleration will be set
            // to -m_maxAcceleration.
            accel = Limit( (velocity - m_prevVelocity) / deltaT, m_maxAcceleration );

            // Because the acceleration may have been changed, we must recalculate the
            // desired velocity.
            velocity = m_prevVelocity + accel * deltaT;

            // Now, calculate the desired position
            position = m_prevPosition + m_prevVelocity * deltaT + 0.5 * accel * deltaT * deltaT;

            /* This section should not be required, but I wrote it a long time ago, so I am
             * not 100% sure.
            if ( 
                    (((outputValue - position) > 0) && 
                     ((outputValue - position) < ((velocity*velocity) / (2*m_maxAcceleration)))) || 
                    (((outputValue - position) < 0) && 
                     ((outputValue - position) > -((velocity*velocity) / (2*m_maxAcceleration)))) 
               )
            {
                if( (deltaP) > m_tolerance )
                {
                    accel = -m_maxAcceleration;
                } else if ( (deltaP) < -m_tolerance )
                {
                    accel = m_maxAcceleration;
                } 
                velocity = m_prevVelocity + accel * deltaT;
                position = m_prevPosition + m_prevVelocity * deltaT + 0.5 * accel * deltaT * deltaT;
            }
            */

            // Finally, command the jaguar to move to the desired position
            // Remember, though, that this is not the target position, but 
            // the position calculated to ensure that we do not exceed the
            // maximum velocity or acceleration values.
            CANJaguar::Set(position);
            break;
        default:
            // We are not using either velocity or position control;
            // set the can output value without any changes.
            CANJaguar::Set(outputValue);
            break;
    }

    // Store the new velocity and acceleration values for use next
    // time this function is called.
    m_prevVelocity = velocity;
    m_prevAccel = accel;
}

// Limits input to be within max of 0. Preserves sign.
float RampedCANJaguar::Limit(float input, float max) 
{
    if (input > max)
    {
        return max;
    } else if (input < -max)
    {
        return -max;
    }
    return input;
}

// Returns the last position the jaguar was commanded to move to.
float RampedCANJaguar::Get()
{
    return m_prevPosition;
}
