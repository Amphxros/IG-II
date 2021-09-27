#include "Molino.h"
#include <SDL.h>

Molino::Molino(Ogre::SceneNode* mNode, int numAspas, int altura, int largoAspas): Obj(mNode), mAspas_(nullptr)
{
	mAspasNode = mNode_->createChildSceneNode();
	mAspasNode->setPosition(0, altura, 0);
	Ogre::SceneNode* mContain = mAspasNode->createChildSceneNode();
	mContain->setPosition(0, 0, 1.5f * altura);
	mAspas_ = new AspasMolino(mContain, 6, 10 , true);


	Ogre::SceneNode* mRoofNode = mNode_->createChildSceneNode();
	Ogre::Entity* en = mSM->createEntity("sphere.mesh");
	mRoofNode->setScale(10*altura/2, 10*altura/2, 10*altura/2);
	mRoofNode->setPosition(0, 3*altura, 0);
	mRoofNode->attachObject(en);
	
	mMolinoNode = mNode_->createChildSceneNode();
	Ogre::Entity* e = mSM->createEntity("Barrel.mesh");
	mMolinoNode->setScale(altura / 2, altura, altura / 2);
	mMolinoNode->attachObject(e);
}

Molino::~Molino()
{
	delete mAspas_;
}

bool Molino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	switch (evt.keysym.sym) {
	case SDLK_h:
		//nodo adicional
		mAspasNode->yaw(Ogre::Degree(5.0));
		// el truco del almendruco
		//mAspasNode->setPosition(0, mAspasNode->getPosition().y, 0);
		//mAspasNode->yaw(Ogre::Degree(5.0));
		//mAspasNode->setPosition(0, mAspasNode->getPosition().y,mAspasNode->getPosition().z* z);
		break;
	}

	return mAspas_->keyPressed(evt);
	
}
