#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>

using namespace Ogre;

const bool E1 = 0;
const bool E1_RELOJ = 0;
const bool E2_TRUCO_DRON = 1;
const float E2_ALTURA_DRON = 550;

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
		// exploracion del dron en E2
		if (ficticioDronNode) {
			// (dron-truco)
			if (E2_TRUCO_DRON) {
				ficticioDronNode->translate(0, -E2_ALTURA_DRON, 0, Ogre::Node::TransformSpace::TS_LOCAL); // !
				ficticioDronNode->pitch(Ogre::Degree(5.0));
				ficticioDronNode->translate(0, E2_ALTURA_DRON, 0, Ogre::Node::TransformSpace::TS_LOCAL); // !
			}
			// (nodo)
			else {
				ficticioDronNode->pitch(Ogre::Degree(5.0), Ogre::Node::TransformSpace::TS_LOCAL);
			}
		}
		break;
	case SDLK_j:
		// direccion del dron en E2
		if (ficticioDronNode) {
			// (dron-truco)
			if (E2_TRUCO_DRON) {
				ficticioDronNode->yaw(Ogre::Degree(5.0), Ogre::Node::TransformSpace::TS_LOCAL);
			}
			// (nodo)
			else {
				ficticioDronNode->yaw(Ogre::Degree(5.0), Ogre::Node::TransformSpace::TS_LOCAL); // !
			}
		}
		break;
	}

	// evento pasa al molino
	if (mMolino_) mMolino_->keyPressed(evt);
	// evento pasa al dron
	if (mDron_) mDron_->keyPressed(evt);
	// evento pasa al avion
	if (mAvion_) mAvion_->keyPressed(evt);

	return true;
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

	mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);

	mCamNode->setPosition(0, 0, 1000);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	//mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  

	// and tell it to render into the main window
	Viewport* vp = getRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));

	//------------------------------------------------------------------------

	// without light we would just get a black screen 

	Light* luz = mSM->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(0.75, 0.75, 0.75);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);

	mLightNode->setDirection(Ogre::Vector3(-1, 1, -1));  //vec3.normalise();
	//lightNode->setPosition(0, 0, 1000);


	Light* luzA = mSM->createLight("LuzA");
	luzA->setType(Ogre::Light::LT_DIRECTIONAL);
	luzA->setDiffuseColour(0.75, 0.75, 0.75);

	Ogre::SceneNode* luzB = mSM->getRootSceneNode()->createChildSceneNode("nLuzB");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	luzB->attachObject(luzA);

	luzB->setDirection(Ogre::Vector3(1, -1, 1));  //vec3.normalise();
	//lightNode->setPosition(0, 0, 1000);

	//------------------------------------------------------------------------

	// finally something to render

	if (E1) { // ENTREGA_1
		// reloj
		if (E1_RELOJ) createClock();
		// molino
		mMolino_ = new Molino(mSM->getRootSceneNode()->createChildSceneNode(), 6, 100, 30);
		addInputListener(mMolino_);
		// dron
		Ogre::SceneNode* node = mSM->getRootSceneNode()->createChildSceneNode();
		node->setScale(0.5, 0.5, 0.5);
		node->setPosition(400, 200, 100);
		mDron_ = new Dron(node, 8, 8, 1);
		addInputListener(mDron_);
	}
	else { // ENTREGA_2
		// planeta
		planetaNode = mSM->getRootSceneNode()->createChildSceneNode();
		planetaNode->scale(5, 5, 5);
		Entity* planeta = mSM->createEntity("sphere.mesh");
		planetaNode->attachObject(planeta);
		// dron explorador
		ficticioDronNode = mSM->getRootSceneNode()->createChildSceneNode();
		if (E2_TRUCO_DRON) {
			ficticioDronNode->translate(0, E2_ALTURA_DRON, 0, Ogre::Node::TransformSpace::TS_LOCAL);
			ficticioDronNode->scale(0.25, 0.25, 0.25);
			mDron_ = new Dron(ficticioDronNode, 5, 8, 1);
			addInputListener(mDron_);
		}
		else {
			medioNode = ficticioDronNode->createChildSceneNode(); // para el (no-truco)
			medioNode->translate(0, E2_ALTURA_DRON, 0);
			medioNode->scale(0.25, 0.25, 0.25);
			mDron_ = new Dron(medioNode, 8, 8, 1);
			addInputListener(mDron_);
		}
		// avion ninja
		avionNode = mSM->getRootSceneNode()->createChildSceneNode();
		avionNode->setPosition(0, 700, 0);
		mAvion_ = new Avion(avionNode, 1, 1, 5);
		addInputListener(mAvion_);
	}

	//---------------------------------------------

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);

	//mCamMgr->setTarget(mSinbadNode);  
	//mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

	//------------------------------------------------------------------------
}