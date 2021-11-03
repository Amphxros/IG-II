#include "Bomba.h"

Bomba::Bomba(Ogre::SceneNode* mNode, std::string mat) : EntidadIG(mNode) {
    Ogre::Entity* ent = mSM->createEntity("Barrel.mesh");
    mNode_->setScale(20,20,20);
    ent->setMaterialName(mat);
    mNode_->attachObject(ent);

    // animación
    animation = mSM->createAnimation("BombaFlota", animDuration);
    track = animation->createNodeTrack(0);
    track->setAssociatedNode(mNode);
    Ogre::Real durPaso = animDuration / 2.0; // 4 pasos intermedios (5 fotogramas) de la misma duración
    
    Ogre::TransformKeyFrame* kf; // 5 keyFrames: origen(0), arriba, origen, abajo, origen(4)
    kf = track->createNodeKeyFrame(durPaso * 0);
    kf->setTranslate(Ogre::Vector3(-10.0, 0.0, 100.0)); // Origen
    kf = track->createNodeKeyFrame(durPaso * 1);
    kf->setTranslate(Ogre::Vector3(-10.0, 100.0, 100.0)); // Arriba
    //...

    Ogre::AnimationState* animationState = mSM->createAnimationState("BombaFlota");
    animationState->setLoop(true);
    animationState->setEnabled(true);
}