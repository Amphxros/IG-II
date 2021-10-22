#include "Avion.h"
#include <SDL.h>

Avion::Avion(Ogre::SceneNode* mNode, float rd, float largo, int nAspas):
	EntidadIG(mNode),numAspas_(nAspas)
{

	mTimerParada_ = new Ogre::Timer();
	mTimerParada_->reset();
	mTimerDespl_ = new Ogre::Timer();
	mTimerParada_->reset();

	cuerpoNode_ = mNode_->createChildSceneNode();
	cuerpoNode_->setScale(rd, rd, rd); // rd/40

	body = mSM->createEntity("sphere.mesh");
	cuerpoNode_->attachObject(body);

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
	heliceINode_->setPosition(60 * -rd - 120 , 0, 50*rd);
	heliceINode_->setScale(0.5, 0.5, 0.5);
	aspasI = new AspasMolino(heliceINode_,numAspas_, 10, true, 1);
	addListener(aspasI);

	heliceDNode_ = mNode_->createChildSceneNode();
	heliceDNode_->setPosition(60 * rd + 120, 0, 50* rd);
	heliceDNode_->setScale(0.5, 0.5, 0.5);
	aspasD = new AspasMolino(heliceDNode_, numAspas_, 10, true, 1);
	addListener(aspasD);

	
	Light* luz = mSM->createLight();
	luz->setType(Ogre::Light::LT_SPOTLIGHT);
	luz->setDiffuseColour(0.75, 0.75, 0.75);
	luz->setDirection(0, -1, 0);
	luzNode_ = mNode_->createChildSceneNode();
	luzNode_->translate(0, -40*rd, 0);
	luzNode_->attachObject(luz);
	
}

Avion::~Avion()
{
}

bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	switch (evt.keysym.sym)
	{
	case SDLK_g:
		this->sendEvent(this);
	default:
		break;
	}
	return true;
}

void Avion::frameRendered(const Ogre::FrameEvent& evt)
{
	if (r_pressed) {
		this->sendEvent(this);
		body->setMaterialName("CuerpoAvionR");
		alaA->setMaterialName("AlaAvionR");
		alaB->setMaterialName("AlaAvionR");
		mTimerDespl_->reset();
		mTimerParada_->reset();
	}
	else {
		//if (OBAMA_SPH) body->setMaterialName("ObamaSphere");
		/*else*/ body->setMaterialName("CuerpoAvion");

		alaA->setMaterialName("AlaAvion");
		alaB->setMaterialName("AlaAvion");
		if (estadoDeParada) // ver si toca moverse
		{
			if (mTimerParada_->getMilliseconds() >= DELTA_PARADA) // toca moverse?
			{
				estadoDeParada = false;
				mTimerParada_->reset();
				mTimerDespl_->reset();//
			}
		}
		else // ver si toca pararse
		{
			// toca pararse?
			if (mTimerDespl_->getMilliseconds() >= DELTA_DESPL) {
				estadoDeParada = true;
				mTimerDespl_->reset();
				mTimerParada_->reset();//

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

				this->sendEvent(this);
				// el movimiento debe seguir
				mNode_->getParent()->pitch(Ogre::Degree(0.5), Ogre::Node::TransformSpace::TS_LOCAL); // (solo para no-truco)
			}
		}
	}
}