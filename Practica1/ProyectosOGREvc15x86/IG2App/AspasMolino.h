#pragma once
#include "Obj.h"
#include "Aspa.h"


class AspasMolino : public Obj
{
public:
	AspasMolino(Ogre::SceneNode* mNode, int numAspas, int largo, bool orn);
	virtual ~AspasMolino();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
public:
	Ogre::SceneNode* mContainer;
	Ogre::SceneNode* mCenter;
	
	std::vector<Aspa*> mAspas_vec;
	int numAspas_;
};