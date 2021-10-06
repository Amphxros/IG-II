#include "AspasMolino.h"
#include <SDL.h>

AspasMolino::AspasMolino(Ogre::SceneNode* mNode, int numAspas, double largo, bool orn, int ori)
: Obj(mNode), numAspas_(numAspas), orientacion_(ori)
{
	mContainer = mNode_->createChildSceneNode();
	mCenter = mNode_->createChildSceneNode();

	float angle = 90.0f;
	for (int i = 0; i < numAspas_; i++) {
		Aspa* a = new Aspa(mContainer->createChildSceneNode(), largo/30, largo/3 , 0.1, orn);
		a->getNode()->roll(Ogre::Degree(angle));
		a->getAdornoNode()->roll(Ogre::Degree(90 - angle));
		mAspas_vec.push_back(a);

		angle += 360.0f / numAspas_;
	}

	Ogre::Entity* centro = mSM->createEntity("Barrel.mesh");
	mCenter->pitch(Ogre::Degree(90.0));
	mCenter->setPosition(0, 0, 0);
	mCenter->setScale(largo/2, largo/2, largo/2);
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
		mContainer->roll(Ogre::Degree(orientacion_));
		for (Aspa* a : mAspas_vec) {
			a->getAdornoNode()->roll(Ogre::Degree(-orientacion_));
			}
		break;
	case SDLK_c:
		//if (mCenter->getPosition().z < 0) {
			mCenter->setPosition(mCenter->getPosition().x, mCenter->getPosition().y, mCenter->getPosition().z - 5);
		//}
		//else if(mCenter->getPosition().z> 30) {
		//	mCenter->setPosition(mCenter->getPosition().x, mCenter->getPosition().y, mCenter->getPosition().z + 5);
		//}
		
		break;
	}
	return true;
}
