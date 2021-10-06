#include "BrazoDron.h"

BrazoDron::BrazoDron(Ogre::SceneNode* mNode, int largo, int rd, int numAspas): Obj(mNode)
{
	mCilinder = mNode_->createChildSceneNode();
	Ogre::SceneNode* node = mNode_->createChildSceneNode();
	mCilinder->setPosition(0, 0, 2* largo +(largo*largo));
	mCilinder->pitch(Ogre::Degree(90));
	
	mCilinder->setScale(largo/2, 4*largo, largo/2);
	Ogre::Entity* e = mSM->createEntity("Barrel.mesh");
	mCilinder->attachObject(e);

	mMotor_ = mNode_->createChildSceneNode();

	mMotor_->setPosition(0,0, 2.5* (largo +rd)* (largo + rd));
	mRotor_ = new RotorDron(mMotor_, largo/20, numAspas, largo);
}

BrazoDron::~BrazoDron()
{
	delete mRotor_;
}

bool BrazoDron::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	return mRotor_->keyPressed(evt);
}
