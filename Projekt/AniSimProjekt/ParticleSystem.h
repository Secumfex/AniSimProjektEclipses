#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "Physics.h"
#include "Forces.h"

class ParticleSystem{
protected:
	vector<Physics* > mParticles;
	vector<Force* > mForces;
public:
	virtual void addParticle(Physics* particle);
	virtual void addParticles(vector<Physics *> particles);
	
	void addForce(Force* force);

	virtual void applyForces(float d_t);
	virtual void update(float d_t);
};

class DampedSpringChain : public ParticleSystem{
protected:
	DampedSpring* mDampedSpring;
public:
	DampedSpringChain(Physics* start= NULL, DampedSpring* dampedSpring = NULL);
	virtual void addParticle(Physics* particle);
	void setDampedSpring(DampedSpring* force);
	virtual void addParticles(vector<Physics *> particles);

};

#endif