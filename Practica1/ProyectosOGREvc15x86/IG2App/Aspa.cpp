#include "Aspa.h"

Aspa::Aspa(Ogre::SceneNode* mNode, double largo, double ancho, double prof, bool orn):
	Obj(mNode), largo_(largo), ancho_(ancho), prof_(prof)
{
	// tablero
	Ogre::SceneNode* tabNode = mNode_->createChildSceneNode();
	tabNode->setScale(largo_ / 2, ancho/2, prof/2);
	tabNode->setPosition(largo_ / 2, 0, 0);
	Ogre::Entity* e = mSM->createEntity("cube.mesh");
	tabNode->attachObject(e);

	// adorno
	Ogre::SceneNode* adornoNode = mNode_->createChildSceneNode();
	adornoNode->setPosition(0,0,0);
	adornoNode->setScale(largo_, ancho_, prof_);
	if (orn)
	{
		Ogre::Entity* en = mSM->createEntity("Barrel.mesh");
		adornoNode->attachObject(en);
	}
}