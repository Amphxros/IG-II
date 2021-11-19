#pragma once
#include "EntidadIG.h"
#include <OgreAnimation.h>
#include <OgreAnimationTrack.h>
#include <OgreKeyFrame.h>
#include <OGRE\OgreAnimationState.h>
#include "OgreFrameListener.h"
#include <OgreTimer.h>

class Bomba : public EntidadIG
{
public:
    Bomba(Ogre::SceneNode* mNode, std::string mat);
    virtual ~Bomba() {
        delete mTimer_;
    };

    virtual void frameRendered(const Ogre::FrameEvent& evt);
    virtual void receiveEvent(EntidadIG* entidad);
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
protected:

    Ogre::SceneNode* particleSystemNode_;
    Ogre::ParticleSystem* particleSys_;
    Ogre::Timer* mTimer_;

    Ogre::Animation* animation;
    Ogre::NodeAnimationTrack* track;
    Ogre::Real animDuration = 6;
    Ogre::AnimationState* animationState;
    
    bool stopped = false;
    void stop();

    bool exploted = false;
    void explode();

};