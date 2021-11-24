#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include "AspasMolino.h"
#include "Molino.h"
#include "Plano.h"
#include "Dron.h"
#include "Avion.h"
#include "Sinbad.h"
#include "Bomba.h"

class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener
{
public:
	explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()  
	virtual ~IG2App() { };   // delete -> shutdown()

protected:
	virtual void setup();
	virtual void shutdown();
	virtual void setupScene();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
	virtual void frameRendered(const Ogre::FrameEvent& evt);

	Ogre::SceneManager* mSM = nullptr;
	OgreBites::TrayManager* mTrayMgr = nullptr;
	Ogre::SceneNode* mLightNode = nullptr;
	Ogre::SceneNode* mLightNode2 = nullptr;
	Ogre::SceneNode* mCamNode = nullptr;
	OgreBites::CameraMan* mCamMgr = nullptr;

	// molino
	Molino* mMolino_ = nullptr;

	// reloj
	Ogre::SceneNode* mClockNode = nullptr;
	Ogre::SceneNode* mHourNode[12];
	Ogre::SceneNode* mNeedles[3];

	void createClock();


	// E2
	Ogre::Entity* planeta = nullptr;
	Ogre::SceneNode* planetaNode = nullptr;
	//
	Plano* plano = nullptr;
	Ogre::SceneNode* planoNode = nullptr;
	//
	Dron* mDronA_ = nullptr;
	Ogre::SceneNode* ficticioDronNode = nullptr;
	Ogre::SceneNode* medioDronNode = nullptr;
	//
	Dron* mDronB_ = nullptr;
	Ogre::SceneNode* ficticioDronNodeMini = nullptr;
	Ogre::SceneNode* medioDronNodeMini = nullptr;
	//
	Avion* mAvion_ = nullptr;
	Ogre::SceneNode* ficticioAvionNode;
	Ogre::SceneNode* medioAvionNode = nullptr;

	// E3
	Sinbad* mSinbad = nullptr;
	Ogre::SceneNode* mSinbadNode = nullptr;
	Ogre::SceneNode* mNoTrucoSinbadNode = nullptr;
	//
	Bomba* mBomba_ = nullptr;
	Ogre::SceneNode* bombaNode = nullptr;
	//
	Ogre::BillboardSet* nieblaSet = nullptr;
	Ogre::SceneNode* nieblaNode = nullptr;
};

#endif