#include "BrazoDron.h"

BrazoDron::BrazoDron(Ogre::SceneNode* mNode, int largo, int rd, int numAspas): Obj(mNode)
{
	mCilinder = mNode_->createChildSceneNode();
	mCilinder->setPosition(0, 0, 0);
	mCilinder->pitch(Ogre::Degree(90));
	
	mCilinder->setScale(largo/2, largo*largo, largo/2);
	Ogre::Entity* e = mSM->createEntity("Barrel.mesh");
	mCilinder->attachObject(e);

	mMotor_ = mNode_->createChildSceneNode();

	mMotor_->setPosition(0,0, 2.5* (largo +rd)* (largo + rd));
	mRotor_ = new RotorDron(mMotor_, largo/10, 4, largo/2 );

}

BrazoDron::~BrazoDron()
{
	delete mRotor_;
}

bool BrazoDron::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	return mRotor_->keyPressed(evt);
}
