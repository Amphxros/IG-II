#include "AspasMolino.h"
#include <SDL.h>

AspasMolino::AspasMolino(Ogre::SceneNode* mNode, int numAspas, int largo, bool orn): Obj(mNode), numAspas_(numAspas)
{
	mAspas_vec = std::vector<Aspa*>(numAspas_);

	mContainer = mNode_->createChildSceneNode();
	mCenter = mNode_->createChildSceneNode();

	float angle = 90.0f;
	for (int i = 0; i < numAspas_; i++) {
		Aspa* a = new Aspa(mContainer->createChildSceneNode(), 2, largo, 0.5, orn);
		a->getNode()->roll(Ogre::Degree(angle));
		mAspas_vec[i] = a;

		angle += 360.0f / numAspas_;
	}

	Ogre::Entity* centro = mSM->createEntity("Barrel.mesh");
	mCenter->pitch(Ogre::Degree(90.0));
	mCenter->setPosition(10, 10, 10);
	mCenter->setScale(30,10,30);
	mCenter->attachObject(centro);
}

AspasMolino::~AspasMolino()
{
	for (int i = 0; i < mAspas_vec.size(); i++) {
		delete mAspas_vec[i];
	}
}

bool AspasMolino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	switch (evt.keysym.sym) {
	case SDLK_g:
		mContainer->roll(Ogre::Degree(0.5f));
		break;
	case SDLK_c:
		if (mCenter->getPosition().z < 0) {
			mCenter->setPosition(mCenter->getPosition().x, mCenter->getPosition().y, mCenter->getPosition().z - 5);
		}
		else if(mCenter->getPosition().z> 30 ) {
			mCenter->setPosition(mCenter->getPosition().x, mCenter->getPosition().y, mCenter->getPosition().z + 5);
		}
		
		break;
	}
	return true;
}
