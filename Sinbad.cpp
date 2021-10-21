#include "Sinbad.h"

Sinbad::Sinbad(Ogre::SceneNode* mNode): EntidadIG(mNode)
{
	Ogre::Entity* e= mSM->createEntity("Sinbad.mesh");
	mNode_->attachObject(e);
}
