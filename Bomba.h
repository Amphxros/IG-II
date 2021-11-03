#pragma once
#include "EntidadIG.h"
#include <OgreAnimation.h>
#include <OgreAnimationTrack.h>
#include <OgreKeyFrame.h>

class Bomba : public EntidadIG
{
    public:
        Bomba(Ogre::SceneNode* mNode, std::string mat);
        virtual ~Bomba() {};
    protected:
        Ogre::Animation* animation;
        Ogre::NodeAnimationTrack* track;
        float animDuration = 6;
};