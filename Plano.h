#pragma once
#include "Obj.h"

#include <OgreMeshManager.h>
class Plano :
    public EntidadIG
{
public:
    Plano(Ogre::SceneNode* mNode);
    virtual ~Plano() {}

    void createMesh();

};

