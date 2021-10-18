#include "Dron.h"

Dron::Dron(Ogre::SceneNode* mNode, int numBrazos, int numAspas, int rd): OgreEntity(mNode), numAspas_(numAspas), numBrazos_(numBrazos)
{
	mContainer_ = mNode_->createChildSceneNode();
	
	// cuerpo
	Ogre::SceneNode* mCenter = mNode_->createChildSceneNode();
	mCenter->setScale(rd, rd, rd);
	Ogre::Entity* e = mSM->createEntity("sphere.mesh");
	mCenter->attachObject(e);
	mBrazos_.reserve(numBrazos);
	// brazos
	float angle = 00.0f; // 90.0f
	for (int i = 0; i < numBrazos_; i++) {
		Ogre::SceneNode* n = mContainer_->createChildSceneNode();
		n->yaw(Ogre::Degree(angle));

		BrazoDron* b = new BrazoDron(n, 10, 1, numAspas_, i == 0);
		mBrazos_.push_back(b);
		if (i % 2 == 0) {
			mBrazos_[i]->setOrientacion(-1);
		}

		angle += 360.0f / numBrazos_;
	}
	mTimer = new Ogre::Timer();
	mTimer->reset();
}

Dron::~Dron()
{
	for (int i = 0; i < mBrazos_.size(); i++) {
		delete mBrazos_[i];
	}
	delete mTimer;
}

void Dron::frameRendered(const Ogre::FrameEvent& evt)
{

	if (mTimer->getMilliseconds() >= 2000) {
		float angle = rand() % 360;
		mNode_->pitch(Ogre::Degree(angle));
		mTimer->reset();
	}


}

bool Dron::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	for (int i = 0; i < mBrazos_.size(); i++) {
		mBrazos_[i]->keyPressed(evt);
	}
	return true;
}
