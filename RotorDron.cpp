#include "RotorDron.h"

RotorDron::RotorDron(Ogre::SceneNode* mNode, double rd, int numAspas, int largoAspas, int grueso): EntidadIG(mNode)
{
	Ogre::SceneNode* container = mNode_->createChildSceneNode();
	
	container->setPosition(0, -rd, 0);
	
	Ogre::Entity* e = mSM->createEntity("sphere.mesh");
	e->setMaterialName("HeliceAvion");
	if (grueso) container->setScale(0.65, 0.65, 0.65);
	else container->setScale(0.5, 0.5, 0.5);
	container->attachObject(e);

	mAspasNode_ = mNode_->createChildSceneNode();
	mAspasNode_->pitch(Ogre::Degree(-90));
	mAspasNode_->setPosition(0,50,0);
	mAspas_ = new AspasMolino(mAspasNode_, numAspas, largoAspas, false, 1);
	addListener(mAspas_);
}

RotorDron::~RotorDron()
{
	delete mAspas_;
}

bool RotorDron::keyPressed(const OgreBites::KeyboardEvent& evt)
{

	this->sendEvent(this);
	return true;

}

void RotorDron::receiveEvent(EntidadIG* entidad)
{
}
