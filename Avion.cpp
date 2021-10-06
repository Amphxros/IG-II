#include "Avion.h"
#include <SDL.h>

Avion::Avion(Ogre::SceneNode* mNode, float rd, float largo, int nAspas):
	Obj(mNode),numAspas_(nAspas)
{
	//esfera
	cuerpoNode_ = mNode_->createChildSceneNode();
	cuerpoNode_->setScale(rd, rd, rd); // rd/40
	Ogre::Entity* body = mSM->createEntity("sphere.mesh");
	cuerpoNode_->attachObject(body);

	pilotoNode_ = mNode_->createChildSceneNode();
	pilotoNode_->setPosition(0, rd, 0);
	Ogre::Entity* pilot = mSM->createEntity("ninja.mesh");

	alaINode_ = mNode_->createChildSceneNode();
	alaINode_->setPosition(40*-rd, 0, 0);
	alaINode_->setScale(3 * largo, largo / 4, largo / 4);
	Ogre::Entity* alaA = mSM->createEntity("cube.mesh");
	alaINode_->attachObject(alaA);

	alaDNode_ = mNode_->createChildSceneNode();
	alaDNode_->setPosition(40*rd, 0, 0);
	alaDNode_->setScale(3 * largo, largo / 4, largo / 4);
	Ogre::Entity* alaB = mSM->createEntity("cube.mesh");
	alaDNode_->attachObject(alaB);

	heliceINode_ = mNode_->createChildSceneNode();
	heliceINode_->setPosition(40* -rd - 120 , 0, 0);
	heliceINode_->setScale(0.5, 0.5, 0.5);
	aspasI = new AspasMolino(heliceINode_,numAspas_, 10, false, 1);

	heliceDNode_ = mNode_->createChildSceneNode();
	heliceDNode_->setPosition(40* rd + 120, 0, 0);
	heliceDNode_->setScale(0.5, 0.5, 0.5);
	aspasD = new AspasMolino(heliceDNode_, numAspas_, 10, false, 1);
}

Avion::~Avion()
{

}

bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	aspasI->keyPressed(evt);
	aspasD->keyPressed(evt);

	return true;
}