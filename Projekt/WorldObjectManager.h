#ifndef WORLDOBJECTMANAGER_H
#define WORLDOBJECTMANAGER_H

#include "ObjectFactory.h"
#include "CollisionManager.h"
#include "Constraints.h"

class WorldObjectManager{
	void initObjects();
	void drawAll();
	void update(float d_t);


};

#endif
