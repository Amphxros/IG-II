#include "Dron.h"
#include <SDL_keycode.h>

Dron::Dron(Ogre::SceneNode* mNode, int numBrazos, int numAspas, int rd, bool perturbador, bool Truco, int Altura)
	: EntidadIG(mNode), numBrazos_(numBrazos), numAspas_(numAspas), rd_(rd), perturbador_(perturbador),
	TRUCO(Truco), ALTURA(Altura)
{
	generaDron();
}

Dron::Dron(Ogre::SceneNode* mNode, int numBrazos, int numAspas, int rd, bool perturbador)
	: EntidadIG(mNode), numBrazos_(numBrazos), numAspas_(numAspas), rd_(rd), perturbador_(perturbador),
	TRUCO(-1), ALTURA(-1)
{
	generaDron();
}

void Dron::generaDron() {
	mContainer_ = mNode_->createChildSceneNode();

	mTimer_ = new Ogre::Timer();
	mTimer_->reset();

	// cuerpo
	Ogre::SceneNode* mCenter = mNode_->createChildSceneNode();
	mCenter->setScale(rd_, rd_, rd_);
	cuerpoDron_ = mSM->createEntity("sphere.mesh");
	if (perturbador_) cuerpoDron_->setMaterialName("SmilySphere");
	else cuerpoDron_->setMaterialName("CuerpoDronB");
	mCenter->attachObject(cuerpoDron_);

	// brazos
	mBrazos_.reserve(numBrazos_);
	float angle = 0.0f;
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

	// foco
	Light* luz = mSM->createLight();
	luz->setType(Ogre::Light::LT_SPOTLIGHT);
	luz->setDiffuseColour(0.75, 0.75, 0.75);
	luz->setDirection(0, -1, 0);
	mLuzNode_ = mContainer_->createChildSceneNode();
	mLuzNode_->translate(0, -rd_, 0);
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
	/// INFO: conforme a E2 ('sendEvent' en lugar de cadena tradicional de 'keyPressed')
	this->sendEvent(this);

	if (r_pressed) {
		mTimer_->reset();
		return;
	}

	//---

	// movimiento autónomo por el planeta //

	// Código defensivo: para ejecutar esta parte del método, el dron debe haberse...
	// ... creado especificando parámetros adicionales con un constructor especial.
	// Ejecutar esta parte del método implica que el dron fue creado para orbitar el planeta.
	if (TRUCO == -1 || ALTURA == -1) return;

	if (estadoDeParada) { // ver si toca moverse
		if (mTimer_->getMilliseconds() >= DELTA_PARADA) { // toca moverse?
			estadoDeParada = false;
			mTimer_->reset();

			// cambio de órbita //
			bool cw = rand() % 2;
			float angle = rand() % 180;
			if (!cw) angle *= -1;
			// (truco)
			if (TRUCO) mNode_->yaw(Ogre::Degree(angle)/*, Ogre::Node::TransformSpace::TS_LOCAL*/);
			// (no-truco)
			else mNode_->getParent()->yaw(Ogre::Degree(angle)/*, Ogre::Node::TransformSpace::TS_LOCAL*/);
		}
	}
	else { // ver si toca pararse
		if (mTimer_->getMilliseconds() >= DELTA_DESPL) { // toca pararse?
			estadoDeParada = true;
			mTimer_->reset();
		}
		else {
			// el movimiento debe seguir
			if (TRUCO) { // (truco)
				mNode_->translate(0, -ALTURA, 0, Ogre::Node::TransformSpace::TS_LOCAL); // !
				mNode_->pitch(Ogre::Degree(0.5)/*, Ogre::Node::TransformSpace::TS_LOCAL*/);
				mNode_->translate(0, ALTURA, 0, Ogre::Node::TransformSpace::TS_LOCAL); // !
			}
			// (no-truco)
			else mNode_->getParent()->pitch(Ogre::Degree(0.5)/*, Ogre::Node::TransformSpace::TS_LOCAL*/);
		}
	}
}

bool Dron::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	switch (evt.keysym.sym) {
	case SDLK_r: ///TODO: Debe hacerse mediante eventos //!!!
		setRPressed();
		break;
	}
	// evento pasa al los brazos del dron
	for (BrazoDron* b : mBrazos_) if (!b->keyPressed(evt)) return false;
	return true;
}

void Dron::setRPressed() {
	r_pressed = !r_pressed;
	if (!perturbador_) { //la esfera central del dron se vuelve roja
		if (r_pressed) cuerpoDron_->setMaterialName("CuerpoDronR");
		else cuerpoDron_->setMaterialName("CuerpoDronB");
	}
}