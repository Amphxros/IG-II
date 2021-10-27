#include "Sinbad.h"
#include "OgreFrameListener.h"

Sinbad::Sinbad(Ogre::SceneNode* mNode): EntidadIG(mNode)
{
	entity = mSM->createEntity("Sinbad.mesh");
	mNode_->attachObject(entity);

	animationState = entity->getAnimationState("RunBase");
	//animationState = entity->getAnimationState("RunTop");
	animationState->setEnabled(true);
	animationState->setLoop(true);
}

void Sinbad::frameRendered(const Ogre::FrameEvent& evt) {
	animationState->addTime(evt.timeSinceLastFrame);

}