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
    Ogre::SceneNode* mContainer_;
    Ogre::SceneNode* mLuzNode_; // foco
    std::vector<BrazoDron*> mBrazos_;

    Ogre::Timer* mTimerDespl_; // temporizador 1
    Ogre::Timer* mTimerParada_; // temporizador 2
    const int DELTA_DESPL = 2000;
    const int DELTA_PARADA = 500;
    bool estadoDeParada = false;

    int numBrazos_;
    int numAspas_;
};