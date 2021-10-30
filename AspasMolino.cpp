#include "AspasMolino.h"
#include <SDL.h>

AspasMolino::AspasMolino(Ogre::SceneNode* mNode, int numAspas, double largo, bool orn, int ori)
: EntidadIG(mNode), numAspas_(numAspas), orientacion_(ori)
{
	mContainer = mNode_->createChildSceneNode();
	mCenter = mNode_->createChildSceneNode();

	float angle = 90.0f;
	for (int i = 0; i < numAspas_; i++) {
		Aspa* a = new Aspa(mContainer->createChildSceneNode(), largo/30, largo/3 , 0.1, orn);
		a->getNode()->roll(Ogre::Degree(angle));
		a->getAdornoNode()->roll(Ogre::Degree(90 - angle));
		mAspas_vec.push_back(a);
		EntidadIG::addListener(a);
		angle += 360.0f / numAspas_;
	}

	Ogre::Entity* centro = mSM->createEntity("Barrel.mesh");
	mCenter->pitch(Ogre::Degree(90.0));
	mCenter->setPosition(0, 0, 0);
	mCenter->setScale(largo/2, largo/2, largo/2);
	centro->setMaterialName("TopeHeliceAvion");
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
		rotaAspas();
		break;
	case SDLK_c:
		mCenter->translate(0, 0, -5/*, Ogre::Node::TransformSpace::TS_PARENT*/);
		break;
	}
	return true;
}

void AspasMolino::receiveEvent(EntidadIG* entidad)
{
	rotaAspas();
}

void AspasMolino::rotaAspas() {
	mContainer->roll(Ogre::Degree(orientacion_));
	for (Aspa* a : mAspas_vec) {
		a->getAdornoNode()->roll(Ogre::Degree(-orientacion_));
	}
}