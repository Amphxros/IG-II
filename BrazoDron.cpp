#include "BrazoDron.h"

BrazoDron::BrazoDron(Ogre::SceneNode* mNode, int largo, int rd, int numAspas, bool grueso): EntidadIG(mNode)
{
	mCilinder_ = mNode_->createChildSceneNode();
	mCilinder_->setPosition(0, 0, 2 * largo + largo * largo);
	mCilinder_->pitch(Ogre::Degree(90));
	
	mCilinder_->setScale(largo/2, 5 * largo, largo/2);
	Ogre::Entity* e = mSM->createEntity("Barrel.mesh");
	e->setMaterialName("Brazo");
	mCilinder_->attachObject(e);

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
	// evento pasa al rotor
	return mRotor_->keyPressed(evt);
}

void BrazoDron::receiveEvent(EntidadIG* entidad)
{
}