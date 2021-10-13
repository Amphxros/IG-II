#include "Obj.h"

// Inicialización del vector de listeners
std::vector<Obj*> Obj::appListeners = std::vector<Obj*>(0, nullptr);

Obj::Obj(Ogre::SceneNode * mNode): mNode_(mNode) {
	mSM = mNode_->getCreator();
}

Obj::~Obj() {
}

void Obj::sendEvent(Obj* entidad) {
	for (Obj* e : appListeners)
		e->receiveEvent(this);
}