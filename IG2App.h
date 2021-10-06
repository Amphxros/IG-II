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

	Molino* mMolino_ = nullptr;
	Dron* mDron_ = nullptr;
	Ogre::SceneManager* mSM = nullptr;
	OgreBites::TrayManager* mTrayMgr = nullptr;
	Ogre::SceneNode* mLightNode = nullptr;
	Ogre::SceneNode* mCamNode = nullptr;
	Ogre::SceneNode* mSinbadNode = nullptr;
	OgreBites::CameraMan* mCamMgr = nullptr;

	// reloj
	Ogre::SceneNode* mClockNode = nullptr;
	Ogre::SceneNode* mHourNode[12];
	Ogre::SceneNode* mNeedles[3];

	// E2
	Ogre::SceneNode* planetaNode = nullptr;
	Ogre::SceneNode* ficticioDronNode = nullptr;
	Ogre::SceneNode* medioNode = nullptr;

	void createClock();
};

#endif