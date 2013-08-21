#pragma once

#include "BasisApplication.h"
#include "Ball.h"
#include "RigidBall.h"
#include "Physics.h"
#include <time.h>
#include <vector>
#include "ParticleSystem.h"

using namespace std;

class ObjectFactory
{
private: 

	//Pointer auf Vectoren, in die die neuen Objekte gefüllt werden
	vector<Ball* >* mBallObjects;
	vector<Physics* >* mPhysicsObjects;
	vector<RigidBall* >* mRigidBallObjects;
	vector<ParticleSystem* >* mParticleSystemObjects;

public:
	ObjectFactory();
	~ObjectFactory(void);

	/*Setter*/
	void setVectorReferences(vector<RigidBall* >* rigidBallObjects,vector<Ball* >* ballObjects , vector<Physics* >* physicsObjects);
	void setRigidBallsVectorReference(vector<RigidBall* >* rigidBallObjects);
	void setBallsVectorReference(vector<Ball* >* ballObjects);
	void setPhysicsVectorReference(vector<Physics* >* physicsObjects);
	void setParticleSystemVectorReference(vector<ParticleSystem* >* particleSystemObjects);

	/*Hinzufügen von Rigid Balls*/
	void addRigidBall(float radius = 0.5, float mass = 1.0, Vector3 position = Vector3(0,0,0), Vector3 velocity = Vector3(0,0,0), Vector3 color = Vector3(1.0, 0.75, 0.0));
	/*Löschen von RigidBallObjekt mit Index i*/
	void removeRigidBallObject(int i);
	
	//Erstellen von zufällig plazierter und bewegter Partikel in der Welt
	vector<Physics* > createParticles(int quantity, float radius = 0.1, float mass = 0.1, float max_velocity = 1.0, Vector3 color = Vector3(1.0, 0.75, 0.0));

	//updated alle Objekte
	void updateAllObjects(float d_t);

	/**Zeichnen aller Objekte*/
	void drawAllObjects();
};

//Position des Balles wird an Physicsposition gebunden
	static void bind(Ball* ball, Physics* physics){
	ball->setPositionPointer(physics->getPositionPointer());
}