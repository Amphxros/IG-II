#pragma once
#include "EntidadIG.h"
#include <OgreAnimation.h>
#include <OgreAnimationTrack.h>
#include <OgreKeyFrame.h>
#include <OGRE\OgreAnimationState.h>
#include "OgreFrameListener.h"

class Bomba : public EntidadIG
{
public:
    Bomba(Ogre::SceneNode* mNode, std::string mat);
    virtual ~Bomba() {};

    virtual void frameRendered(const Ogre::FrameEvent& evt);

protected:
    Ogre::Animation* animation;
    Ogre::NodeAnimationTrack* track;
    Ogre::Real animDuration = 6;
    Ogre::AnimationState* animationState;
};