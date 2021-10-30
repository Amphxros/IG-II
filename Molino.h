#pragma once
#include "EntidadIG.h"
#include "AspasMolino.h"
class Molino :
	public EntidadIG
{
public:
	Molino(Ogre::SceneNode* mNode, int numAspas, int altura, int largoAspas);
	virtual ~Molino();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
protected:
	AspasMolino* mAspas_;
	Ogre::SceneNode* mMolinoNode;
	Ogre::SceneNode* container;
	Ogre::SceneNode* mAspasNode;
	float altura_;
	bool molinoTruco_;
};

