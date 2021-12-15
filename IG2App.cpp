#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>

#include "EntidadIG.h"
#include "Plano.h"
#include <OGRE/OgreBillboardSet.h>
#include <OGRE/OgreBillboard.h>
using namespace Ogre;

enum Entregas {
	Ent1, Ent2, Ent3_1, Ent3_2, P2_Ent
};

const Entregas ENTREGA_ACTUAL = Entregas::P2_Ent;
//
const bool E1_RELOJ = 1;
//
const bool E2_TRUCO = 1;
const float E2_ALTURA_DRON = 550;
const float E2_ALTURA_AVION = 700;
//
const bool E3_TRUCO = 1;
const float E3_ALTURA_SINBAD = 600;
const float E3_DISTANCIA_AVION = 400;
const float E3_ALTITUD_AVION = 500;
// (para P2_Ent) --v
const bool E4_TRUCO = 1;
const float E4_DISTANCIA_AVION = 400;
const float E4_ALTITUD_AVION = 500;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	switch (evt.keysym.sym)
	{
	case SDLK_ESCAPE:
		getRoot()->queueEndRendering();
		break;
	case SDLK_g:
		// rotacion reloj
		if (mClockNode) mClockNode->roll(Ogre::Degree(5));
		break;
	case SDLK_h:
		// rotacion esferas reloj
		if (mClockNode) mSM->getSceneNode("esferas")->roll(Ogre::Degree(5));
		//---
		// exploracion del dron en E2
		if (ENTREGA_ACTUAL == Entregas::Ent2 && ficticioDronNode) {
			// (dron-truco)
			if (E2_TRUCO) {
				ficticioDronNode->translate(0, -E2_ALTURA_DRON, 0, Ogre::Node::TransformSpace::TS_LOCAL); // !
				ficticioDronNode->pitch(Ogre::Degree(5.0)/*, Ogre::Node::TransformSpace::TS_LOCAL*/);
				ficticioDronNode->translate(0, E2_ALTURA_DRON, 0, Ogre::Node::TransformSpace::TS_LOCAL); // !
			}
			// (nodo)
			else ficticioDronNode->pitch(Ogre::Degree(5.0)/*, Ogre::Node::TransformSpace::TS_LOCAL*/);
		}
		break;
	case SDLK_j:
		// direccion del dron en E2
		if (ENTREGA_ACTUAL == Entregas::Ent2 && ficticioDronNode) {
			ficticioDronNode->yaw(Ogre::Degree(5.0)/*, Ogre::Node::TransformSpace::TS_LOCAL*/);
		}
		break;

	case SDLK_t:
		
		break;
	}
	// evento pasa al molino
	if (mMolino_) mMolino_->keyPressed(evt);
	// evento pasa a los drones
	if (mDronA_) mDronA_->keyPressed(evt);
	if (mDronB_) mDronB_->keyPressed(evt);
	// evento pasa al avion
	if (mAvion_) mAvion_->keyPressed(evt);
	// evento pasa a Sinbad
	if (mSinbad) mSinbad->keyPressed(evt);
	// evento pasa a bomba
	if (mBomba_) mBomba_->keyPressed(evt);

	return true;
}

void IG2App::frameRendered(const Ogre::FrameEvent& evt)
{
	if (ENTREGA_ACTUAL == Entregas::Ent2 && ficticioDronNode) {
		// evento pasa al dron
		mDronA_->frameRendered(evt);
	}
	if (ficticioDronNodeMini) {
		// evento pasa al dron mini
		mDronB_->frameRendered(evt);
	}
	if (ficticioAvionNode) {
		// evento pasa al avion
		mAvion_->frameRendered(evt);
	}
	if (mSinbadNode) {
		// evento pasa a Sinbad
		mSinbad->frameRendered(evt);
	}
	if (bombaNode) { ///TODO: preguntar al profe si esto se hace así // !!!
		// evento pasa a la bomba
		mBomba_->frameRendered(evt);
	}
	if (planoNode) plano->frameRendered(evt);
}

void IG2App::createClock()
{
	mClockNode = mSM->getRootSceneNode()->createChildSceneNode("nClock");
	Ogre::SceneNode* n = mSM->getSceneNode("nClock")->createChildSceneNode("esferas");
	float angle = 90.0f;
	for (int i = 0; i < 12; i++) {
		float x = Ogre::Math::Cos(Ogre::Degree(angle));
		float z = Ogre::Math::Sin(Ogre::Degree(angle));

		mHourNode[i] = mSM->getSceneNode("esferas")->createChildSceneNode("Hora " + std::to_string(i + 1));
		mHourNode[i]->setPosition(Vector3(1000 * x, 1000 * z, 0));
		if (i % 2 == 0) {
			mSM->getSceneNode("Hora " + std::to_string(i + 1))->setScale(Vector3(0.5f, 0.5f, 0.5f));
		}
		Entity* e = mSM->createEntity("sphere.mesh");
		mHourNode[i]->attachObject(e);

		angle += 360.0f / 12;
	}

	Ogre::SceneNode* node = mSM->getSceneNode("nClock")->createChildSceneNode("n");
	for (int i = 0; i < 3; i++) {
		mNeedles[i] = mSM->getSceneNode("n")->createChildSceneNode("Aguja " + std::to_string(i));

		Entity* e = mSM->createEntity("cube.mesh");
		mNeedles[i]->attachObject(e);
	}

	//horas
	mNeedles[0]->setScale(6, 0.3f, 3);
	mNeedles[0]->setPosition(250, 0, 30);

	//minutos
	mNeedles[1]->setScale(0.3f, 8, 3);
	mNeedles[1]->setPosition(0, 300, 15);

	//segundos
	mNeedles[2]->setScale(0.1f, 10, 3);
	mNeedles[2]->roll(Ogre::Degree(-45), Ogre::Node::TransformSpace::TS_PARENT); /*TS_LOCAL, TS_PARENT, TS_WORLD*/
	mNeedles[2]->setPosition(-250, -250, 0);
}

void IG2App::shutdown()
{
	mShaderGenerator->removeSceneManager(mSM);
	mSM->removeRenderQueueListener(mOverlaySystem);

	mRoot->destroySceneManager(mSM);

	delete mTrayMgr;  mTrayMgr = nullptr;
	delete mCamMgr; mCamMgr = nullptr;

	// do not forget to call the base 
	IG2ApplicationContext::shutdown();
}

void IG2App::setup(void)
{
	// do not forget to call the base first
	IG2ApplicationContext::setup();

	mSM = mRoot->createSceneManager();

	// register our scene with the RTSS
	mShaderGenerator->addSceneManager(mSM);

	mSM->addRenderQueueListener(mOverlaySystem);

	mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);
	mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
	addInputListener(mTrayMgr);

	addInputListener(this);
	setupScene();
}

void IG2App::setupScene(void)
{
	// create the camera
	Camera* cam = mSM->createCamera("Cam");
	cam->setNearClipDistance(1);
	cam->setFarClipDistance(10000);
	cam->setAutoAspectRatio(true);
	//cam->setPolygonMode(Ogre::PM_WIREFRAME); 

	// añadir y configurar cámara para el reflejo
	Camera* camRef = mSM->createCamera("RefCam");
	camRef->setNearClipDistance(1);
	camRef->setFarClipDistance(10000);
	camRef->setAutoAspectRatio(true); //

	mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);

	mCamNode->setPosition(0, 0, 1000);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	//mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  

	// and tell it to render into the main window
	Viewport* vp = getRenderWindow()->addViewport(cam);
	//
	if (ENTREGA_ACTUAL == Entregas::P2_Ent)
		// el puto espacio interestelar
		vp->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));
	else
		vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));

	//------------------------------------------------------------------------

	// without light we would just get a black screen

	if (ENTREGA_ACTUAL == Entregas::P2_Ent) {
		Light* luz = mSM->createLight("Luz");
		luz->setType(Ogre::Light::LT_DIRECTIONAL);
		luz->setDiffuseColour(1.0, 1.0, 1.0);
		luz->setDirection(Ogre::Vector3(0, -1, -1));

		mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz"); //
		//mLightNode = mCamNode->createChildSceneNode("nLuz");
		mLightNode->attachObject(luz);
	}
	else {
		Light* luz = mSM->createLight("Luz");
		luz->setType(Ogre::Light::LT_DIRECTIONAL);
		luz->setDiffuseColour(0.75, 0.75, 0.75);
		//luz->setDirection(...);

		mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz"); //
		//mLightNode = mCamNode->createChildSceneNode("nLuz");
		mLightNode->attachObject(luz);
		mLightNode->setPosition(0, 100, 1000);
		mLightNode->setDirection(Ogre::Vector3(-1, 1, -1));  //vec3.normalise();


		Light* luz2 = mSM->createLight("Luz2");
		luz2->setType(Ogre::Light::LT_DIRECTIONAL);
		luz2->setDiffuseColour(0.75, 0.75, 0.75);

		mLightNode2 = mSM->getRootSceneNode()->createChildSceneNode("nLuz2");
		mLightNode2->attachObject(luz2);
		mLightNode2->setPosition(0, 100, 1000);
		mLightNode2->setDirection(Ogre::Vector3(1, -1, 1));  //vec3.normalise();
	}

	//------------------------------------------------------------------------

	// finally something to render

	if (ENTREGA_ACTUAL == Entregas::Ent1) { // ENTREGA_1
		// reloj
		if (E1_RELOJ) createClock();

		// molino
		mMolino_ = new Molino(mSM->getRootSceneNode()->createChildSceneNode(), 6, 100, 30);

		// dron
		ficticioDronNode = mSM->getRootSceneNode()->createChildSceneNode();
		ficticioDronNode->setPosition(400, 200, 100);
		ficticioDronNode->setScale(0.5, 0.5, 0.5);
		mDronA_ = new Dron(ficticioDronNode, 8, 8, 1, false);
	}
	else if (ENTREGA_ACTUAL == Entregas::Ent2) { // ENTREGA_2
		// planeta
		planetaNode = mSM->getRootSceneNode()->createChildSceneNode();
		planetaNode->scale(5, 5, 5);
		planeta = mSM->createEntity("sphere.mesh");
		planeta->setMaterialName("Planeta");
		planetaNode->attachObject(planeta);

		// plano
		planoNode = mSM->getRootSceneNode()->createChildSceneNode();
		planoNode->setPosition(0, 0, -1000);
		planoNode->pitch(Ogre::Degree(90));
		planoNode->setScale(3, 3, 3);
		plano = new Plano(planoNode, "Plano");

		// dron explorador
		ficticioDronNode = mSM->getRootSceneNode()->createChildSceneNode();
		// dron perturbador
		ficticioDronNodeMini = mSM->getRootSceneNode()->createChildSceneNode();
		// avion ninja
		ficticioAvionNode = mSM->getRootSceneNode()->createChildSceneNode();

		if (E2_TRUCO) {
			// dron explorador
			ficticioDronNode->translate(0, E2_ALTURA_DRON, 0);
			ficticioDronNode->scale(0.25, 0.25, 0.25);
			mDronA_ = new Dron(ficticioDronNode, 5, 3, 1, false, E2_TRUCO, E2_ALTURA_DRON);
			EntidadIG::addListener(mDronA_);

			// dron perturbador
			ficticioDronNodeMini->translate(0, -E2_ALTURA_DRON, 0);
			ficticioDronNodeMini->pitch(Ogre::Degree(180.0));
			ficticioDronNodeMini->scale(0.15, 0.15, 0.15);
			mDronB_ = new Dron(ficticioDronNodeMini, 5, 3, 1, true, E2_TRUCO, E2_ALTURA_DRON);

			// avion ninja
			ficticioAvionNode->setPosition(0, E2_ALTURA_AVION, 0);
			mAvion_ = new Avion(ficticioAvionNode, 1, 1, 5, E2_TRUCO, E2_ALTURA_AVION, false, true);
			EntidadIG::addListener(mAvion_);
		}
		else {
			// dron explorador
			medioDronNode = ficticioDronNode->createChildSceneNode(); // para el (no-truco)
			medioDronNode->translate(0, E2_ALTURA_DRON, 0);
			medioDronNode->scale(0.25, 0.25, 0.25);
			mDronA_ = new Dron(medioDronNode, 5, 3, 1, false, E2_TRUCO, E2_ALTURA_DRON);
			EntidadIG::addListener(mDronA_);

			// dron perturbador
			medioDronNodeMini = ficticioDronNodeMini->createChildSceneNode(); // para el (no-truco)
			medioDronNodeMini->translate(0, -E2_ALTURA_DRON, 0);
			medioDronNodeMini->pitch(Ogre::Degree(180.0));
			medioDronNodeMini->scale(0.15, 0.15, 0.15);
			mDronB_ = new Dron(medioDronNodeMini, 5, 3, 1, true, E2_TRUCO, E2_ALTURA_DRON);

			// avion ninja
			medioAvionNode = ficticioAvionNode->createChildSceneNode(); // para el (no-truco)
			medioAvionNode->setPosition(0, E2_ALTURA_AVION, 0);
			mAvion_ = new Avion(medioAvionNode, 1, 1, 5, E2_TRUCO, E2_ALTURA_AVION, false, true);
			EntidadIG::addListener(mAvion_);
		}
	}
	else if (ENTREGA_ACTUAL == Entregas::Ent3_1) { // ENTREGA_3 - Sinbad en planeta
		// planeta
		planetaNode = mSM->getRootSceneNode()->createChildSceneNode();
		planetaNode->scale(5, 5, 5);
		planeta = mSM->createEntity("sphere.mesh");
		planeta->setMaterialName("Planeta");
		planetaNode->attachObject(planeta);

		// plano
		planoNode = mSM->getRootSceneNode()->createChildSceneNode();
		planoNode->setPosition(0, 0, -1000);
		planoNode->pitch(Ogre::Degree(90));
		planoNode->setScale(3, 3, 3);
		plano = new Plano(planoNode, "Plano");

		// Sinbad el ogro marino
		mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode();
		if (E3_TRUCO) { // Sinbad usa el gran truco del famoso indio del libro
			mSinbadNode->translate(0, E3_ALTURA_SINBAD, 0);
			mSinbadNode->scale(20, 20, 20);
			mSinbad = new Sinbad(mSinbadNode, E3_TRUCO, E3_ALTURA_SINBAD);
		}
		else { // Sinbad usa un nodo intermedio
			mNoTrucoSinbadNode = mSinbadNode->createChildSceneNode(); // para el (no-truco)
			mNoTrucoSinbadNode->translate(0, E3_ALTURA_SINBAD, 0);
			mNoTrucoSinbadNode->scale(20, 20, 20);
			mSinbad = new Sinbad(mNoTrucoSinbadNode, E3_TRUCO, E3_ALTURA_SINBAD);
		}
	}
	else if (ENTREGA_ACTUAL == Entregas::Ent3_2) { // ENTREGA_3 - Sinbad en atentado 
		// río -> plano con textura 
		planoNode= mSM->getRootSceneNode()->createChildSceneNode();
		planoNode->setScale(3, 3, 3);
		planoNode->setPosition(0, 0, 0);
		plano = new Plano(planoNode, "RioAgua");
		EntidadIG::addListener(plano);

		// plataforma amarilla
		Ogre::SceneNode* platAmarilla= mSM->getRootSceneNode()->createChildSceneNode();
		platAmarilla->setPosition(-1000, 5, 1000);
		Plano* pAmarilla = new Plano(platAmarilla, "PlataformaAmarilla");

		// plataforma roja
		Ogre::SceneNode* platRoja= mSM->getRootSceneNode()->createChildSceneNode();
		platRoja->setPosition(1000, 5, -1000);
		Plano* pRoja = new Plano(platRoja, "PlataformaRoja");

		// bomba
		bombaNode = mSM->getRootSceneNode()->createChildSceneNode();
		bombaNode->setPosition(0, 10, 0);
		bombaNode->setScale(30, 30, 30);
		mBomba_ = new Bomba(bombaNode, "Bomba");
		EntidadIG::addListener(mBomba_);

		// cara perturbadora
		Ogre::SceneNode* faceNode = mSM->getRootSceneNode()->createChildSceneNode();
		faceNode->setPosition(1000, 100, -1000);
		faceNode->scale(0.5, 0.5, 0.5);
		Entity* face = mSM->createEntity("sphere.mesh");
		face->setMaterialName("SmilySphere"); //ObamaSphere
		faceNode->attachObject(face);

		// Sinbad el ogro marino
		mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode();
		mSinbadNode->translate(-1000, 100, 1000);
		mSinbadNode->scale(20, 20, 20);
		mSinbad = new Sinbad(mSinbadNode, true);
		EntidadIG::addListener(mSinbad);
		
		// avión
		ficticioAvionNode = mSM->getRootSceneNode()->createChildSceneNode();
		if (E3_TRUCO) {
			ficticioAvionNode->setPosition(E3_DISTANCIA_AVION, E3_ALTITUD_AVION, 0);
			mAvion_ = new Avion(ficticioAvionNode, 1, 1, 5, E3_TRUCO, E3_DISTANCIA_AVION, true, true);
		}
		else {
			medioAvionNode = ficticioAvionNode->createChildSceneNode(); // para el (no-truco)
			medioAvionNode->setPosition(E3_DISTANCIA_AVION, E3_ALTITUD_AVION, 0);
			mAvion_ = new Avion(medioAvionNode, 1, 1, 5, E3_TRUCO, E3_DISTANCIA_AVION, true, true);
		}

		// niebla
		nieblaNode = mSM->getRootSceneNode()->createChildSceneNode();
		nieblaNode->setPosition(Vector3(800, 150, -500));
		nieblaSet = mSM->createBillboardSet("fogBbSet", 15);
		nieblaSet->setDefaultDimensions(1000, 1000);
		nieblaSet->setMaterialName("Smoke");
		int capas = 5;
		int escalones = 3;
		for (int i = 0; i < capas; i++) { // cada uno: repartido a lo ancho en capas
			for (int j = 0; j < escalones; j++) { // cada uno: echado hacia atrás y con alturas como escalones
				Vector3 offset(100 * (j % escalones), 300 * (j % escalones), 500 * (i % capas));
				Ogre::Billboard* nieblaBillboard = nieblaSet->createBillboard(nieblaNode->getPosition() + offset);
			}
		}
		nieblaNode->attachObject(nieblaSet);
	}
	else if (ENTREGA_ACTUAL == Entregas::P2_Ent) { // ENTREGA_4 y ENTREGA_5
		// plano celeste
		mSM->setSkyPlane(
			/*enable*/
			true,
			/*plane*/
			Plane(Vector3::UNIT_Z, -20),
			/*materialName*/ // nombre del material
			"Espacio", // (i) anteriormente: "Space", "PlanoCeleste"; ahora: "Espacio"
			/*scale = 1000*/
			0.25,
			/*tiling = 10*/
			1,
			/*drawFirst*/ // dibujarse primero
			true,
			/*bow = 0*/ // curvatura
			0.0,
			/*Xsegments = 1*/
			100,
			/*Ysegments = 1*/
			100
		);

		// río -> plano con textura 
		planoNode = mSM->getRootSceneNode()->createChildSceneNode();
		planoNode->setScale(3, 3, 3);
		planoNode->setPosition(0, 0, 0);
		plano = new Plano(planoNode, "RioAgua");
		EntidadIG::addListener(plano);

		// plataforma amarilla
		Ogre::SceneNode* platAmarilla = mSM->getRootSceneNode()->createChildSceneNode();
		platAmarilla->setPosition(1000, 5, -1000);
		Plano* pAmarilla = new Plano(platAmarilla, "PlataformaAmarilla");

		// bomba
		bombaNode = mSM->getRootSceneNode()->createChildSceneNode();
		bombaNode->setPosition(0, 10, 0);
		bombaNode->setScale(30, 30, 30);
		mBomba_ = new Bomba(bombaNode, "BombaAgujereadaIluminada"); // (i) anteriormente: "BombaTeselada", "BombaAgujereada"; ahora: "BombaAgujereadaIluminada"
		EntidadIG::addListener(mBomba_);

		// cara perturbadora
		Ogre::SceneNode* faceNode = mSM->getRootSceneNode()->createChildSceneNode();
		faceNode->setPosition(1000, 100, -1000);
		faceNode->scale(0.5, 0.5, 0.5);
		Entity* face = mSM->createEntity("sphere.mesh");
		face->setMaterialName("SmilySphere"); //ObamaSphere
		faceNode->attachObject(face);

		// Sinbad el ogro marino
		mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode();
		mSinbadNode->translate(-1000, 100, 1000);
		mSinbadNode->scale(20, 20, 20);
		mSinbad = new Sinbad(mSinbadNode, true);
		EntidadIG::addListener(mSinbad);

		// avión
		ficticioAvionNode = mSM->getRootSceneNode()->createChildSceneNode();
		if (E4_TRUCO) {
			ficticioAvionNode->setPosition(E4_DISTANCIA_AVION, E4_ALTITUD_AVION, 0);
			mAvion_ = new Avion(ficticioAvionNode, 1, 1, 5, E4_TRUCO, E4_DISTANCIA_AVION, true, false);
		}
		else {
			medioAvionNode = ficticioAvionNode->createChildSceneNode(); // para el (no-truco)
			medioAvionNode->setPosition(E4_DISTANCIA_AVION, E4_ALTITUD_AVION, 0);
			mAvion_ = new Avion(medioAvionNode, 1, 1, 5, E4_TRUCO, E4_DISTANCIA_AVION, true, false);
		}
	}
	else { // ENTREGA_???

	}

	//---------------------------------------------

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);

	//mCamMgr->setTarget(mSinbadNode);  
	//mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

	//------------------------------------------------------------------------
}