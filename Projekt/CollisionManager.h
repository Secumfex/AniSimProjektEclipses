#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "RigidBall.h"
#include "Forces.h"
#include "Constraints.h"
#include "UtilityClasses.h"
#include "Vector3.h"

//Hilfsklasse um Index-Tupel zu speichern


class CollisionManager{
private:
	vector<RigidBall* >* mRigidBalls;  
	vector<Force* > mCollisionForces; //Enth�lt Vektorbasierte Behandlungen von Kollisionen
public:
	

	/*Setter*/
	 void setRigidBallsVectorReference(vector<RigidBall* >* rigidBallObjects){
		mRigidBalls = rigidBallObjects;
	}

	void testRigidBallsWorld(){
	for (unsigned int i = 0; i < mRigidBalls->size(); i++){
			Vector3 p =  mRigidBalls->at(i)->getPosition();
			float r = mRigidBalls->at(i)->getRadius();
			Vector3 n(0,0,0);
			if (p.getX()+r > World_max_X ){
					mRigidBalls->at(i)->setPosition(World_max_X-r,p.getY(),p.getZ());
					n.setX(-1.0);
					
					mCollisionForces.push_back(
						new ReflectiveCollision(mRigidBalls->at(i)->getPhysics(),n));
			}
			if (p.getY()+r > World_max_Y ){
					mRigidBalls->at(i)->setPosition(p.getX(),World_max_Y-r,p.getZ());
					n.setY(-1.0);
					mCollisionForces.push_back(
						new ReflectiveCollision(mRigidBalls->at(i)->getPhysics(),n));
			}
			if (p.getZ()+r > World_max_Z ){
					mRigidBalls->at(i)->setPosition(p.getX(),p.getY(),World_max_Z-r);
					n.setZ(-1.0);
					mCollisionForces.push_back(
						new ReflectiveCollision(mRigidBalls->at(i)->getPhysics(),n));
			}	
			if (p.getX()-r < World_min_X ){
					mRigidBalls->at(i)->setPosition(World_min_X+r,p.getY(),p.getZ());
					n.setX(1.0);
					mCollisionForces.push_back(
						new ReflectiveCollision(mRigidBalls->at(i)->getPhysics(),n));
			}
			if (p.getY()-r < World_min_Y ){
					mRigidBalls->at(i)->setPosition(p.getX(),World_min_Y+r,p.getZ());
					n.setY(1.0);
					mCollisionForces.push_back(
						new ReflectiveCollision(mRigidBalls->at(i)->getPhysics(),n));
			}
			if (p.getZ()-r < World_min_Z ){
					mRigidBalls->at(i)->setPosition(p.getX(),p.getY(),World_min_Z+r);
					n.setZ(1.0);
					mCollisionForces.push_back(
						new ReflectiveCollision(mRigidBalls->at(i)->getPhysics(),n));
			
			}	
		}
	}

	//Reflektiert die Physik an der gegebenen Normalen
	void reflect(Physics* lhs, Vector3 normal){
		lhs->reflect(normal);
	}

	//Alle RigidBall-Objekte auf Kollisionen untereinander testen
	void testRigidBallsAgainstRigidBalls(){
		if (mRigidBalls->size() == 0) {return;} //vvvvvvvv --> dieser Ausdruck ist wegen unsigned int = MAX_VALUE wenn size = 0
		for (unsigned int i = 0; i <mRigidBalls->size()-1; i++){
			for (unsigned int j = i+1; j < mRigidBalls->size();j++){
				if (mRigidBalls->at(i)->checkCollision(mRigidBalls->at(j))){
					mCollisionForces.push_back(
						new ElasticCollision(mRigidBalls->at(i)->getPhysics(),mRigidBalls->at(j)->getPhysics()));
				}
			}
		}
	}

	void applyCollisionForces(float d_t){
		for (unsigned int i = 0; i < mCollisionForces.size(); i ++){
			mCollisionForces[i]->apply_fun(d_t);
		} 
		mCollisionForces.clear();
	}
};

#endif
