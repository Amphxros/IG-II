#include "Avion.h"
#include <SDL.h>

Avion::Avion(Ogre::SceneNode* mNode, float rd, float largo, int nAspas):
	OgreEntity(mNode),numAspas_(nAspas)
{
	cuerpoNode_ = mNode_->createChildSceneNode();
	cuerpoNode_->setScale(rd, rd, rd); // rd/40
	Ogre::Entity* body = mSM->createEntity("sphere.mesh");
	cuerpoNode_->attachObject(body);

	pilotoNode_ = mNode_->createChildSceneNode();
	pilotoNode_->setScale(-0.5, 0.5, -0.5);
	pilotoNode_->setPosition(0, 50, 0);
	Ogre::Entity* pilot = mSM->createEntity("ninja.mesh");
	pilotoNode_->attachObject(pilot);
	
	frenteNode_ = mNode_->createChildSceneNode();
	frenteNode_->setPosition(0, 0, 80 * rd);
	frenteNode_->setScale(15, 10, 15);
	frenteNode_->pitch(Ogre::Degree(90));
	Ogre::Entity* front = mSM->createEntity("Barrel.mesh");
	frenteNode_->attachObject(front);

	alaINode_ = mNode_->createChildSceneNode();
	alaINode_->setPosition(40 * -rd, 0, 0);
	alaINode_->setScale(3 * largo, largo / 4, largo / 4);
	Ogre::Entity* alaA = mSM->createEntity("cube.mesh");
	alaINode_->attachObject(alaA);
	
	alaDNode_ = mNode_->createChildSceneNode();
	alaDNode_->setPosition(40 * rd, 0, 0);
	alaDNode_->setScale(3 * largo, largo / 4, largo / 4);
	Ogre::Entity* alaB = mSM->createEntity("cube.mesh");
	alaDNode_->attachObject(alaB);

	heliceINode_ = mNode_->createChildSceneNode();
	heliceINode_->setPosition(40 * -rd - 120 , 0, 8*rd);
	heliceINode_->setScale(0.5, 0.5, 0.5);
	aspasI = new AspasMolino(heliceINode_,numAspas_, 10, false, 1);
	addListener(aspasI);

	heliceDNode_ = mNode_->createChildSceneNode();
	heliceDNode_->setPosition(40 * rd + 120, 0, 8* rd);
	heliceDNode_->setScale(0.5, 0.5, 0.5);
	aspasD = new AspasMolino(heliceDNode_, numAspas_, 10, false, 1);
	addListener(aspasD);
	
	Light* luz = mSM->createLight();
	luz->setType(Ogre::Light::LT_SPOTLIGHT);
	luz->setDiffuseColour(0.75, 0.75, 0.75);
	luz->setDirection(0, -1, 0);
	luzNode_ = mNode_->createChildSceneNode();
	luzNode_->translate(0, -40*rd, 0);
	luzNode_->attachObject(luz);
}

Avion::~Avion()
{

}

bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	this->sendEvent(this);
	return true;
}