#include "RotorDron.h"

RotorDron::RotorDron(Ogre::SceneNode* mNode, double rd, int numAspas, int largoAspas, int grueso): OgreEntity(mNode)
{
	Ogre::SceneNode* container = mNode_->createChildSceneNode();
	
	container->setPosition(0, -rd, 0);
	
	Ogre::Entity* e = mSM->createEntity("sphere.mesh");
	if (grueso) container->setScale(0.65, 0.65, 0.65);
	else container->setScale(0.5, 0.5, 0.5);
	container->attachObject(e);

	mAspasNode_ = mNode_->createChildSceneNode();
	mAspasNode_->pitch(Ogre::Degree(-90));
	mAspasNode_->setPosition(0,50,0);
	mAspas_ = new AspasMolino(mAspasNode_, numAspas, largoAspas, false, 1);
}

RotorDron::~RotorDron()
{
	delete mAspas_;
}

bool RotorDron::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	//return mAspas_->keyPressed(evt);
	return true;

}

void RotorDron::receiveEvent(OgreEntity* entidad)
{
	this->sendEvent(entidad);
}
