#ifndef PHYSICS_H
#define PHYSICS_H

#include "Vector3.h"
#include <vector>

using namespace std;

//Forwarding Declaration von Forces (nötig weil kein gegenseitiger Include möglich)
class Forces;

class Physics{

	private:
	Vector3 mPosition;
	Vector3 mImpulse;
	Vector3 mVelocity;
	Vector3 mForceAccumulator;

	float mMass;  //masse == 0 --> statisches Objekt
	float i_Mass; //inverted Mass

	//Hilffunktionen bei Änderung von Impuls oder Geschwindigkeit
	void updateImpulse();
	void updateVelocity();

	public:
	//Konstruktor
	Physics();
	Physics(float mass, Vector3 velocity, Vector3 position);
	~Physics();

	//Position aktualisieren
	void update(float d_t);

	//Annahme: Abprallen an Fläche mit Oberflächennormalen normal
	void reflect(Vector3& normal);

	void applyForce(Vector3 force);
	void applyAccumulatedForce();

	//Setter
	void setImpulse(Vector3 impulse);
	void setVelocity(Vector3 velocity);
	void setMass(float mass);
	void setPosition(Vector3 position);
	void setPosition(float x, float y, float z);
	//Getter
	Vector3 getPosition() const;
	Vector3* getPositionPointer();
	Vector3 getVelocity() const;
	Vector3 getImpulse() const;
	float getMass() const;
};

void drawDirection(const Physics& input);
void drawInfluenceDirection(const Physics& target, const Physics& infl);
float getDistance(const Physics& lhs, const Physics& rhs);
void collide(Physics* lhs, const Vector3& lhsNormal, Physics* rhs, const Vector3& rhsNormal);

#endif
