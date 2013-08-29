#include "RigidBody.h"

/***************Rigid Body ********************/
RigidBody::RigidBody(float mass, Matrix3 Ibody){
	setMass(mass);
	setIbody(Ibody);
}

void RigidBody::setIbody(Matrix3 Ibody){
	mIbody = Ibody;
	Ibody.invert();
	mIbodyinv = Ibody;
}

void RigidBody::setMass(float mass){
	mMass = mass;
}

void RigidBody::update(float d_t){

}

/***************Rigid Block ********************/
RigidBlock::RigidBlock(float a, float b, float c){
	mA = a;
	mB = b;
	mC = c;
}
