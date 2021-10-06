#include "Molino.h"
#include <SDL.h>

Molino::Molino(Ogre::SceneNode* mNode, int numAspas, int altura, int largoAspas): Obj(mNode), mAspas_(nullptr), altura_(altura)
{
	mAspasNode = mNode_->createChildSceneNode();
	mAspasNode->setPosition(0, 2* altura, 0);
	
	container = mAspasNode->createChildSceneNode();
	container->setPosition(0, 0, 1.5f * altura);

	mAspas_ = new AspasMolino(container, numAspas, largoAspas , true,1);

	Ogre::SceneNode* mRoofNode = mNode_->createChildSceneNode();
	mRoofNode->setPosition(0, 3*altura-20, 0);
	mRoofNode->setScale(1.3, 1.3, 1.3);
	Ogre::Entity* en = mSM->createEntity("sphere.mesh");
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
		if (false) {
			// nodo adicional
			mAspasNode->yaw(Ogre::Degree(5.0));
		}
		else
		{
			// el truco del almendruco
			container->translate(0, 0, -1.5 * altura_, Ogre::Node::TransformSpace::TS_LOCAL);
			container->yaw(Ogre::Degree(5.0));
			container->translate(0, 0, 1.5 * altura_, Ogre::Node::TransformSpace::TS_LOCAL);
		}
		break;
	}

	return mAspas_->keyPressed(evt);
}
