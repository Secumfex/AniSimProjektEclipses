#pragma once

#include "BasisApplication.h"
#include "Vector3.h"

class Ball
{
private:
	float mRadius;
	Vector3* mPosition;
	Vector3 mColor;
public:
		
Ball(float radius = 0.5, Vector3* position = new Vector3(0,0,0));
~Ball();		
		/* Getter & Setter*/
float getRadius(); Vector3 getColor();
Vector3* getPositionPointer();
Vector3 getPosition();

void setRadius(float radius); void setColor(float r, float g, float b); void setColor(Vector3 color);
void setPositionPointer(Vector3* position);
void setPosition(float x,float y,float z);
void setPosition(Vector3& position);

/*Funktionalität*/

bool virtual checkCollision(Ball* with);

void draw();
};

