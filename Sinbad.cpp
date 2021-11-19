#include "Sinbad.h"
#include "OgreFrameListener.h"
#include <SDL_keycode.h>
#include <iostream>
#include <OgreTimer.h>
#include "Bomba.h"

Sinbad::Sinbad(Ogre::SceneNode* mNode, bool cam)
	: EntidadIG(mNode), TRUCO(-1), ALTURA(-1), caminanteRio(cam) {
	generaSinbad();
}
Sinbad::Sinbad(Ogre::SceneNode* mNode, bool Truco, float Altura)
	: EntidadIG(mNode), TRUCO(Truco), ALTURA(Altura), caminanteRio(false) {
	generaSinbad();
}
Sinbad::Sinbad(Ogre::SceneNode* mNode)
	: EntidadIG(mNode), TRUCO(-1), ALTURA(-1), caminanteRio(false) {
	generaSinbad();
}

void Sinbad::configMvAnim() {
	mvAnimation = mSM->createAnimation("CarreraRio", mvAnimDuration);
	mvTrack = mvAnimation->createNodeTrack(0);
	mvTrack->setAssociatedNode(mNode_);
	Ogre::Real durPaso = mvAnimDuration / 5.0; // 5 pasos intermedios de la misma duración
	//
	// fotogramas
	Ogre::Vector3 destinoRojo(1000, 100, -1000);
	Ogre::Vector3 destinoAmarillo(-1000, 100, 1000);
	Ogre::Vector3 ejeRot(0, 1, 0);
	float anguloRot = 0;
	Ogre::TransformKeyFrame* kf;
	/* 6 keyFrames:
	origen
	giroRojo
	pasoRojo
	giroAmarillo
	pasoAmarillo
	giroOrigen */
	/**/
	// Origen (estoy en amarillo)
	kf = mvTrack->createNodeKeyFrame(durPaso * 0);
	kf->setTranslate(destinoAmarillo);
	kf->setRotation(Ogre::Quaternion(Ogre::Degree(anguloRot), ejeRot));
	kf->setScale({ 20, 20, 20 });
	// GiroRojo (sigo en amarillo)
	kf = mvTrack->createNodeKeyFrame(durPaso * 1);
	anguloRot += 135;
	kf->setTranslate(destinoAmarillo);
	kf->setRotation(Ogre::Quaternion(Ogre::Degree(anguloRot), ejeRot));
	kf->setScale({ 20, 20, 20 });
	// PasoRojo (ya no estoy en amarillo)
	kf = mvTrack->createNodeKeyFrame(durPaso * 2);
	kf->setTranslate(destinoRojo);
	kf->setRotation(Ogre::Quaternion(Ogre::Degree(anguloRot), ejeRot));
	kf->setScale({ 20, 20, 20 });
	// GiroAmarillo
	kf = mvTrack->createNodeKeyFrame(durPaso * 3);
	anguloRot -= 180;
	kf->setTranslate(destinoRojo);
	kf->setRotation(Ogre::Quaternion(Ogre::Degree(anguloRot), ejeRot));
	kf->setScale({ 20, 20, 20 });
	// PasoAmarillo
	kf = mvTrack->createNodeKeyFrame(durPaso * 4);
	kf->setTranslate(destinoAmarillo);
	kf->setRotation(Ogre::Quaternion(Ogre::Degree(anguloRot), ejeRot));
	kf->setScale({ 20, 20, 20 });
	// GiroOrigen
	kf = mvTrack->createNodeKeyFrame(durPaso * 5);
	anguloRot += 45;
	kf->setTranslate(destinoAmarillo);
	kf->setRotation(Ogre::Quaternion(Ogre::Degree(anguloRot), ejeRot));
	kf->setScale({ 20, 20, 20 });
	//
	mvAnimationState = mSM->createAnimationState("CarreraRio");
	mvAnimationState->setLoop(true);
	mvAnimationState->setEnabled(true);
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
	dead = false;

	// al principio Sinbad camina (no baila)

	animationStateRunBottom = entity->getAnimationState("RunBase");
	animationStateRunBottom->setEnabled(true);
	animationStateRunBottom->setLoop(true);

	animationStateRunTop = entity->getAnimationState("RunTop");
	animationStateRunTop->setEnabled(true);
	animationStateRunTop->setLoop(true);

	animationStateDancing = entity->getAnimationState("Dance");
	animationStateDancing->setEnabled(false);
	animationStateDancing->setLoop(true);

	animationStateDeadBottom = entity->getAnimationState("IdleBase");
	animationStateDeadBottom->setEnabled(false);
	animationStateDeadBottom->setLoop(true);
	
	animationStateDeadTop = entity->getAnimationState("IdleTop");
	animationStateDeadTop->setEnabled(false);
	animationStateDeadTop->setLoop(true);

	// animación: carrera en el río
	// (solo para la parte 2 de la E3 (de la práctica 1))
	if (caminanteRio) configMvAnim();

	// espadas uwu
	rightSword = mSM->createEntity("Sword.mesh");
	leftSword = mSM->createEntity("Sword.mesh");
	leftHandOccupied = false;
	rightHandOccupied = false;
	//
	arma(true);
	///arma(false);
	///cambiaEspada();
	///arma();
}

void Sinbad::arma()
{
	if (!rightHandOccupied) {
		entity->attachObjectToBone("Handle.R", rightSword);
		rightHandOccupied = true;
	}
	if (!leftHandOccupied) {
		entity->attachObjectToBone("Handle.L", leftSword);
		leftHandOccupied = true;
	}
}

void Sinbad::arma(bool rH)
{
	if (rH) { // arma va a mano derecha
		if (leftHandOccupied) {
			entity->detachObjectFromBone(leftSword);
			leftHandOccupied = false;
		}
		if (!rightHandOccupied) {
			entity->attachObjectToBone("Handle.R", rightSword);
			rightHandOccupied = true;
		}
	}
	else { // arma va a mano izquierda
		if (rightHandOccupied) {
			entity->detachObjectFromBone(rightSword);
			rightHandOccupied = false;
		}
		if (!leftHandOccupied) {
			entity->attachObjectToBone("Handle.L", leftSword);
			leftHandOccupied = true;
		}
	}
}

void Sinbad::cambiaEspada()
{
	if (leftHandOccupied) {
		if (!rightHandOccupied) {
			// pase de i. a d.
			entity->detachObjectFromBone(leftSword);
			leftHandOccupied = false;
			entity->attachObjectToBone("Handle.R", rightSword);
			rightHandOccupied = true;
		}
	}
	else if (rightHandOccupied) {
		if (!leftHandOccupied) {
			// pase de d. a i.
			entity->detachObjectFromBone(rightSword);
			rightHandOccupied = false;
			entity->attachObjectToBone("Handle.L", leftSword);
			leftHandOccupied = true;
		}
	}
}

void Sinbad::desarma()
{
	if (leftHandOccupied) {
		entity->detachObjectFromBone(leftSword);
		leftHandOccupied = false;
	}
	if (rightHandOccupied) {
		entity->detachObjectFromBone(rightSword);
		rightHandOccupied = false;
	}
}

void Sinbad::frameRendered(const Ogre::FrameEvent& evt)
{
	if (dead) {
		// animación esqueletal de moribundo
		animationStateDeadBottom->addTime(evt.timeSinceLastFrame);
		animationStateDeadTop->addTime(evt.timeSinceLastFrame);
		return;
	}
	else {
		if (caminanteRio) // carrera en el río (animación de nodo)
			mvAnimationState->addTime(evt.timeSinceLastFrame);
	}

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
				animationStateRunBottom->addTime(evt.timeSinceLastFrame);
				animationStateRunTop->addTime(evt.timeSinceLastFrame);
			}
		}
		else {
			// actualización de animaciones esqueletales: caminar
			animationStateRunBottom->addTime(evt.timeSinceLastFrame);
			animationStateRunTop->addTime(evt.timeSinceLastFrame);
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
				animationStateRunBottom->setEnabled(true);
				animationStateRunTop->setEnabled(true);
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
				animationStateRunBottom->setEnabled(false);
				animationStateRunTop->setEnabled(false);
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

void Sinbad::receiveEvent(EntidadIG* entidad)
{
	if (dynamic_cast<Bomba*>(entidad) != nullptr){
		die();
	}
}

void Sinbad::die()
{
	if (!dead && caminanteRio) {
		// cambio de animaciones esqueletales: Sinbad ha de morirse
		animationStateRunBottom->setEnabled(false);
		animationStateRunTop->setEnabled(false);
		animationStateDancing->setEnabled(false);
		animationStateDeadBottom->setEnabled(true);
		animationStateDeadTop->setEnabled(true);
		dead = true;
		////mvAnimationState->setEnabled(false);

		// se le quitan las espadas
		desarma();

		// rotación del nodo (caída boca arriba) (¡solo hecho en modo "truco"!)
		mNode_->pitch(Ogre::Degree(90.0f));///TODO

		///TODO: temporizador para que no sea al instante
	}
}

void Sinbad::cPressed()
{
	if (dead) return;

	c_pressed = !c_pressed; // palanca
	if (c_pressed) {
		// cambio de animaciones esqueletales: Sinbad ha de bailar
		animationStateRunBottom->setEnabled(false);
		animationStateRunTop->setEnabled(false);
		animationStateDancing->setEnabled(true);
	}
	else {
		// cambio de animaciones esqueletales: Sinbad ha de caminar
		animationStateRunBottom->setEnabled(true);
		animationStateRunTop->setEnabled(true);
		animationStateDancing->setEnabled(false);
	}
}