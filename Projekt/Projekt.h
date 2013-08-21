#ifndef PROJEKT_H
#define PROJEKT_H

#include "Constraints.h"

#include "ObjectFactory.h"
#include "CollisionManager.h"
#include "WorldManager.h"

#include <iostream>
using namespace std;

class Projekt : public BasisApplication
{
	//---------------CONSTRUCTORS & DESTRUCTOR------------
	public:
		Projekt(void);
		~Projekt(void);

	//---------------MEMBER VARIABLES---------------------
	protected:	//Besserbei zeiten mal ein World-Manager basteln
		vector<RigidBall* > mRigidBallObjects;
		vector<Ball* > mBallObjects;
		vector<Physics* > mPhysicsObjects;
			
		vector<Force* > mForceObjects;
		//vector<ParticleSystem* > mParticleSystemObjects;

		WorldManager mWorldManager;
		ObjectFactory mObjectFactory;
		CollisionManager mCollisionManager;

	//---------------MEMBER FUNCTIONS---------------------
	private:
		void initObjects();
		void drawWorldConstraints();
	public:
		virtual void init(void);
		virtual void update(float d_t);
		virtual void draw(void);
};
#endif
