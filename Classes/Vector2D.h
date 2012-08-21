#ifndef VECTOR2D_H
#define VECTOR2D_H
/*
 * Vector2D.h
 *
 *  Created on: Jan 24, 2012
 *      Author: Joseph Martin
 */

/*
 * Description:
 */
class Vector2D {
public:
    Vector2D();
    Vector2D(float x_init, float y_init);
    float GetMagnitude();
    float x;
    float y;
};
#endif
