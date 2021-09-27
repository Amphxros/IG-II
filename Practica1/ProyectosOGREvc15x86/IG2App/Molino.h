#pragma once
#include "Obj.h"
#include "AspasMolino.h"
class Molino :
	public Obj
{
public:
	Molino(Ogre::SceneNode* mNode, int numAspas, int altura, int largoAspas);
	virtual ~Molino();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
protected:
	AspasMolino* mAspas_;
	Ogre::SceneNode* mMolinoNode;
	Ogre::SceneNode* mAspasNode;
	
};

