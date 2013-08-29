#include "WorldManager.h"

#include <iostream>
using namespace std;


void WorldManager::update(float d_t){
	mCollisionManager.testRigidBallsWorld();
	mCollisionManager.testRigidBallsAgainstRigidBalls();
	mCollisionManager.applyCollisionForces(d_t);
	
	applyGlobalForces(d_t);

	//Wohin damit?
	for (unsigned int i = 0; i < mForceObjects.size();i++){
		mForceObjects[i]->apply_fun(d_t);
	}
	for (unsigned int i = 0; i < mParticleSystemObjects.size();i++){
		mParticleSystemObjects[i]->applyForces(d_t);
	}

	mObjectFactory.updateAllObjects(d_t);
}

void WorldManager::init(){
	
	//Benutzereingaben:
		cout<<"Anzahl gewˆhnlicher Rigid Balls: ";
		cin >> normal_Rigid_Balls;
		cout<<"Anzahl federnde B‰lle um groﬂen Ball: ";
		cin >> spring_Rigid_Balls;
		cout<<"L‰nge der Federnden Ball-Kette: ";
		cin >> spring_chain_length;
		cout<<"Erdanziehungskraft (1/0): ";
		cin >> gravity_flag;

	//Referenzen setzen
	mObjectFactory.setVectorReferences(&mRigidBallObjects,&mBallObjects,&mPhysicsObjects);
	mObjectFactory.setParticleSystemVectorReference(&mParticleSystemObjects);
	mCollisionManager.setRigidBallsVectorReference(&mRigidBallObjects);

///////////////////////////////////////////////////////////////////////////////////////////////
	//StartObjekte erstellen
				//groﬂer Ball
	mObjectFactory.addRigidBall(0.5,0.7,Vector3(0.0,2.0,0.0),Vector3(0.0,0.0,0.0));
	mRigidBallObjects[0]->setColor(1.0,0,0.0);

				//feder 1
	mObjectFactory.addRigidBall(0.3,0.5,Vector3(1.0,1.0,1.0),Vector3(-0.1,-0.1,0.1));
	mRigidBallObjects[1]->setColor(0.0,1.0,1.0);
				//feder 2

	mObjectFactory.addRigidBall(0.3,0.5,Vector3(2.0,4.0,0.0)),Vector3(-0.1,-0.1,-0.1);
	mRigidBallObjects[2]->setColor(0.0,1.0,1.0);
				//Partikel
	vector<Physics* > temp_particles = mObjectFactory.createParticles(normal_Rigid_Balls,0.25,0.3,2.5);



//////////////////////////////////////////////////////////////////////////////////////////////

	//Testweise
	if(gravity_flag){
		SimpleForce* gravity = new SimpleForce(Vector3(0.0,-1.5,0.0));
		mGlobalForceObjects.push_back(gravity);
	}
	
	ViscousDrag* drag = new ViscousDrag();
	DampedSpring* spring =new  DampedSpring(mRigidBallObjects[1]->getPhysics(),mRigidBallObjects[2]->getPhysics(),10.0,0.1,2.0);
	
	mForceObjects.push_back(spring);
	mGlobalForceObjects.push_back(drag);
	//mGlobalForceObjects.push_back(gravity);


	//Kugeln um groﬂe Kugel herum
	temp_particles = mObjectFactory.createParticles(spring_Rigid_Balls,0.2,0.25,2.5, Vector3(0.4,0.1,0.7));
	for (unsigned int i = 0; i < temp_particles.size(); i ++){
		spring->addPhysicsPair(mRigidBallObjects[0]->getPhysics(),temp_particles[i]);
	}

	//Federkette von Kugeln
	temp_particles = mObjectFactory.createParticles(spring_chain_length,0.15,0.2,2.5, Vector3(0.1,1.0,0.3));
	DampedSpring* spring2 = new DampedSpring();
	spring2->setDampConstant(0.2);
	spring2->setRestLength(0.7);
	spring2->setSpringConstant(5.0);
	Physics* start = temp_particles[0];
	DampedSpringChain* springChain = new DampedSpringChain(start,spring2);
	//temp_particles.erase(temp_particles.begin());
	springChain->addParticles(temp_particles);
	mParticleSystemObjects.push_back(springChain);


	/////////////////////////////////////////////////////////////////////////////////////////
	//Alle B‰lle bei GlobalForces Anmelden
	for (unsigned int i = 0; i < mRigidBallObjects.size(); i ++){
		for (unsigned int j = 0; j < mGlobalForceObjects.size();j++){
			mGlobalForceObjects[j]->addInfluencedPhysics(mRigidBallObjects[i]->getPhysics());
		}
	}
}

void WorldManager::drawWorldConstraints(){
	glPointSize(5.0);
	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR,currentColor);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
		glVertex3f(World_max_X,World_max_Y,World_max_Z);
		glVertex3f(World_max_X,World_min_Y,World_max_Z);
		glVertex3f(World_max_X,World_max_Y,World_min_Z);
		glVertex3f(World_max_X,World_min_Y,World_min_Z);
		glVertex3f(World_min_X,World_min_Y,World_max_Z);
		glVertex3f(World_min_X,World_min_Y,World_min_Z);
		glVertex3f(World_min_X,World_max_Y,World_min_Z);
		glVertex3f(World_min_X,World_max_Y,World_max_Z);
	glEnd();
	glColor4f(currentColor[0],currentColor[1],currentColor[2],currentColor[3]);
}

void WorldManager::draw(){
	drawWorldConstraints();
	mObjectFactory.drawAllObjects();
}

void WorldManager::applyGlobalForces(float d_t){
	for (unsigned int i = 0; i < mGlobalForceObjects.size(); i++){
		mGlobalForceObjects[i]->apply_fun(d_t);
	}
}
