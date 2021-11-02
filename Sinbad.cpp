#include "Sinbad.h"
#include "OgreFrameListener.h"
#include <SDL_keycode.h>
#include <iostream>
#include <OgreTimer.h>

Sinbad::Sinbad(Ogre::SceneNode* mNode, bool Truco, int Altura)
	: EntidadIG(mNode), TRUCO(Truco), ALTURA(Altura)
{
	generaSinbad();
}

Sinbad::Sinbad(Ogre::SceneNode* mNode)
	: EntidadIG(mNode), TRUCO(-1), ALTURA(-1)
{
	generaSinbad();
}

void Sinbad::generaSinbad()
{
	mTimer_ = new Ogre::Timer();
	mTimer_->reset();
	estadoDeParada = false;

	entity = mSM->createEntity("Sinbad.mesh");
	mNode_->attachObject(entity);

	/// Mostrar estados de animación
	if (SHOW_ANIMS) {
		Ogre::AnimationStateSet* aux = entity->getAllAnimationStates();
		auto it = aux->getAnimationStateIterator().begin();
		std::cout << "//_ Las animaciones esqueletales disponibles para Sinbad son: _\\\\\n";
		while (it != aux->getAnimationStateIterator().end()) {
			auto s = it->first;
			std::cout << "\t* " << s << '\n';
			++it;
		}
	}

	c_pressed = false;

	// al principio Sinbad camina (no baila)

	animationStateBottom = entity->getAnimationState("RunBase");
	animationStateBottom->setEnabled(true);
	animationStateBottom->setLoop(true);

	animationStateTop = entity->getAnimationState("RunTop");
	animationStateTop->setEnabled(true);
	animationStateTop->setLoop(true);

	animationStateDancing = entity->getAnimationState("Dance");
	animationStateDancing->setEnabled(false);
	animationStateDancing->setLoop(true);
}

void Sinbad::arma()
{
}

void Sinbad::arma(bool rH)
{
}

void Sinbad::cambiaEspada()
{
}

void Sinbad::frameRendered(const Ogre::FrameEvent& evt)
{
	if (c_pressed) {
		// actualización de animaciones esqueletales: bailar
		animationStateDancing->addTime(evt.timeSinceLastFrame);

		mTimer_->reset();
		return;
	}
	else {
		if (DANCE_AT_REST) {
			if (estadoDeParada) {
				// actualización de animaciones esqueletales: bailar
				animationStateDancing->addTime(evt.timeSinceLastFrame);
			}
			else {
				// actualización de animaciones esqueletales: caminar
				animationStateBottom->addTime(evt.timeSinceLastFrame);
				animationStateTop->addTime(evt.timeSinceLastFrame);
			}
		}
		else {
			// actualización de animaciones esqueletales: caminar
			animationStateBottom->addTime(evt.timeSinceLastFrame);
			animationStateTop->addTime(evt.timeSinceLastFrame);
		}
	}

	//---

	// movimiento autónomo por el planeta //

	// Código defensivo: para ejecutar esta parte del método, Sinbad debe haberse...
	// ... creado especificando parámetros adicionales con un constructor especial.
	// Ejecutar esta parte del método implica que Sinbad fue creado para caminar sobre el planeta.
	if (TRUCO == -1 || ALTURA == -1) return;

	if (estadoDeParada) { // ver si toca moverse
		if (mTimer_->getMilliseconds() >= DELTA_PARADA) { // toca moverse?
			estadoDeParada = false;
			mTimer_->reset();

			if (DANCE_AT_REST) {
				// cambio de animaciones esqueletales: Sinbad ha de caminar
				animationStateBottom->setEnabled(true);
				animationStateTop->setEnabled(true);
				animationStateDancing->setEnabled(false);
			}

			// cambio de ruta //
			bool cw = rand() % 2;
			float angle = rand() % 180;
			if (!cw) angle *= -1;
			// (truco)
			if (TRUCO) mNode_->yaw(Ogre::Degree(angle));
			// (no-truco)
			else mNode_->getParent()->yaw(Ogre::Degree(angle));
		}
	}
	else { // ver si toca pararse
		if (mTimer_->getMilliseconds() >= DELTA_DESPL) { // toca pararse?
			estadoDeParada = true;
			mTimer_->reset();

			if (DANCE_AT_REST) {
				// cambio de animaciones esqueletales: Sinbad ha de bailar
				animationStateBottom->setEnabled(false);
				animationStateTop->setEnabled(false);
				animationStateDancing->setEnabled(true);
			}
		}
		else {
			// el movimiento debe seguir
			if (TRUCO) { // (truco)
				mNode_->translate(0, -ALTURA, 0, Ogre::Node::TransformSpace::TS_LOCAL); // !
				mNode_->pitch(Ogre::Degree(0.5));
				mNode_->translate(0, ALTURA, 0, Ogre::Node::TransformSpace::TS_LOCAL); // !
			}
			// (no-truco)
			else mNode_->getParent()->pitch(Ogre::Degree(0.5));
		}
	}
}

bool Sinbad::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	switch (evt.keysym.sym)
	{
	case SDLK_c: ///TODO: Debe hacerse mediante eventos //!!!
		cPressed();
		break;
	default:
		break;
	}

	return true;
}

void Sinbad::cPressed()
{
	c_pressed = !c_pressed; // palanca
	if (c_pressed) {
		// cambio de animaciones esqueletales: Sinbad ha de bailar
		animationStateBottom->setEnabled(false);
		animationStateTop->setEnabled(false);
		animationStateDancing->setEnabled(true);
	}
	else {
		// cambio de animaciones esqueletales: Sinbad ha de caminar
		animationStateBottom->setEnabled(true);
		animationStateTop->setEnabled(true);
		animationStateDancing->setEnabled(false);
	}
}