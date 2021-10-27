#include "Sinbad.h"
#include "OgreFrameListener.h"

Sinbad::Sinbad(Ogre::SceneNode* mNode): EntidadIG(mNode)
{
	entity = mSM->createEntity("Sinbad.mesh");
	mNode_->attachObject(entity);

	animationStateBottom = entity->getAnimationState("RunBase");
	animationStateTop = entity->getAnimationState("RunTop");
	animationStateBottom->setEnabled(true);
	animationStateBottom->setLoop(true);
	animationStateTop->setEnabled(true);
	animationStateTop->setLoop(true);
}

void Sinbad::frameRendered(const Ogre::FrameEvent& evt) {
	animationStateBottom->addTime(evt.timeSinceLastFrame);
	animationStateTop->addTime(evt.timeSinceLastFrame);
}