#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include "AspasMolino.h"
#include "Molino.h"
#include "Dron.h"
#include "Avion.h"
#include "Sinbad.h"

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

	Molino* mMolino_ = nullptr;
	Dron* mDron_A = nullptr;
	Dron* mDron_B = nullptr;

	Avion* mAvion_ = nullptr;
	Ogre::SceneManager* mSM = nullptr;
	OgreBites::TrayManager* mTrayMgr = nullptr;
	Ogre::SceneNode* mLightNode = nullptr;
	Ogre::SceneNode* mCamNode = nullptr;
	Ogre::SceneNode* mSinbadNode = nullptr; //E3
	OgreBites::CameraMan* mCamMgr = nullptr;

	// reloj
	Ogre::SceneNode* mClockNode = nullptr;
	Ogre::SceneNode* mHourNode[12];
	Ogre::SceneNode* mNeedles[3];

	// E2
	Ogre::SceneNode* planetaNode = nullptr;
	Ogre::SceneNode* ficticioDronNode = nullptr;
	Ogre::SceneNode* medioNode = nullptr;
	Ogre::SceneNode* medioNodemini = nullptr;
	//
	Ogre::SceneNode* avionNode = nullptr;
	Ogre::SceneNode* ficticioAvionNode;
	Ogre::SceneNode* planoNode = nullptr;
	//
	Ogre::Entity* planeta;

	//E3
	Sinbad* sinbadEntidad = nullptr;
	
	
	void createClock();
};

#endif