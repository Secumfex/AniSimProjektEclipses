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
	protected:
		WorldManager mWorldManager;

	//---------------MEMBER FUNCTIONS---------------------
	private:
	public:
		virtual void init(void);
		virtual void update(float d_t);
		virtual void draw(void);
};
#endif
