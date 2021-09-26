#pragma once
#include "Obj.h"
#include "Aspa.h"

class AspasMolino : public Obj
{
public:
	AspasMolino(Ogre::SceneNode* mNode, int numAspas);
	virtual ~AspasMolino();
public:
	std::vector<Aspa*> mAspas_;

};