#include "Dron.h"
#include <iostream>

Dron::Dron(Ogre::SceneNode* mNode, int numBrazos, int numAspas, int rd, bool mini): EntidadIG(mNode), numAspas_(numAspas), numBrazos_(numBrazos)
{
	mContainer_ = mNode_->createChildSceneNode();
	
	// cuerpo
	Ogre::SceneNode* mCenter = mNode_->createChildSceneNode();
	mCenter->setScale(rd, rd, rd);
	Ogre::Entity* e = mSM->createEntity("sphere.mesh");
	if (mini) {
		e->setMaterialName("CuerpoAvionR");
	}
	else {
		e->setMaterialName("SmilySphere");
	}
	
	mCenter->attachObject(e);
	
	mBrazos_.reserve(numBrazos);
	// brazos
	float angle = 0.0f; // 90.0f
	for (int i = 0; i < numBrazos_; i++) {
		Ogre::SceneNode* n = mContainer_->createChildSceneNode();
		n->yaw(Ogre::Degree(angle));

		BrazoDron* b = new BrazoDron(n, 10, 1, numAspas_, i == 0);
		addListener(b);
		mBrazos_.push_back(b);
		if (i % 2 == 0) {
			mBrazos_[i]->setOrientacion(-1);
		}

		angle += 360.0f / numBrazos_;
	}
	mTimer_ = new Ogre::Timer();
	mTimer_->reset();

	Light* luz = mSM->createLight();
	luz->setType(Ogre::Light::LT_SPOTLIGHT);
	luz->setDiffuseColour(0.75, 0.75, 0.75);
	luz->setDirection(0, -1, 0);
	mLuzNode_ = mContainer_->createChildSceneNode();
	mLuzNode_->translate(0, -rd, 0);
	mLuzNode_->attachObject(luz);
}

Dron::~Dron()
{
	for (int i = 0; i < mBrazos_.size(); i++) {
		delete mBrazos_[i];
	}
	delete mTimer_;
}

void Dron::frameRendered(const Ogre::FrameEvent& evt)
{
	this->sendEvent(this);
	//std::cout << mTimer_->getMilliseconds() << " ";
	if (r_pressed) {
		mTimer_->reset();
	}
	else {
		if (estadoDeParada) // ver si toca moverse
		{
			if (mTimer_->getMilliseconds() >= DELTA_PARADA) // toca moverse?
			{
				estadoDeParada = false;
				mTimer_->reset();
			}
		}
		else // ver si toca pararse
		{
			// toca pararse?
			if (mTimer_->getMilliseconds() >= DELTA_DESPL) {
				estadoDeParada = true;
				mTimer_->reset();

				// cambio órbita
				bool cw = rand() % 2;
				float angle = rand() % 180;
				if (!cw) { // revisar sentido correcto
					angle *= -1;
				}
				mNode_->getParent()->yaw(Ogre::Degree(angle), Ogre::Node::TransformSpace::TS_LOCAL); // !
			}
			else
			{
				// el movimiento debe seguir
				mNode_->getParent()->pitch(Ogre::Degree(0.5), Ogre::Node::TransformSpace::TS_LOCAL); // (solo para no-truco)
			}
		}

		}
	}

bool Dron::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	return true;
}