#pragma once
#include "EntidadIG.h"
#include <OgreAnimation.h>
#include <OgreAnimationTrack.h>
#include <OgreKeyFrame.h>
#include <OGRE\OgreAnimationState.h>

const bool SHOW_ANIMS = 1;
const bool DANCE_AT_REST = 1;

class Sinbad : public EntidadIG
{
public:
    // camina en el río
    Sinbad(Ogre::SceneNode* mNode, bool cam);
    // orbita
    Sinbad(Ogre::SceneNode* mNode, bool Truco, float Altura);
    // no orbita ni camina
    Sinbad(Ogre::SceneNode* mNode);

    virtual ~Sinbad() {};
    
    virtual void frameRendered(const Ogre::FrameEvent& evt);
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
    virtual void receiveEvent(EntidadIG* entidad);
protected:
    Ogre::Entity* entity;
    Ogre::Entity* rightSword;
    Ogre::Entity* leftSword;
    Ogre::AnimationState* animationStateRunBottom;
    Ogre::AnimationState* animationStateRunTop;
    Ogre::AnimationState* animationStateDancing;
    Ogre::AnimationState* animationStateDeadBottom;
    Ogre::AnimationState* animationStateDeadTop;

    // carrera en el río
    Ogre::Animation* mvAnimation;
    Ogre::NodeAnimationTrack* mvTrack;
    Ogre::Real mvAnimDuration = 12;
    Ogre::AnimationState* mvAnimationState;
    void configMvAnim();
    bool caminanteRio;

    Ogre::Timer* mTimer_; // temporizador de movimiento
    const int DELTA_DESPL = 5000;
    const int DELTA_PARADA = 3000;
    bool estadoDeParada = false;

    void generaSinbad();

    void arma();
    void arma(bool rH);
    void cambiaEspada();
    bool rightHandOccupied;
    bool leftHandOccupied;
    void desarma();

    Ogre::Timer* mBombTimer_; // temporizador de activación de bomba del río
    const int DELTA_BOMB = 5000;
    void die();
    bool dead;

    void cPressed();
    bool c_pressed;

    const bool TRUCO = -1;
    const float ALTURA = -1;
};