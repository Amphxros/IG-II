#include "BrazoDron.h"

BrazoDron::BrazoDron(Ogre::SceneNode* mNode, int largo, int rd, int numAspas, bool grueso): OgreEntity(mNode)
{
	mCilinder = mNode_->createChildSceneNode();
	mCilinder->setPosition(0, 0, 2 * largo + largo * largo);
	mCilinder->pitch(Ogre::Degree(90));
	
	mCilinder->setScale(largo/2, 5 * largo, largo/2);
	Ogre::Entity* e = mSM->createEntity("Barrel.mesh");
	mCilinder->attachObject(e);

	mMotor_ = mNode_->createChildSceneNode();

	mMotor_->setPosition(0,0, 2.5* (largo +rd)* (largo + rd));
	mRotor_ = new RotorDron(mMotor_, largo/20, numAspas, largo, grueso);
	addListener(mRotor_);
}

BrazoDron::~BrazoDron()
{
	delete mRotor_;
}

bool BrazoDron::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	this->sendEvent(this);
	return true;
}

void BrazoDron::receiveEvent(OgreEntity* entidad)
{
}
