#include "Obj.h"

// La constructora pasa el nodo asociado al objeto creado, como par�metro
Obj::Obj(Ogre::SceneNode* node) {
	mNode = node;
	Ogre::SceneManager* mSM = mNode->getCreator();
}
