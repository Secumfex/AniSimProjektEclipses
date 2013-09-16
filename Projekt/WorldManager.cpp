#include "WorldManager.h"

#include "Quaternion.h"
#include <iostream>
using namespace std;


void WorldManager::update(float d_t){
//	cout<<"----beginning Collision Manager Testphase..."<<endl;
//	cout<<"------beginning RigidBallWorld Testphase..."<<endl;
	mCollisionManager.testRigidBallsWorld();
//	cout<<"------beginning RigidBallAgainstRigidBall Testphase..."<<endl;
	mCollisionManager.testRigidBallsAgainstRigidBalls();
//	cout<<"------beginning ApplyCollisionForces phase..."<<endl;
	mCollisionManager.applyCollisionForces(d_t);
//	cout<<"----Collision Manager Testphase ended."<<endl;
	
//	cout<<"----Applying global forces..."<<endl;
	applyGlobalForces(d_t);
//	cout<<"----Applying global forces ended."<<endl;

//	cout<<"----Applying forces..."<<endl;
	//Wohin damit?
	for (unsigned int i = 0; i < mForceObjects.size();i++){
		mForceObjects[i]->apply_fun(d_t);
	}
	for (unsigned int i = 0; i < mParticleSystemObjects.size();i++){
		mParticleSystemObjects[i]->applyForces(d_t);
	}
//	cout<<"----Applying forces ended."<<endl;

//	cout<<"----updating All Objects..."<<endl;
	mObjectFactory.updateAllObjects(d_t);
//	cout<<"----updating All Objects ended."<<endl;
}

inline void WorldManager:: initRigidBallSimulation(){
	//großer Ball
	mObjectFactory.addRigidBall(0.5,0.7,Vector3(0.0,2.0,0.0),Vector3(0.0,0.0,0.0),Vector3(1.0,0.0,0.0));

	//feder 1 Ball
	mObjectFactory.addRigidBall(0.3,0.5,Vector3(1.0,1.0,1.0),Vector3(-0.1,-0.1,0.1),Vector3(0.0,1.0,1.0));
	//feder 2 Ball
	mObjectFactory.addRigidBall(0.3,0.5,Vector3(2.0,4.0,0.0)),Vector3(-0.1,-0.1,-0.1),Vector3(0.0,1.0,1.0);
	//Federkraft die feder 1 und feder 2 Ball verbindet und von dem großen Ball verwendet wird
	DampedSpring* spring =new  DampedSpring(mRigidBallObjects[1]->getPhysics(),mRigidBallObjects[2]->getPhysics(),10.0,0.1,2.0);
	mForceObjects.push_back(spring);

	//lose Bälle
	vector<Physics* > temp_particles = mObjectFactory.createParticles(normal_Rigid_Balls,0.25,0.3,2.5);

	//federnde Kugeln um große Kugel herum
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
}

inline void WorldManager::initRigidBodySimulation(){
	Quaternion rotation(0.0,0.0,0.0,0.0);
	mObjectFactory.addRigidBlock(1,1,1,
			Vector3(0,2.0,0),Vector3(0,0,0),
			rotation,Vector3(10,10.0,0.0));
}

void WorldManager::init(){
	
	//Referenzen setzen
	mObjectFactory.setVectorReferences(&mRigidBallObjects,&mBallObjects,&mPhysicsObjects);
	mObjectFactory.setParticleSystemVectorReference(&mParticleSystemObjects);
	mObjectFactory.setRigidBodyVectorReference(&mRigidBodyObjects);
	mCollisionManager.setRigidBallsVectorReference(&mRigidBallObjects);

	//Benutzereingaben:

		//Wahl des Simulationsprogramms:
		cout<<"Wahl des Simulationsprogramms:"<<endl<<"1 : Ball-Simulation"<<endl<<"2 : Block-Simulation"<<endl;
		cin >> simulation_index;
	switch(simulation_index){
	case 1:
		cout<<"Anzahl gewöhnlicher Rigid Balls: ";
		cin >> normal_Rigid_Balls;
		cout<<"Anzahl federnde Bälle um großen Ball: ";
		cin >> spring_Rigid_Balls;
		cout<<"Länge der Federnden Ball-Kette: ";
		cin >> spring_chain_length;
		cout<<"Erdanziehungskraft-Stärke: ";
		cin >> gravity_strength;
		initRigidBallSimulation();
		break;
	case 2:
		initRigidBodySimulation();
		break;
	}


///////////////Globale Kräfte/////////////////////////////////////////////////////////////////////////

	if(gravity_strength > 0.0){
		SimpleForce* gravity = new SimpleForce(Vector3(0.0,-gravity_strength,0.0));
		mGlobalForceObjects.push_back(gravity);
	}
	
	ViscousDrag* drag = new ViscousDrag();
	mGlobalForceObjects.push_back(drag);

/////////////////////////////////////////////////////////////////////////////////////////
	//Alle Objekte bei GlobalForces Anmelden
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
