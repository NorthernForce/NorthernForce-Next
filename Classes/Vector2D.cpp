/*
 * Vector2D.cpp
 *
 *  Created on: Jan 24, 2012
 *      Author: Joseph Martin
 */

#include "Vector2D.h"
#include <math.h>

/*
 * Default constructor
 */
Vector2D::Vector2D()
{
	x = 0.0;
    y = 0.0;
}

/*
 * @breif Constructor taking initial values for the
 * x and y components of the vector
 * @param x_init initial x value for the vector
 * @param y_init initial y value for the vector
 */
Vector2D::Vector2D(float x_init, float y_init) 
{
    x = x_init;
    y = y_init;
}

/*
 * @brief Function returning the magnitude of the vector
 * @returns magnitude of the vector
 */
float Vector2D::GetMagnitude()
{
    return sqrt(x*x + y*y);
}
