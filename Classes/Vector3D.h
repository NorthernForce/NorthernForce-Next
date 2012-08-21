#ifndef VECTOR3D_H
#define VECTOR3D_H
/*
 * Vector3D.h
 *
 *  Created on: Jan 24, 2012
 *      Author: Joseph Martin
 */

/*
 * Description:
 */
class Vector3D {
public:
    Vector3D();
    Vector3D(float x_init, float y_init, float z_init);
    float Magnitude() const;
	float DotProduct (const Vector3D& v) const;
	Vector3D CrossProduct (const Vector3D& v) const;
	void Normalize();
	friend Vector3D operator - (const Vector3D& lhs, const Vector3D& rhs);

    float x;
    float y;
    float z;
};
#endif
