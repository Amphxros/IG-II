#pragma once
#include "EntidadIG.h"
#include <OgreMeshManager.h>
#include <string>
#include <OgreTimer.h>
class Plano : public EntidadIG
{
public:
    Plano(Ogre::SceneNode* mNode, std::string mat);
    virtual ~Plano() {}

    void createMesh();
    void setMaterial(std::string mat) {
        createMesh();
        mPlano = mSM->createEntity("mPlane1080x800" + mat);
        mPlano->setMaterialName(mat);
    }

    virtual void receiveEvent(EntidadIG* entidad);
    virtual void frameRendered(const Ogre::FrameEvent& evt);
protected:
    Ogre::Entity* mPlano;
    std::string material;
    Ogre::Timer* mTimer;
    bool changingMat = false;
};

