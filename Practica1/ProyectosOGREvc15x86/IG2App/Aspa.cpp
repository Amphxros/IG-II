#include "Aspa.h"

Aspa::Aspa(Ogre::SceneNode* m, double largo, double ancho, double prof):
	 Obj(m), largo_(largo), ancho_(ancho), prof_(prof)
{
	// tablero
	tabNode = m->createChildSceneNode();
	Ogre::Entity* e = mSM->createEntity("cube.mesh");
	tabNode->setScale(largo, ancho, prof);
	tabNode->setPosition(largo / 2, ancho / 2, prof / 2);
	tabNode->attachObject(e);

	//adorno
	adornoNode = m->createChildSceneNode();
	Ogre::Entity* en = mSM->createEntity("Barrel.mesh");
	adornoNode->setPosition(largo, ancho, 0);
	//adornoNode->setScale()
	m->attachObject(en);


}