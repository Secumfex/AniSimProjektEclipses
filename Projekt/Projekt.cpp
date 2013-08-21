#include "Projekt.h"

Projekt::Projekt(){
	
}

Projekt::~Projekt(){

}

void Projekt::init(){
	mWorldManager.init();
}

void Projekt::draw(){
	BasisApplication::draw();
	mWorldManager.draw();
}

void Projekt::update(float d_t){
	BasisApplication::update(d_t);
	mWorldManager.update(d_t);
}


