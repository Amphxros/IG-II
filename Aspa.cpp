#include "Aspa.h"

Aspa::Aspa(Ogre::SceneNode* mNode, double largo, double ancho, double prof, bool orn):
	Obj(mNode), largo_(largo), ancho_(ancho), prof_(prof)
{
	// tablero
	tabNode = mNode_->createChildSceneNode();
	tabNode->setScale(largo_ / 2, ancho/2, prof/2);
	tabNode->setPosition(largo_ / 2, 0, 0);
	Ogre::Entity* obj = mSM->createEntity("cube.mesh");
	//Ogre::MovableObject* obj = mSM->createMovableObject("cube.mesh");
	tabNode->attachObject(obj);

	// adorno
	adornoNode = mNode_->createChildSceneNode();
	adornoNode->setPosition(0, 250*largo -40, 0);
	adornoNode->roll(Ogre::Degree(90));
	adornoNode->setScale(4, 8, 4);

	if (orn)
	{
		Ogre::MovableObject* adorno = mSM->createMovableObject("cube.mesh");
		adornoNode->attachObject(adorno);
	}
}