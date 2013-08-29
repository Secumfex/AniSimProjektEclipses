#include "Forces.h"

#include "Physics.h"
#include <iostream>
using namespace std;

/*Force Funktionalit�t*/
void Force::addInfluencedPhysics(Physics* physics){
	mInfluencedPhysics.push_back(physics);
}

void Force::addInfluencedPhysics(vector<Physics* > physics){
	for (unsigned int i = 0; i < physics.size(); i ++){
		addInfluencedPhysics(physics[i]);
	}
}

vector<Physics* > Force::getInfluencedPhysics(){
	return mInfluencedPhysics;
}
void Force::apply_fun(float d_t){
}

/*Unary Force Funktionalit�t*/
void UnaryForce::apply_fun(float d_t){
}

/*Binary Force Funktionalit�t*/
void BinaryForce::addPhysicsPair(Physics* lhs, Physics* rhs){
	mInfluencedPhysics.push_back(lhs);
	int lhs_i = mInfluencedPhysics.size()-1;
	mInfluencedPhysics.push_back(rhs);
	int rhs_i = mInfluencedPhysics.size()-1;
	mPairs.push_back(IntTupel(lhs_i,rhs_i));
}
void BinaryForce::apply_fun(float d_t){ }

/*SimpleForce Funktionalit�t*/
SimpleForce::SimpleForce(Vector3 force){
	mForce = force;
}
void SimpleForce::setForce(Vector3 force){
	mForce = force;
}
void SimpleForce::setForce(float x, float y, float z){
	mForce = Vector3(x,y,z);
}
void SimpleForce::setForce(Vector3 dir, float length){
	dir.normalize();
	mForce = dir*length;
}
void SimpleForce::apply_fun(float d_t){
	for (unsigned int i = 0; i < mInfluencedPhysics.size(); i++){
		mInfluencedPhysics[i]->applyForce(mForce*d_t);
	}
}

/*ElasticCollision Funktionalit�t*/
ElasticCollision::ElasticCollision(Physics* lhs, Physics*rhs){
	addPhysicsPair(lhs,rhs);
	mRhs = rhs;
	mLhs = lhs;
	mLhsNormal = (rhs->getPosition()-lhs->getPosition());
	mLhsNormal.normalize();
	mRhsNormal = (-1.0)*mLhsNormal;
}
void ElasticCollision::apply_fun(float d_t){
	//Bewegen sich von einander weg --> kein Absto�en n�tig
	if ((mLhs->getVelocity() - mRhs->getVelocity()) * mLhsNormal <= 0){
		return;
	} 
	else{
	 Vector3 forceAgainstRhs = (mLhs->getImpulse() * (mRhsNormal)) * mRhsNormal;
	 Vector3 forceAgainstLhs = (mRhs->getImpulse() * (mLhsNormal)) * mLhsNormal;
	 Vector3 totalForceAgainstRhs = forceAgainstRhs - forceAgainstLhs;
	 Vector3 totalForceAgainstLhs = forceAgainstLhs - forceAgainstRhs;
	 mLhs->applyForce(totalForceAgainstLhs);
	 mRhs->applyForce(totalForceAgainstRhs);
	}
}

/*ReflectiveCollision Funktionalit�t*/
ReflectiveCollision::ReflectiveCollision(Physics* target, Vector3& normal){
	mNormal = normal;
	addInfluencedPhysics(target);
	mTarget = target;
}
void ReflectiveCollision::apply_fun(float d_t){
	Vector3 v = mTarget->getVelocity();
	Vector3 newDirection = -2*((v*mNormal)*mNormal) + v;
	mTarget->setVelocity(newDirection);
}

/*ViscousDrag Funktionalit�t*/
ViscousDrag::ViscousDrag(float drag){
	setDrag(drag);
}
void ViscousDrag::setDrag(float drag){
	mDrag = drag;
}
float ViscousDrag::getDrag(){
	return mDrag;
}
void ViscousDrag::apply_fun(float d_t){
	for (unsigned int i = 0; i < mInfluencedPhysics.size();i++){
		Vector3 velocity = mInfluencedPhysics[i]->getVelocity();
		mInfluencedPhysics[i]->applyForce((-1.0)*mDrag*velocity*d_t);
	}
}

/*DampedSpring Funktionalit�t*/
DampedSpring::DampedSpring(Physics* lhs, Physics* rhs,float springConstant, float dampConstant, float restLength){
	if (lhs != NULL && rhs != NULL){
		addPhysicsPair(lhs,rhs);
	}
	setDampConstant(dampConstant);
	setSpringConstant(springConstant);
	setRestLength(restLength);
}
void DampedSpring::setDampConstant(float dampConstant){
	mDampConstant = dampConstant;
}
void DampedSpring::setSpringConstant(float springConstant){
	mSpringConstant = springConstant;
}
void DampedSpring::setRestLength(float restLength){
	mRestLength = restLength;
}
void DampedSpring::apply_fun(float d_t){
	for (unsigned int i = 0; i < mPairs.size(); i++){
		Physics* lhs = mInfluencedPhysics[mPairs[i].i];
		Physics* rhs = mInfluencedPhysics[mPairs[i].j];

		Vector3 pos_lhs = lhs->getPosition();
		Vector3 pos_rhs = rhs->getPosition();
		Vector3 pos_dif = (pos_rhs-pos_lhs);
		Vector3 vel_dif = rhs->getVelocity()-lhs->getVelocity();
		float pos_dif_length = pos_dif.length();

		//Tension --> "Gespanntheit" Ber�cksichtigt L�nge der Feder in Ruheposition
		float tension = pos_dif_length-mRestLength;
		
		Vector3 f_b = pos_dif;
		f_b.normalize();
		f_b *= (mSpringConstant * tension + mDampConstant * ((vel_dif * pos_dif) / pos_dif_length))*d_t;
		Vector3 f_a = (-1.0) * f_b;
		
		lhs->applyForce(f_b);
		rhs->applyForce(f_a);
	}
}
