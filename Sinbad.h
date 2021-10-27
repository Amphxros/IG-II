#pragma once
#include "Obj.h"
#include <OGRE\OgreAnimationState.h>

class Sinbad : public EntidadIG
{
public:
    Sinbad(Ogre::SceneNode* mNode);
    virtual ~Sinbad() {};
    virtual void frameRendered(const Ogre::FrameEvent& evt);
protected:
    Ogre::Entity* entity;
    Ogre::AnimationState* animationStateBottom;
    Ogre::AnimationState* animationStateTop;
};