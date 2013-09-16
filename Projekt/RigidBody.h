#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Physics.h"
#include "Matrix3.h"
#include "Quaternion.h"

#include <GL/glut.h>

class RigidBody {
/*attribute:
 * position			x(t)
 * orientation 		R(t)			(informal)
 * linear momentum  P(t) = m * v <<-- Änderung: P'(t+t_d) =P(t)+ F(t_d)  genau wie Änderung des Impulses!
 * angular momentum L(t) = I (t) * w(t)    <<-- I: Inertia Tensor (Trägheitstensor) bestimmt die Masseverteilung im  Körper. Wird als LUT abgespeichert oder so
 *
 *	constant: I_body	: Inertia des Körpers
 *			  M			: Masse des Körpers
 *
 *	auxillary: v(t)	= P(t) / M
 *			   I(t) = R(t) * I_body * R(t)^T
 *			   w(t) = I(t)^(-1) * L(t)
 *
 *	Ableitung (Änderung pro Zeitintervall):
 *			       v(t)    		<-- �nderung der Position 		�ber Zeit = Geschwindigkeit
 *			       w(t) * R(t) 	<-- �nderung der Rotation 		�ber Zeit = Winkelgeschwindigkeit (oder so)
 *			       F(t)    		<-- �nderung des Impulses 		�ber Zeit = Krafteinwirkung
 *			       torque(t) 	<--	�nderung des Drehimpulses 	�ber Zeit = Drehkrafteinwirkung (Drehmoment)
 */

 /**
 * torque <-- Drehmoment: Änderung des angular momentum (quasi wie Lineare Kraft �nderung des linear momentum)
 *
 * I(t) = R(t) * I_body * R(t)^T
 * I_body ist konstant, da in Objektkoordinaten
 * so lässt er sich ganz lecker neu berechnen
 */

/**
 * Implementation nach Rigid Body Dynamics 1
 */
protected:
	/* Constant quantities - Berechnet vor Simulationsbeginn*/
	float mMass; 		/* mass M */
	Matrix3 mIbody; 		/* Ibody */
	Matrix3 mIbodyinv; 	/* I−1 body (inverse of Ibody) */

	/* State variables */
	Vector3 mX; 		/* x(t)/ << Position*/
	Quaternion mQ; 		/* R(t)/ << Rotation*/
	Vector3 mP; 		/* P(t)/ << Impuls*/
	Vector3 mL; 		/* L(t)	 << Angular Momentum / */

	/* Derived quantities (auxiliary variables) */
	Matrix3 mIinv; 	/* I−1(t)	 << Inverser Trägheitstensor/ */
	Matrix3 mR;
	Vector3 mV; 		/* v(t)/ << Velocity aus Impuls berechnet*/
	Vector3 mOmega;  /* w(t)/ 	 << Omega (w) Winkelgeschwindigkeit oder so*/

	/* Computed quantities */
	Vector3 mForce; 	/* F(t)/ << Anzuwendende Kraft (?)*/
	Vector3 mTorque; /* torque(t)/ <<Anzuwendender Drehmoment (?)*/

public:
	~RigidBody();
	RigidBody(float mass = 1.0, Matrix3 Ibody = Matrix3(1.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,1.0),
			  Vector3 position = Vector3(0,0,0), Vector3 velocity = Vector3(0,0,0),
			  Quaternion rotation = Quaternion(), Vector3 angularMomentum = Vector3(0,0,0));

	/*Getter und Setter*/
	void setMass(float mass);
	void setIbody(Matrix3 Ibody);
	void setPosition(Vector3 position);
	void setPosition(float x = 0.0, float y = 0.0, float z = 0.0);
	void setRotation(Quaternion rotation);
	void setAngularMomentum(Vector3 angularMomentum);
	void setOmega(Vector3 omega);

	void setImpulse(Vector3 impulse);
	void setVelocity(Vector3 velocity);

	/*Misc*/
	void applyForceAndTorque();
	void update(float d_t);
	virtual void draw();
	void printState();
};

//Ein Block mit Seitenlängen a, b, c
class RigidBlock : public RigidBody{
protected:
	float mA;
	float mB;
	float mC;
public:
	RigidBlock(float a = 1.0, float b = 1.0, float c = 1.0,
			Vector3 position = Vector3(0,0,0), Vector3 velocity = Vector3(0,0,0),
			Quaternion rotation = Quaternion(), Vector3 angularMomentum = Vector3(0,0,0));
	virtual void draw();
};

//Sonderfall von RigidBlock, Seitenlängen gleich
class RigidCube : public RigidBlock{
protected:
	float mSideLength;
public:
	RigidCube(float sideLength = 1.0);
	void setSideLength(float sideLength);
};

#endif
