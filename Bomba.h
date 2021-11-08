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
    virtual void receiveEvent(EntidadIG* entidad);
protected:
    Ogre::Animation* animation;
    Ogre::NodeAnimationTrack* track;
    Ogre::Real animDuration = 6;
    Ogre::AnimationState* animationState;
    bool hasExploted = false;
    inline void explode() { hasExploted = true;  } //proximamente habra que cambiar esto por un generador y explotar de verdad
};