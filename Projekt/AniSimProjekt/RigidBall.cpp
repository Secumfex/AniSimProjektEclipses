#include "RigidBall.h"

RigidBall::RigidBall(float radius, float mass, Vector3 position, Vector3 velocity, Vector3 color){
	setPhysics(new Physics( mass, velocity, position));
	setRadius(radius);
	setColor(color);
}

void RigidBall::setPhysics(Physics* physics){
	mPhysics = physics;
	setPositionPointer(mPhysics->getPositionPointer());
}

Physics* RigidBall::getPhysics(){
	return mPhysics;
}

//Bälle kollidieren nach Ball-Kollisions-Kriterium
bool RigidBall::checkCollision(RigidBall* with){
	return Ball::checkCollision(with);
	}

void RigidBall::update(float d_t){
	mPhysics->update(d_t);
}