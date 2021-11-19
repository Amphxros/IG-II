#include "Avion.h"
#include <SDL.h>
#include "Plano.h"
#include <OGRE/OgreParticleSystem.h>
#include <OGRE/OgreBillboardSet.h>
#include <OGRE/OgreBillboard.h>
Avion::Avion(Ogre::SceneNode* mNode, float rd, float largo, int nAspas, bool Truco, int Altura, bool ate)
	: EntidadIG(mNode), numAspas_(nAspas), TRUCO(Truco), ALTURA(Altura), atentado(ate)
{
	mTimer_ = new Ogre::Timer();
	mTimer_->reset();

	cuerpoNode_ = mNode_->createChildSceneNode();
	cuerpoNode_->setScale(rd, rd, rd); // rd/40

	body = mSM->createEntity("sphere.mesh");
	cuerpoNode_->attachObject(body);
	if (OBAMA_SPH) body->setMaterialName("ObamaSphere");
	else body->setMaterialName("CuerpoAvion");

	pilotoNode_ = mNode_->createChildSceneNode();
	pilotoNode_->setScale(-0.5, 0.5, -0.5);
	pilotoNode_->setPosition(0, 50, 0);
	Ogre::Entity* pilot = mSM->createEntity("ninja.mesh");
	pilot->setMaterialName("NinjaAvion");
	pilotoNode_->attachObject(pilot);
	
	frenteNode_ = mNode_->createChildSceneNode();
	frenteNode_->setPosition(0, 0, 80 * rd);
	frenteNode_->setScale(15, 10, 15);
	frenteNode_->pitch(Ogre::Degree(90));
	Ogre::Entity* front = mSM->createEntity("Barrel.mesh");
	front->setMaterialName("MorroAvion");
	frenteNode_->attachObject(front);

	alaINode_ = mNode_->createChildSceneNode();
	alaINode_->setPosition(40 * -rd, 0, 0);
	alaINode_->setScale(3 * largo, largo / 4,largo);
	alaA = mSM->createEntity("cube.mesh");
	alaA->setMaterialName("AlaAvion");
	alaINode_->attachObject(alaA);
	
	alaDNode_ = mNode_->createChildSceneNode();
	alaDNode_->setPosition(40 * rd, 0, 0);
	alaDNode_->setScale(3 * largo, largo / 4, largo);
	alaB = mSM->createEntity("cube.mesh");
	alaB->setMaterialName("AlaAvion");
	alaDNode_->attachObject(alaB);

	heliceINode_ = mNode_->createChildSceneNode();
	heliceINode_->setPosition(60 * -rd - 120 , 0, 50 * rd);
	heliceINode_->setScale(0.5, 0.5, 0.5);
	aspasI = new AspasMolino(heliceINode_,numAspas_, 10, true, 1);
	addListener(aspasI);

	heliceDNode_ = mNode_->createChildSceneNode();
	heliceDNode_->setPosition(60 * rd + 120, 0, 50 * rd);
	heliceDNode_->setScale(0.5, 0.5, 0.5);
	aspasD = new AspasMolino(heliceDNode_, numAspas_, 10, true, 1);
	addListener(aspasD);

	pointsNode_ = mNode_->createChildSceneNode();
	pointsNode_->setPosition(0, 30, -150);
	pointsNode_->pitch(Ogre::Degree(-90));
	//
	BillboardSet* points = mSM->createBillboardSet("b", 1);
	Billboard* bb = points->createBillboard(Vector3(0, 0, 0));
	points->setDefaultDimensions(50, 50);
	points->setMaterialName("PointsBillboard");
	pointsNode_->attachObject(points);

	particleTrailNode_ = mNode_->createChildSceneNode();
	particleTrailNode_->setPosition(0, -50, -100);
	particleTrailSys_ = mSM->createParticleSystem("trail", "IG2App/Smoke");
	particleTrailSys_->setEmitting(true);
	particleTrailNode_->attachObject(particleTrailSys_);

	Light* luz = mSM->createLight();
	luz->setType(Ogre::Light::LT_SPOTLIGHT);
	luz->setDiffuseColour(0.75, 0.75, 0.75);
	luz->setDirection(0, -1, 0);
	luzNode_ = mNode_->createChildSceneNode();
	luzNode_->translate(0, -40 * rd, 0);
	luzNode_->attachObject(luz);
}

Avion::~Avion()
{
}

void Avion::frameRendered(const Ogre::FrameEvent& evt)
{
	/// INFO: conforme a E2 ('sendEvent' en lugar de cadena tradicional de 'keyPressed')
	
	if (r_pressed) {
		mTimer_->reset();
		return;
	}

	//---

	if (atentado) {
		// movimiento en torno a la bomba del río //
		if (TRUCO) { // (truco)
			mNode_->translate(-ALTURA, 0, 0, Ogre::Node::TransformSpace::TS_LOCAL); // !
			mNode_->yaw(Ogre::Degree(-0.5));
			mNode_->translate(ALTURA, 0, 0, Ogre::Node::TransformSpace::TS_LOCAL); // !
		}
		// (no-truco)
		else mNode_->getParent()->yaw(Ogre::Degree(-0.5));
	}
	else {
		// movimiento autónomo por el planeta //

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
}

bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	switch (evt.keysym.sym)
	{
	case SDLK_g:
		/// INFO: conforme a E2 ('sendEvent' en lugar de cadena tradicional de 'keyPressed')
		break;
	case SDLK_r: ///TODO: Debe hacerse mediante eventos //!!!
		// si se está en la entrega del río, el avión en lugar de detenerse explota
		if (atentado) explode();
		else setRPressed();
		break;
	}
	// el evento keyPressed (evento a la antigua) no pasa más allá en este método, ...
	// ...por ello el desplazamiento del cilindro de las AspasMolino del Avion no ocurre
	return true;
}

void Avion::setRPressed()
{
	// las alas del avión se vuelven rojas
	if (r_pressed) {
		alaA->setMaterialName("AlaAvionR");
		alaB->setMaterialName("AlaAvionR");
	}
	else {
		alaA->setMaterialName("AlaAvion");
		alaB->setMaterialName("AlaAvion");
	}
}

void Avion::explode()
{
	// si ya explotó, no pasa nada (salvo la desactivación del humo)
	if (r_pressed) {
		particleExplosionSys_->setEmitting(false);
		return;
	}

	// desactivamos el trail
	particleTrailSys_->setEmitting(false);
	// activamos explosion
	particleExplosionNode_ = mNode_->createChildSceneNode();
	particleExplosionSys_ = mSM->createParticleSystem("explosion", "IG2App/Explosion");
	particleExplosionSys_->setEmitting(true);
	particleExplosionNode_->attachObject(particleExplosionSys_);

	// explota
	
	// ocultamos todo
	luzNode_->detachAllObjects(); // desactivar foco
	cuerpoNode_->detachAllObjects();
	pilotoNode_->detachAllObjects();
	frenteNode_->detachAllObjects();
	heliceDNode_->detachAllObjects();
	heliceINode_->detachAllObjects();
	alaDNode_->detachAllObjects();
	alaINode_->detachAllObjects();
	pointsNode_->detachAllObjects();
	aspasD->eraseAll();
	aspasI->eraseAll();
	
	// (esto hace que no se trate de ejecutar los moviminetos)
	r_pressed = true;
	this->sendEvent(this);
}
