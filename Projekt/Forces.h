#ifndef FORCES_H
#define FORCES_H

#include <vector>
#include "Vector3.h"
#include "UtilityClasses.h"

using namespace std;

//Forwarding Declaration von Physics, weil kein gegenseitiger include möglich ist (OOP Logik)
class Physics;

class Force {
private:
protected:
	vector<Physics* > mInfluencedPhysics;
public:
	void addInfluencedPhysics(Physics* physics);
	void addInfluencedPhysics(vector <Physics* > physics);
	vector<Physics* > getInfluencedPhysics(); 
	virtual void apply_fun(float d_t);
};

//Wirkt auf jede beeinflusste Physik unabhängig von einander
class UnaryForce: public Force{
public:
	virtual void apply_fun(float d_t);
};

//Wirkt nur auf diese beiden Physics
class BinaryForce : public Force{
private:
protected:
	vector<IntTupel> mPairs;
public:
	void addPhysicsPair(Physics* lhs, Physics* rhs);
	virtual void apply_fun(float d_t);
};

/*Einfache Kraft, bestehend bloß aus einer Richtung*/
class SimpleForce : public UnaryForce{
protected:
	Vector3 mForce;
private:
public:	
	SimpleForce(Vector3 force = Vector3(0,0,0));
	void setForce(Vector3 force);				//Vektor dessen Länge der Kraft entspricht
	void setForce(float x, float y, float z);   //Vektor dessen Länge der Kraft entspricht, Skalar
	void setForce(Vector3 dir, float length);	//Richtung und "Newton"-mäßigen wert
	virtual void apply_fun(float d_t);
};


/*Wechselwirkende Kraft bei unelastischer Kollision zweier Physics*/
class ElasticCollision : public BinaryForce{
private:
	Physics* mLhs;
	Physics* mRhs;
	Vector3 mLhsNormal;
	Vector3 mRhsNormal;
public:
	ElasticCollision(Physics* lhs, Physics* rhs);
	virtual void apply_fun(float d_t);
};

/*Reflektieren an einer Normalen*/
class ReflectiveCollision : public SimpleForce{
private:
	Vector3 mNormal;
	Physics* mTarget;
public:
	ReflectiveCollision(Physics* target, Vector3& normal);
	virtual void apply_fun(float d_t);
};

/*Strömungswiderstand (Luft-)*/
class ViscousDrag : public UnaryForce{
private:
	float mDrag;
public:
	ViscousDrag(float drag = 0.01);
	virtual void apply_fun(float d_t);
	float getDrag();
	void setDrag(float drag);
};

/*Federkraft zwischen zwei Physics*/
class DampedSpring : public BinaryForce{
private:
	float mSpringConstant;
	float mDampConstant;
	float mRestLength;
public:
	DampedSpring(Physics* lhs = NULL, Physics* rhs = NULL, float springConstant = 5.0, float dampConstant = 0.1, float restLength = 1.0);
	void setSpringConstant(float springConstant);
	void setDampConstant(float dampConstant);
	void setRestLength(float restLength);
	virtual void apply_fun(float d_t);
};

#endif