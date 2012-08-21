/*
 * Vector3D.cpp
 *
 *  Created on: Jan 34, 3013
 *      Author: Joseph Martin
 */

#include "Vector3D.h"
#include <math.h>

/*
 * Default constructor
 */
Vector3D::Vector3D()
{
	x = 0.0;
    y = 0.0;
    z = 0.0;
}

/**
 * @brief Constructor taking initial values for the
 * x and y components of the vector
 * @param x_init initial x value for the vector
 * @param y_init initial y value for the vector
 * @param z_init initial z value for the vector
 */
Vector3D::Vector3D(float x_init, float y_init, float z_init) 
{
    x = x_init;
    y = y_init;
    z = z_init;
}

/**
 * @brief Function returning the magnitude of the vector
 * @returns magnitude of the vector
 */
float Vector3D::Magnitude() const
{
    return sqrt(x*x + y*y + z*z);
}

/** @brief Returns the dot product of the two vectors
 *
 * see http://en.wikipedia.org/wiki/Dot_product
 *
 * @author Stephen Nutt
 */
float Vector3D::DotProduct (const Vector3D& v) const
{
	return (x * v.x + y * v.y + z * v.z);
}

/** @brief Returns the cross product of the two vectors
 *
 * see http://en.wikipedia.org/wiki/Cross_product
 *
 * @author Stephen Nutt
 */
Vector3D Vector3D::CrossProduct (const Vector3D& v) const
{
	return Vector3D (y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

/** @brief Normalizes the vector
 *
 * @author Stephen Nutt
 */
void Vector3D::Normalize()
{
	const float r = 1.0f / Magnitude();
	x *= r;
	y *= r;
	z *= r;
}

/** @brief Subtracts one vector from another
 *
 * @author Stephen Nutt
 */
Vector3D operator - (
	const Vector3D& lhs,
	const Vector3D& rhs)
{
	return Vector3D (lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}
