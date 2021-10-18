#include "Obj.h"

// Inicialización del vector de listeners
std::vector<OgreEntity*> OgreEntity::appListeners = std::vector<OgreEntity*>(0, nullptr);

OgreEntity::OgreEntity(Ogre::SceneNode * mNode): mNode_(mNode) {
	mSM = mNode_->getCreator();
}

OgreEntity::~OgreEntity() {
}

void OgreEntity::sendEvent(OgreEntity* entidad) {
	for (OgreEntity* e : appListeners)
		e->receiveEvent(this);
}