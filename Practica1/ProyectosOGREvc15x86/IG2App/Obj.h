#pragma once
#include <OgreInput.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>

class Obj : public OgreBites::InputListener {
public:
	Obj(Ogre::SceneNode* node);
	~Obj();
	
	// Métodos de InputListener que pueden redefinirse
	virtual void frameRendered(const Ogre::FrameEvent& evt);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual bool keyReleased(const OgreBites::KeyboardEvent& evt);
	virtual bool mousePressed(const OgreBites::MouseButtonEvent& evt);
	virtual bool mouseRelease(const OgreBites::MouseButtonEvent& evt);
	virtual bool mouseMoved(const OgreBites::MouseMotionEvent& evt);
	virtual bool mouseWheelRolled(const OgreBites::MouseWheelEvent& evt);

protected:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM; //No siempre necesario 
	
	//...
};