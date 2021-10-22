#pragma once
#include "Obj.h"
#include "BrazoDron.h"
#include <vector>
#include <OgreTimer.h>

class Dron : public EntidadIG
{
public:
    Dron(Ogre::SceneNode* mNode, int numBrazos, int numAspas, int rd, bool mini);
    virtual ~Dron();

    virtual void frameRendered(const Ogre::FrameEvent& evt);
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
    void setRPressed() { r_pressed = !r_pressed; }

private:
    Ogre::SceneNode* mContainer_;
    Ogre::SceneNode* mLuzNode_; // foco
    std::vector<BrazoDron*> mBrazos_;

    Ogre::Timer* mTimer_; // temporizador
    const int DELTA_DESPL = 2000;
    const int DELTA_PARADA = 500;
    bool estadoDeParada = false;

    bool r_pressed = false;

    int numBrazos_;
    int numAspas_;
};