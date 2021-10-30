#pragma once
#include "EntidadIG.h"
#include <OgreMeshManager.h>

class Plano : public EntidadIG
{
public:
    Plano(Ogre::SceneNode* mNode);
    virtual ~Plano() {}

    void createMesh();

};

