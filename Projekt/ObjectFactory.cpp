#include "ObjectFactory.h"
#include <iostream>
using namespace std;

ObjectFactory::ObjectFactory(){
	srand(time(NULL));
}


ObjectFactory::~ObjectFactory(void)
{
}

//Vectoren in die neue Objekte gef�llt werden
void ObjectFactory::setVectorReferences(vector<RigidBall* >* rigidBallObjects, vector<Ball* >* ballObjects , vector<Physics* >* physicsObjects){
	mRigidBallObjects = rigidBallObjects;
	mBallObjects = ballObjects;
	mPhysicsObjects = physicsObjects;
}

void ObjectFactory::setRigidBallsVectorReference(vector<RigidBall* >* rigidBallObjects){
		mRigidBallObjects = rigidBallObjects;
}
void ObjectFactory::setRigidBodyVectorReference(vector<RigidBody* >* rigidBodyObjects){
		mRigidBodyObjects = rigidBodyObjects;
}

void ObjectFactory::setBallsVectorReference(vector<Ball* >* ballObjects){
		mBallObjects = ballObjects;
	}

void ObjectFactory::setPhysicsVectorReference(vector<Physics* >* physicsObjects){
		mPhysicsObjects = physicsObjects;
}

void ObjectFactory::setParticleSystemVectorReference(vector<ParticleSystem* >* particleSystemObjects){
		mParticleSystemObjects = particleSystemObjects;
}

vector<Physics* > ObjectFactory::createParticles(int quantity, float radius, float mass, float max_velocity, Vector3 color){
	float rX,rY,rZ;
	vector<Physics* > particles;

	for (int i = 0; i < quantity; i++){
		rX = rand()/(float)RAND_MAX-0.5;
		rY = rand()/(float)RAND_MAX-0.5;
		rZ = rand()/(float)RAND_MAX-0.5;	
		Vector3 position(rX*5.0,rY*5.0,rZ*5.0);
		rX = rand()/(float)RAND_MAX-0.5;
		rY = rand()/(float)RAND_MAX-0.5;
		rZ = rand()/(float)RAND_MAX-0.5;	
		Vector3 velocity(rX*max_velocity,rY*max_velocity,rZ*max_velocity);

		addRigidBall(radius,mass,position,velocity,color);
		float last = mRigidBallObjects->size()-1;
		particles.push_back(mRigidBallObjects->at(last)->getPhysics());	
	}
	return particles;
}

void ObjectFactory::addRigidBall(float radius, float mass, Vector3 position, Vector3 velocity, Vector3 color){
	mRigidBallObjects->push_back(new RigidBall(radius,mass,position,velocity,color));
}

void ObjectFactory::addRigidBlock(float a, float b, float c,
									Vector3 position, Vector3 velocity,
									Matrix3 rotation, Vector3 angularMomentum){
	mRigidBodyObjects->push_back(new RigidBlock(a,b,c,position,velocity,rotation,angularMomentum));
}

//void ObjectFactory::removeRigidBallObject(int i){
//	mRigidBallObjects->erase(mRigidBallObjects->begin()+i);
//}

void ObjectFactory::updateAllObjects(float d_t){
	
	/*for (unsigned int i = 0; i < mParticleSystemObjects->size(); i++){
		mParticleSystemObjects->at(i)->update(d_t);
	}*/
	for (unsigned int i = 0; i < mRigidBallObjects->size();i++){
		mRigidBallObjects->at(i)->getPhysics()->update(d_t);
	}
	for (unsigned int i = 0; i < mPhysicsObjects->size();i++){
		mPhysicsObjects->at(i)->update(d_t);
	}
	for (unsigned int i = 0; i < mRigidBodyObjects->size(); i++){
		mRigidBodyObjects->at(i)->update(d_t);
	}
}

void ObjectFactory::drawAllObjects(){
	for (unsigned int i = 0; i < mRigidBallObjects->size();i++){
		mRigidBallObjects->at(i)->draw();
	}
	for (unsigned int i = 0; i < mBallObjects->size();i++){
		mBallObjects->at(i)->draw();
	}
	for (unsigned int i = 0; i < mRigidBodyObjects->size(); i++){
		mRigidBodyObjects->at(i)->draw();
	}
}
