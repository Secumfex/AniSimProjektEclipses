#include "Physics.h"

/*Konstruktor*/
Physics::Physics(){
	mMass = 1.0;
	i_Mass = 1.0;
	mPosition.setX(0.0);
	mPosition.setY(0.0);
	mPosition.setZ(0.0);
	mVelocity.setX(0.0);
	mVelocity.setY(0.0);
	mVelocity.setZ(0.0);
	updateImpulse();
}
	//Masse 0 -> solid
Physics::Physics(float mass, Vector3 velocity, Vector3 position){
	setMass(mass);
	setVelocity(velocity);
	setPosition(position);
}

Physics::~Physics(){
}

/*Hilfsfunktionen*/
void Physics::updateImpulse(){
	mImpulse = mMass * mVelocity;
}

void Physics::updateVelocity(){
	mVelocity = i_Mass*mImpulse;
}

/*Setter*/
void Physics::setVelocity(Vector3 velocity){
	if (mMass != 0){
		mVelocity = velocity;
		updateImpulse();
	}
}

void Physics::setImpulse(Vector3 impulse){
	if (mMass != 0){
		mImpulse = impulse;
		updateVelocity();
	}
}

void Physics::setMass(float mass){
	mMass = mass;
	if (mMass != 0.0){
		i_Mass = 1.0 / mMass;
	}
	else{
		i_Mass = 1.0;
	}
	updateImpulse();
}

void Physics::setPosition(Vector3 position){
	mPosition = position;
}

void Physics::setPosition(float x, float y, float z){
	mPosition.setX(x);
	mPosition.setY(y);
	mPosition.setZ(z);
}

/*Getter*/
float Physics::getMass() const{
	return mMass;
}

Vector3 Physics::getPosition() const{
	return mPosition;
}

Vector3* Physics::getPositionPointer(){
	Vector3* pointer = &mPosition;
	return pointer;
}

Vector3 Physics::getVelocity() const{
	return mVelocity;
}

Vector3 Physics::getImpulse() const{
	return mImpulse;
}

/*Kollisionsbezogene Funktionen*/
void Physics::reflect(Vector3& normal){
	Vector3 v = getVelocity();
	Vector3 newDirection = -2*((v*normal)*normal) + v;
	setVelocity(newDirection);
}

/*Update des Zustandes in Abh�ngigkeit von Zeitintervall*/
void Physics::update(float d_t){
	applyAccumulatedForce();
	setPosition( mPosition + (mVelocity * d_t));
}

/*Kraft wird angewandt*/
void Physics::applyAccumulatedForce(){
	Vector3 impulse = getImpulse();
	setImpulse(impulse+mForceAccumulator);
	mForceAccumulator = Vector3(0,0,0);
}
	//Masse = 0 --> nix passiert
void Physics::applyForce(Vector3 force){
	if (mMass != 0){
		mForceAccumulator+=force;
	}
}

//Linke und Rechte Oberfl�chennormale entlang die wirkende Kraft wirken soll
void collide(Physics* lhs, const Vector3& lhsNormal, Physics* rhs, const Vector3& rhsNormal){
	if ((lhs->getVelocity() - rhs->getVelocity()) * lhsNormal <= 0){
		return;
	} 
	else{
	 Vector3 forceAgainstRhs = (lhs->getImpulse() * (rhsNormal)) * rhsNormal;
	 Vector3 forceAgainstLhs = (rhs->getImpulse() * (lhsNormal)) * lhsNormal;
	 Vector3 totalForceAgainstRhs = forceAgainstRhs - forceAgainstLhs;
	 Vector3 totalForceAgainstLhs = forceAgainstLhs - forceAgainstRhs;
	 lhs->applyForce(totalForceAgainstLhs);
	 rhs->applyForce(totalForceAgainstRhs);
	}
}