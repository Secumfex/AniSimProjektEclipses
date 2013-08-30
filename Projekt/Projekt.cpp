#include "Projekt.h"

Projekt::Projekt(){
	
}

Projekt::~Projekt(){

}

void Projekt::init(){
//	cout<<"initiating Program..."<<endl;
	mWorldManager.init();
//	cout<<"initiation ended."<<endl;
}

void Projekt::draw(){
//	cout<<"Beginning draw-routine..."<<endl;
	BasisApplication::draw();
	mWorldManager.draw();
//	cout<<"Draw-Routine ended."<<endl;
}

void Projekt::update(float d_t){
//	cout<<"Beginning update-routine..."<<endl;
	BasisApplication::update(d_t);
//	cout<<"--Beginning WorldManger-Update..."<<endl;
	mWorldManager.update(d_t);
//	cout<<"--WorldManager-Update ended."<<endl;
//	cout<<"Update-Routine ended."<<endl;
}


