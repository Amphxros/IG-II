#pragma once
#include "Obj.h"
#include "BrazoDron.h"
#include <vector>
#include <OgreTimer.h>

class Dron : public EntidadIG
{
public:
    // E2 mov. autónomo
    Dron(Ogre::SceneNode* mNode, int numBrazos, int numAspas, int rd, bool perturbador, bool Truco, int Altura);
    // normal
    Dron(Ogre::SceneNode* mNode, int numBrazos, int numAspas, int rd, bool perturbador);
    virtual ~Dron();

    virtual void frameRendered(const Ogre::FrameEvent& evt);
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
    void setRPressed();

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
    int rd_;
    bool perturbador_;

    Ogre::Entity* cuerpoDron_ = nullptr;

    void generaDron();

    // E2 mov. autónomo
    const bool TRUCO = -1;
    const int ALTURA = -1;
};