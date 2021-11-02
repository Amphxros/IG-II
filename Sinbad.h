#pragma once
#include "EntidadIG.h"
#include <OGRE\OgreAnimationState.h>

const bool SHOW_ANIMS = 1;
const bool DANCE_AT_REST = 1;

class Sinbad : public EntidadIG
{
public:
    Sinbad(Ogre::SceneNode* mNode, bool Truco, int Altura); // orbita
    Sinbad(Ogre::SceneNode* mNode); // no orbita
    virtual ~Sinbad() {};
    
    virtual void frameRendered(const Ogre::FrameEvent& evt);
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
protected:
    Ogre::Entity* entity;
    Ogre::Entity* rightSword;
    Ogre::Entity* leftSword;
    Ogre::AnimationState* animationStateBottom;
    Ogre::AnimationState* animationStateTop;
    Ogre::AnimationState* animationStateDancing;

    Ogre::Timer* mTimer_; // temporizador
    const int DELTA_DESPL = 5000;
    const int DELTA_PARADA = 3000;
    bool estadoDeParada = false;

    void generaSinbad();

    void arma();
    void arma(bool rH);
    void cambiaEspada();
    bool rightHandOccupied;
    bool leftHandOccupied;

    void cPressed();
    bool c_pressed;

    const bool TRUCO = -1;
    const int ALTURA = -1;
};