#pragma once
#include "EntidadIG.h"
#include <OgreMeshManager.h>
#include <string>


class Plano : public EntidadIG
{
public:
    Plano(Ogre::SceneNode* mNode, std::string mat);
    virtual ~Plano() {}

    void createMesh();
    std::string material;
};

