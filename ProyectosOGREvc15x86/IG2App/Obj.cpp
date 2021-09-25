#include "Obj.h"

Obj::Obj(Ogre::SceneNode* node, std::string s): mNode_(node), id(s)
{
	 mSM = mNode_->getCreator();
}
