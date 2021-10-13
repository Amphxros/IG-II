#include "EntidadIG.h"

// Inicialización del vector de listeners
std::vector<EntidadIG*> EntidadIG::appListeners = std::vector<EntidadIG*>(0, nullptr);

EntidadIG::EntidadIG(SceneNode *nodo, ...) {
	mNode = nodo;
	mSM = mNode->getCreator();
}

EntidadIG::~EntidadIG() {
	//...
}

EntidadIG::EntidadIG(Ogre::SceneNode* mNode): mNode_(mNode)
{
	mSM = mNode_->getCreator();
}


