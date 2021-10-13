#pragma once

#include <OGRE\Bites\OgreInput.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

class EntidadIG : public OgreBites::InputListener {
public:
	//Constructora y destructora
	EntidadIG(Ogre::SceneNode* mNode);
	virtual ~EntidadIG();
	//Vector est�tico de listeners
	static std::vector<EntidadIG*> appListeners;
	
	//A�adir entidad como listener al vector con push_back()
	static void addListener(EntidadIG* entidad) {
		appListeners.push_back(entidad);
	};

	virtual void frameRendered(const Ogre::FrameEvent& evt) {}; // implementar en clases que lo requieran

	/*
	En la definici�n del m�todo se puede usar el tiempo transcurrido desde el �ltimo frame renderizado para obtener efectos:
		Ogre::Real time = evt.timeSinceLastFrame;
	
	Por ejemplo, giros o desplazamientos en los que el espacio desplazado o el �ngulo girado es funci�n de este tiempo transcurrido:
		Ogre::Real time = evt.timeSinceLastFrame;
		distance = 80 * time;
		mNode->translate(distance, 0, distance, Ogre::Node::TS_LOCAL);
	*/

protected:
	Ogre::SceneNode* mNode_;
	Ogre::SceneManager* mSM;
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) { return false; };
};