#include "Ball.h"

Ball::Ball(float radius, Vector3* position){
	mRadius = radius;
	mPosition = position;

	mColor = Vector3(1.0, 0.75, 0.0);
}

Ball::~Ball(){

}

void Ball::draw(){
	//mPhysics.updatePosition();

	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR,currentColor);
	glColor3f(mColor.getX(),mColor.getY(),mColor.getZ());

	glPushMatrix();
		glTranslatef(mPosition->getX(),mPosition->getY(),mPosition->getZ());
		//glutWireSphere(mRadius, 20,10);
		glutSolidSphere(mRadius,15,10);
	glPopMatrix();

	glColor4f(currentColor[0],currentColor[1],currentColor[2],currentColor[3]);
}

float Ball::getRadius(){
	return mRadius;
}

Vector3 Ball::getColor(){
	return mColor;
}

Vector3* Ball::getPositionPointer(){
	return mPosition;
}

Vector3 Ball::getPosition(){
	return *mPosition;
}

void Ball::setPosition(float x, float y, float z){
	mPosition->setX(x);
	mPosition->setY(y);
	mPosition->setZ(z);
}

void Ball::setPosition(Vector3& position){
	setPosition(position.getX(),position.getY(),position.getZ());
}

void Ball::setColor(Vector3 color){
	mColor = color;
}

void Ball::setColor(float r, float g, float b){
	mColor.setX(r);
	mColor.setY(g);
	mColor.setZ(b);
}

void Ball::setPositionPointer(Vector3* position){
	mPosition = position;
}

void Ball::setRadius(float radius){
	mRadius = radius;
}

/**
 * true when with.radius + this.radius > distance of with and this
 */
bool Ball::checkCollision(Ball* with){
				float combinedRadius = getRadius() +with->getRadius(); 
				float distance =  (getPosition() - (with->getPosition())).length();
				if ( combinedRadius >= distance ) {
					return true;
				}
				else{
					return false;
				}
}