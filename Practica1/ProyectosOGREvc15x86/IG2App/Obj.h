#pragma once
#include <OGRE\Bites\OgreInput.h>
#include <OgreEntity.h>

#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
class Obj: public OgreBites::InputListener
{
public:
	Obj(Ogre::SceneNode* node);
	~Obj() { delete mNode_; };

	Ogre::SceneNode* getNode() { return mNode_; };

	// Métodos de InputListener que pueden redefinirse
	virtual void frameRendered(const Ogre::FrameEvent& evt) {};
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) { return false; };
	virtual bool keyReleased(const OgreBites::KeyboardEvent& evt) { return false; };
	virtual bool mousePressed(const OgreBites::MouseButtonEvent& evt) { return false; };
	virtual bool mouseRelease(const OgreBites::MouseButtonEvent& evt) { return false; };
	virtual bool mouseMoved(const OgreBites::MouseMotionEvent& evt) { return false; };
	virtual bool mouseWheelRolled(const OgreBites::MouseWheelEvent& evt) { return false; };

protected:
	Ogre::SceneNode* mNode_;
	Ogre::SceneManager* mSM; //No siempre necesario 
};