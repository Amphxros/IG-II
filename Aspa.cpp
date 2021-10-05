#include "Aspa.h"

Aspa::Aspa(Ogre::SceneNode* mNode, double largo, double ancho, double prof, bool orn):
	Obj(mNode), largo_(largo), ancho_(ancho), prof_(prof)
{
	// tablero
	tabNode = mNode_->createChildSceneNode();
	tabNode->setScale(largo_ / 2, ancho/2, prof/2);
	tabNode->setPosition(largo_ / 2, 0, 0);
	Ogre::Entity* e = mSM->createEntity("cube.mesh");
	tabNode->attachObject(e);

	// adorno
	adornoNode = mNode_->createChildSceneNode();
	adornoNode->setPosition(0, 250*largo -40, 0);
	adornoNode->roll(Ogre::Degree(90));
	adornoNode->setScale(4, 8, 4);

	if (orn)
	{
		Ogre::Entity* en = mSM->createEntity("Barrel.mesh");
		adornoNode->attachObject(en);
	}
}