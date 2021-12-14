#include "Bomba.h"
#include <OGRE/OgreParticleSystem.h>
#include "Sinbad.h"
#include <SDL_keycode.h>

Bomba::Bomba(Ogre::SceneNode* mNode, std::string mat) : EntidadIG(mNode) {
    Ogre::Entity* ent = mSM->createEntity("uv_sphere.mesh");
    //mNode_->setScale(20, 20, 20);
    ent->setMaterialName(mat);
    mNode_->attachObject(ent);

    // animación
    animation = mSM->createAnimation("BombaFlota", animDuration);
    track = animation->createNodeTrack(0);
    track->setAssociatedNode(mNode_);
    Ogre::Real durPaso = animDuration / 4.0; // 4 pasos intermedios de la misma duración
    
    // fotogramas
    Ogre::Vector3 eje(0, 1, 0);
    float angulo = 0;
    Ogre::TransformKeyFrame* kf; // 5 keyFrames: origen(0), arriba, origen, abajo, origen(4)
    // Origen
    kf = track->createNodeKeyFrame(durPaso * 0);
    kf->setTranslate(Ogre::Vector3(-100.0, 0.0, 100.0));
    kf->setRotation(Ogre::Quaternion(Ogre::Degree(angulo), eje));
    //kf->setScale({ 20, 20, 20 });
    // Arriba
    kf = track->createNodeKeyFrame(durPaso * 1);
    kf->setTranslate(Ogre::Vector3(-100.0, 100.0, 100.0));
    angulo += (45/2);
    kf->setRotation(Ogre::Quaternion(Ogre::Degree(angulo), eje));
    //kf->setScale({ 20, 20, 20 });
    // Origen
    kf = track->createNodeKeyFrame(durPaso * 2);
    kf->setTranslate(Ogre::Vector3(-100.0, 0.0, 100.0));
    angulo -= (45 / 2);
    kf->setRotation(Ogre::Quaternion(Ogre::Degree(angulo), eje));
    //kf->setScale({ 20, 20, 20 });
    // Abajo
    kf = track->createNodeKeyFrame(durPaso * 3);
    kf->setTranslate(Ogre::Vector3(-100.0, -100.0, 100.0));
    angulo -= (45 / 2);
    kf->setRotation(Ogre::Quaternion(Ogre::Degree(angulo), eje));
    //kf->setScale({ 20, 20, 20 });
    // Origen
    kf = track->createNodeKeyFrame(durPaso * 4);
    kf->setTranslate(Ogre::Vector3(-100.0, 0.0, 100.0));
    angulo += (45 / 2);
    kf->setRotation(Ogre::Quaternion(Ogre::Degree(angulo), eje));
    //kf->setScale({ 20, 20, 20 });

    animationState = mSM->createAnimationState("BombaFlota");
    animationState->setLoop(true);
    animationState->setEnabled(true);
}

void Bomba::frameRendered(const Ogre::FrameEvent& evt)
{
    if (!stopped) {
        // la bomba "flota" en el río
        animationState->addTime(evt.timeSinceLastFrame);
    }
}

void Bomba::receiveEvent(EntidadIG* entidad)
{
    if (dynamic_cast<Sinbad*>(entidad) != nullptr) {
        explode();
    }
}

bool Bomba::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    switch (evt.keysym.sym)
    {
    case SDLK_t:
        stop();
        break;
    default:
        break;
    }

    return true;
}

void Bomba::stop()
{
    if (!stopped) {
        stopped = true;
        this->sendEvent(this);
    }
}

inline void Bomba::explode()
{
    if (!exploted) {
        mNode_->detachAllObjects(); 
        //mNode_->setPosition(0, 50, 0); ///TODO: poner a nivel del agua
        particleSystemNode_ = mNode_->createChildSceneNode();
        particleSys_ = mSM->createParticleSystem("explosionBomba", "IG2App/BombSmoke");
        particleSys_->setEmitting(true);
        particleSystemNode_->attachObject(particleSys_);
        this->sendEvent(this);
        exploted = true;
        stopped = true;
    }
}