#include "EntidadIG.h"

// Inicialización del vector de listeners
std::vector<EntidadIG*> EntidadIG::appListeners = std::vector<EntidadIG*>(0, nullptr);

EntidadIG::EntidadIG(Ogre::SceneNode * mNode): mNode_(mNode) {
	mSM = mNode_->getCreator();
}

EntidadIG::~EntidadIG() {
}

void EntidadIG::sendEvent(EntidadIG* entidad) {
	for (EntidadIG* e : appListeners) e->receiveEvent(this);
}