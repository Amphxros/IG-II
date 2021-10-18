#pragma once
#include "Obj.h"
#include "BrazoDron.h"
#include <vector>
#include <OgreTimer.h>

class Dron : public OgreEntity
{
public:
    Dron(Ogre::SceneNode* mNode, int numBrazos, int numAspas, int rd);
    virtual ~Dron();

    virtual void frameRendered(const Ogre::FrameEvent& evt);
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
private:
    Ogre::Timer* mTimer;

    Ogre::SceneNode* mContainer_;
    std::vector<BrazoDron*> mBrazos_;

    int numBrazos_;
    int numAspas_;
};