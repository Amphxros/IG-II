#include "Sinbad.h"
#include "OgreFrameListener.h"
#include <SDL_keycode.h>

Sinbad::Sinbad(Ogre::SceneNode* mNode): EntidadIG(mNode)
{
	entity = mSM->createEntity("Sinbad.mesh");
	mNode_->attachObject(entity);

	/// Mostrar estados de animación
	Ogre::AnimationStateSet* aux = entity->getAllAnimationStates();
	auto it = aux->getAnimationStateIterator().begin();
	while (it != aux->getAnimationStateIterator().end()) {
		auto s = it->first;
		
		++it;
	}
	///

	animationStateBottom = entity->getAnimationState("RunBase");
	animationStateTop = entity->getAnimationState("RunTop");
	animationStateDancing = entity->getAnimationState("Dance");

	animationStateBottom->setEnabled(true);
	animationStateBottom->setLoop(true);

	animationStateTop->setEnabled(true);
	animationStateTop->setLoop(true);

	animationStateDancing->setEnabled(false);
	animationStateDancing->setLoop(true);
	c_pressed = false;

}

void Sinbad::frameRendered(const Ogre::FrameEvent& evt) {

	if (c_pressed) {
		//cambiamos las animaciones esqueletales
		animationStateDancing->setEnabled(true);
		animationStateBottom->setEnabled(false);
		animationStateTop->setEnabled(false);
		//actualizamos las animaciones esqueletales
		animationStateDancing->addTime(evt.timeSinceLastFrame);
	}
	else {
		//cambiamos las animaciones esqueletales
		animationStateDancing->setEnabled(false);
		animationStateBottom->setEnabled(true);
		animationStateTop->setEnabled(true);
		//actualizamos las animaciones esqueletales
		animationStateBottom->addTime(evt.timeSinceLastFrame);
		animationStateTop->addTime(evt.timeSinceLastFrame);

		//actualizar la trayectoria TODO

		if (TRUCO) {
			mNode_->translate(0, -ALTURA, 0, Ogre::Node::TransformSpace::TS_LOCAL); // !
			mNode_->pitch(Ogre::Degree(0.5)/*, Ogre::Node::TransformSpace::TS_LOCAL*/);
			mNode_->translate(0, ALTURA, 0, Ogre::Node::TransformSpace::TS_LOCAL); // !
		}
		else {
			mNode_->getParent()->pitch(Ogre::Degree(0.5));
		}
	}
}

bool Sinbad::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	switch (evt.keysym.sym)
	{
	case SDLK_c:
		c_pressed = !c_pressed;
		break;
	default:
		break;
	}

	return true;
}