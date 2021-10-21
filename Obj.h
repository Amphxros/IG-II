#pragma once

#include <OGRE\Bites\OgreInput.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <vector>

class EntidadIG: public OgreBites::InputListener {
public:
	//Constructora y destructora
	EntidadIG(Ogre::SceneNode* mNode);
	virtual ~EntidadIG();

	Ogre::SceneNode* getNode() { return mNode_; };

	// Vector estático de listeners
	static std::vector<EntidadIG*> appListeners;

	// Añadir entidad como listener al vector con push_back()
	static void addListener(EntidadIG* entidad) { appListeners.push_back(entidad); };

	// Métodos de InputListener que pueden redefinirse
	virtual void frameRendered(const Ogre::FrameEvent& evt) {  }; // implementar en clases que lo requieran
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) { return false; };
	virtual bool keyReleased(const OgreBites::KeyboardEvent& evt) { return false; };
	virtual bool mousePressed(const OgreBites::MouseButtonEvent& evt) { return false; };
	virtual bool mouseRelease(const OgreBites::MouseButtonEvent& evt) { return false; };
	virtual bool mouseMoved(const OgreBites::MouseMotionEvent& evt) { return false; };
	virtual bool mouseWheelRolled(const OgreBites::MouseWheelEvent& evt) { return false; };
	
	//En la definición del método frameRendered se puede usar el tiempo transcurrido desde el último frame renderizado para obtener efectos:
		////Ogre::Real time = evt.timeSinceLastFrame;
	
	//Por ejemplo, giros o desplazamientos en los que el espacio desplazado o el ángulo girado es función de este tiempo transcurrido:
		////Ogre::Real time = evt.timeSinceLastFrame;
		////distance = 80 * time;
		////mNode->translate(distance, 0, distance, Ogre::Node::TS_LOCAL);

	// mensajes
	void sendEvent(EntidadIG* entidad);
	virtual void receiveEvent(EntidadIG* entidad) {};

protected:
	Ogre::SceneNode* mNode_;
	Ogre::SceneManager* mSM; //No siempre necesario
};