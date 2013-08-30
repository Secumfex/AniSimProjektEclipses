#include "RigidBody.h"

#include "Quaternion.h"
#include <iostream>
using namespace std;

//Hilfsfunktion für Multiplikation von Vektor mit Matrix (für R_dot)
Matrix3 Star(Vector3 a){
	return Matrix3( 0 , -a.getZ(), a.getY(),
					a.getZ(),	0, -a.getX(),
					-a.getY(), a.getX(), 0);
}

/***************Rigid Body ********************/
RigidBody::RigidBody(float mass, Matrix3 Ibody,
		Vector3 position, Vector3 velocity,
		Matrix3 rotation, Vector3 angularMomentum){

	setPosition(position);
	setRotation(rotation);
	setVelocity(velocity);

	setMass(mass);
	setIbody(Ibody);

	setAngularMomentum(angularMomentum);
}

RigidBody::~RigidBody(){

}

/*************Setter***********/
void RigidBody::setIbody(Matrix3 Ibody){
	mIbody = Ibody;
	Ibody.invert();
	mIbodyinv = Ibody;
	Matrix3 R_trans = mR;
	R_trans.transpose();
	mIinv =  mR * mIbodyinv * R_trans;

}
void RigidBody::setPosition(Vector3 position){
	mX = position;
}
void RigidBody::setPosition(float x, float y, float z){
	mX = Vector3(x,y,z);
}
void RigidBody::setRotation(Matrix3 rotation){
	mR = rotation;
}

void RigidBody::setAngularMomentum(Vector3 angularMomentum){
	mL = angularMomentum;
	mOmega = mIinv * mL;
}

void RigidBody::setOmega(Vector3 omega){
	mOmega = omega;
}

void RigidBody::setImpulse(Vector3 impulse){
	mP = impulse;
	if(mMass != 0.0){
		mV = mP * ((1.0) / mMass);
	}
}
void RigidBody::setVelocity(Vector3 velocity){
	mV = velocity;
	mP = mV * mMass;
}
void RigidBody::setMass(float mass){
	mMass = mass;
}

/*********** Funktionalität ***********/

/**
 * Annahme: torque und force wurden für d_t bereits berechnet
 */
void RigidBody::update(float d_t){
	/////Update des Status
	//UpdatePosition
	Vector3 Xdot = mV*d_t;
	setPosition(mX+Xdot);

	//UpdateRotation
	Matrix3 Rdot = Star(mOmega) * mR * d_t;
	setRotation(mR+Rdot);

	//Anwenden wirkender Kräfte auf Linear und Angular Momentum
	Vector3 Pdot = mForce;
	mP += Pdot;
	mForce = Vector3(0,0,0);

	Vector3 Ldot = mTorque;
	mL += Ldot;
	mTorque = Vector3(0,0,0);

	////Update der Hilfsvariablen
	//UpdateVelocity
	if (mMass != 0){
	mV = mP * ((1.0)/ mMass);}
	//Update I_inv
	Matrix3 R_trans = mR;
	R_trans.transpose();
	mIinv = mR * mIbodyinv * R_trans;
	//Update Omega
	mOmega = mIinv * mL;

}
void RigidBody::draw(){

}

void RigidBody::applyForceAndTorque(){
	setImpulse(mP + mForce);
}



/***************Rigid Block ********************/
RigidBlock::RigidBlock(float a, float b, float c,
		Vector3 position, Vector3 velocity,
		Matrix3 rotation, Vector3 angularMomentum){

	setPosition(position);
	setRotation(rotation);
	setVelocity(velocity);

	mA = a;
	mB = b;
	mC = c;

	setMass( a*b*c );
	Matrix3 I_body( b*b+c*c	,0		,0,
					0		,a*a+c*c,0,
					0		,0		,a*a+b*b);
	setIbody(I_body);

	setAngularMomentum(angularMomentum);
}

void RigidBlock::draw(){

	float x = mA/2.0;
	float y = mB/2.0;
	float z = mC/2.0;

	glLineWidth(2.0);
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR,currentColor);
	glColor3f(1.0,0.0,0.0);

	glTranslatef(mX.getX(),mX.getY(),mX.getZ());
	Quaternion r(mR);
	//cout<<"Rotation: "<<r.getW() <<" , "<< r.getX() <<" , "<<  r.getY()<<" , "<<  r.getZ()<<endl;
	glRotatef(r.getW(),r.getX(),r.getY(),r.getZ());
	glPushMatrix();
		glBegin(GL_LINE_LOOP);
			glVertex3f(-x,-y,z); //0
			glVertex3f(x,-y,z); //1
			glVertex3f(x,y,z); //2
			glVertex3f(-x,y,z); //3
			glVertex3f(-x,-y,z); //4
			glVertex3f(-x,-y,-z); //5
			glVertex3f(x,-y,-z); //6
			glVertex3f(x,y,-z); //7
			glVertex3f(-x,y,-z); //8
			glVertex3f(-x,-y,-z); //9
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(-x,y,z); //10
			glVertex3f(-x,y,-z); //10
			glVertex3f(x,y,z); //11
			glVertex3f(x,y,-z); //11
			glVertex3f(x,-y,z); //12
			glVertex3f(x,-y,-z); //12
		glEnd();
	glPopMatrix();
	glColor4f(currentColor[0],currentColor[1],currentColor[2],currentColor[3]);
}
