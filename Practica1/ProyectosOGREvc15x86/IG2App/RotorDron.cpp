#include "RotorDron.h"

RotorDron::RotorDron(Ogre::SceneNode* mNode, double rd, int numAspas, int largoAspas): Obj(mNode)
{
	Ogre::SceneNode* container = mNode_->createChildSceneNode();
	
	container->setPosition(0, -rd, 0);
	
	Ogre::Entity* e = mSM->createEntity("sphere.mesh");
	container->attachObject(e);

	mAspasNode_ = mNode_->createChildSceneNode();
	mAspasNode_->pitch(Ogre::Degree(-90));
	mAspasNode_->setPosition(0,100,0);
	mAspas_ = new AspasMolino(mAspasNode_, numAspas, largoAspas, false);

}

RotorDron::~RotorDron()
{
	delete mAspas_;
}

bool RotorDron::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	return mAspas_->keyPressed(evt);
}
