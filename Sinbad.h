#pragma once
#include "EntidadIG.h"
#include <OGRE\OgreAnimationState.h>

class Sinbad : public EntidadIG
{
public:
    Sinbad(Ogre::SceneNode* mNode);
    virtual ~Sinbad() {};
    
    virtual void frameRendered(const Ogre::FrameEvent& evt);
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
protected:
    Ogre::Entity* entity;
    Ogre::AnimationState* animationStateBottom;
    Ogre::AnimationState* animationStateTop;
    Ogre::AnimationState* animationStateDancing;

    bool c_pressed;

    const bool TRUCO = -1;
    const int ALTURA = -1;
};