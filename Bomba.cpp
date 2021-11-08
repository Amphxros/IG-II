#include "Bomba.h"

Bomba::Bomba(Ogre::SceneNode* mNode, std::string mat) : EntidadIG(mNode) {
    addListener(this);
    Ogre::Entity* ent = mSM->createEntity("Barrel.mesh");
    mNode_->setScale(20,20,20);
    ent->setMaterialName(mat);
    mNode_->attachObject(ent);

    // animación
    animation = mSM->createAnimation("BombaFlota", animDuration);
    track = animation->createNodeTrack(0);
    track->setAssociatedNode(mNode_);
    Ogre::Real durPaso = animDuration / 4.0; // 4 pasos intermedios de la misma duración
    
    //animaciones
    Ogre::TransformKeyFrame* kf; // 5 keyFrames: origen(0), arriba, origen, abajo, origen(4)
    kf = track->createNodeKeyFrame(durPaso * 0);
    kf->setTranslate(Ogre::Vector3(-100.0, 0.0, 100.0)); // Origen
    kf->setScale({ 30, 30, 30 });
    kf = track->createNodeKeyFrame(durPaso * 1);
    kf->setTranslate(Ogre::Vector3(-100.0, 10.0, 100.0)); // Arriba
    kf->setScale({ 30, 30, 30 });
    kf = track->createNodeKeyFrame(durPaso * 2);
    kf->setTranslate(Ogre::Vector3(-100.0, 0.0, 100.0)); // Origen
    kf->setScale({ 30, 30, 30 });
    kf = track->createNodeKeyFrame(durPaso * 3);
    kf->setTranslate(Ogre::Vector3(-100.0, -10.0, 100.0)); // Abajo
    kf->setScale({ 30, 30, 30 });
    kf = track->createNodeKeyFrame(durPaso * 4);
    kf->setTranslate(Ogre::Vector3(-100.0, 0.0, 100.0)); // Origen
    kf->setScale({ 30, 30, 30 });

    animationState = mSM->createAnimationState("BombaFlota");
    animationState->setLoop(true);
    animationState->setEnabled(true);
}

void Bomba::frameRendered(const Ogre::FrameEvent& evt)
{
    if (!hasExploted) {
        animationState->addTime(evt.timeSinceLastFrame);
    }
}

void Bomba::receiveEvent(EntidadIG* entidad)
{
    if (static_cast<Bomba*>(entidad) != nullptr) {
        mNode_->setPosition(Ogre::Vector3(0, 0, 0)); //para resetearla a su posicion de origen
        explode();
    }
}

