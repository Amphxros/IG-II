#include "Obj.h"

Obj::Obj(Ogre::SceneNode* node): mNode_(node)
{
	 mSM = mNode_->getCreator();
}
