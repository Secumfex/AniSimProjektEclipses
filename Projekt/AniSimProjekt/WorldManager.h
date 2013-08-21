#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include "ObjectFactory.h"
#include "CollisionManager.h"
#include "ParticleSystem.h"
#include "Constraints.h"

class WorldManager{
private:
	vector<RigidBall* > mRigidBallObjects;
	vector<Ball* > mBallObjects;
	vector<Physics* > mPhysicsObjects;
			
	vector<Force* > mForceObjects;
	vector<Force* > mGlobalForceObjects;
	vector<ParticleSystem* > mParticleSystemObjects;
		
	ObjectFactory mObjectFactory;
	CollisionManager mCollisionManager;

	void applyGlobalForces(float d_t);

public:

	void init();
	void draw();
	void update(float d_t);


	void initObjects();
	void drawWorldConstraints();


};

#endif