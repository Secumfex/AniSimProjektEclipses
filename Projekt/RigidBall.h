#ifndef RIGIDBALL_H
#define RIGIDBALL_H

#include "Ball.h"
#include "Physics.h"

/**
Wie Ball, aber um ein Physics-Attribut erweitert. Erm�glicht das behandeln als Starrk�rper
*/
class RigidBall : public Ball{

private:
	Physics* mPhysics;
public:

	RigidBall(float radius = 0.5, float mass = 1.0, Vector3 position = Vector3(0,0,0), Vector3 velocity = Vector3(0,0,0), Vector3 color = Vector3(1.0, 0.75, 0.0));
	~RigidBall();

	Physics* getPhysics();
	void setPhysics(Physics* physics);
	void update(float d_t);


	bool checkCollision(RigidBall* with);
};

#endif
