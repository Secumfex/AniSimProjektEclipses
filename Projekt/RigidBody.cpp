#include "RigidBody.h"

#include <iostream>
using namespace std;

//Hilfsfunktion für Multiplikation von Vektor mit Matrix (für R_dot)
Matrix3 Star(Vector3 a){
	return Matrix3( 0 , -a.getZ(), a.getY(),
					a.getZ(),	0, -a.getX(),
					-a.getY(), a.getX(), 0);
}

void RigidBody::printState(){

	//Status
cerr << "Position: ";
mX.debugPrintToCerr();
cerr<< "Rotation-Quaternion: ";
mQ.debugPrintToCerr();
cerr<<"Linear Momentum: ";
mP.debugPrintToCerr();
cerr<< "Angular Momentum: ";
mL.debugPrintToCerr();


	//Misc
cerr << "Rotation-Matrix: ";
mR.debugPrintToCerr();
cerr << "Omega: ";
mOmega.debugPrintToCerr();
cerr<<"I_inv: ";
mIinv.debugPrintToCerr();
cerr<<"Velocity: ";
mV.debugPrintToCerr();
}

/***************Rigid Body ********************/
RigidBody::RigidBody(float mass, Matrix3 Ibody,
		Vector3 position, Vector3 velocity,
		Quaternion rotation, Vector3 angularMomentum){

	setPosition(position);
	setRotation(rotation);

	setMass(mass);
	setIbody(Ibody);
	setVelocity(velocity);

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
void RigidBody::setRotation(Quaternion rotation){
	mQ = rotation;

	Quaternion normQ = mQ;
	normQ.norm();
	mR = normQ.computeRotationMatrix();
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
/*******Eulerintegration***************/
	/////Update des Status
	//UpdatePosition
	Vector3 Xdot = mV*d_t;
	setPosition(mX+Xdot);

	//UpdateRotation
	Quaternion OmegaQuat(0,mOmega);
	Quaternion Qdot = (OmegaQuat*mQ)*0.5;
	Qdot.debugPrintToCerr();
	mQ += Qdot;
    mQ.norm();
	//mQ.debugPrintToCerr();


/*******Momente aktualisieren********/
	//Anwenden wirkender Kräfte auf Linear und Angular Momentum
	Vector3 Pdot = mForce;
	mP += Pdot;
	mForce = Vector3(0,0,0);

	Vector3 Ldot = mTorque;
	mL += Ldot;
	mTorque = Vector3(0,0,0);

/*****Hilfsvariablen aktualisieren****/
	//UpdateVelocity
	if (mMass != 0){
	mV = mP * ((1.0)/ mMass);}

	//Update RotationMatrix
	Quaternion normQ(mQ);
	normQ.norm();
	mR = normQ.computeRotationMatrix();

	//Update I_inv
	Matrix3 R_trans = mR;
	R_trans.transpose();
	mIinv = mR * mIbodyinv * R_trans;
	//Update Omega
	mOmega = mIinv * mL;

	//printState();
}

void RigidBody::draw(){

}

//void RigidBody::applyForceAndTorque(){
//	setImpulse(mP + mForce);
//}



/***************Rigid Block ********************/
RigidBlock::RigidBlock(float a, float b, float c,
		Vector3 position, Vector3 velocity,
		Quaternion rotation, Vector3 angularMomentum){

	//Status setzen
	setPosition(position);
	setRotation(rotation);

	//Trägheitstensor berechnen
	mA = a;
	mB = b;
	mC = c;

	setMass( a*b*c );
	Matrix3 I_body( b*b+c*c	,0		,0,
					0		,a*a+c*c,0,
					0		,0		,a*a+b*b);
	setIbody(I_body);

	setVelocity(velocity);
	setAngularMomentum(angularMomentum);

	printState();
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
	//cout<<"Rotation: "<<r.getW() <<" , "<< r.getX() <<" , "<<  r.getY()<<" , "<<  r.getZ()<<endl;
	glRotatef(mQ.getAngle(),mQ.getX(),mQ.getY(),mQ.getZ());
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
