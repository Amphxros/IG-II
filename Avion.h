#pragma once
#include "Obj.h"
#include "AspasMolino.h"

class Avion : public OgreEntity
{
public:
    Avion(Ogre::SceneNode* mNode, float rd, float largo, int nAspas);
    virtual ~Avion();

    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
private:
    Ogre::SceneNode* cuerpoNode_; // esfera de la nave
    Ogre::SceneNode* frenteNode_; // cilindro de la parte delantera
    Ogre::SceneNode* pilotoNode_; // ninja
    Ogre::SceneNode* alaINode_; // ala izquierda (cubo escalado)
    Ogre::SceneNode* alaDNode_; // ala derecha (cubo escalado)
    Ogre::SceneNode* heliceINode_; // helice derecha (AspasMolino)
    Ogre::SceneNode* heliceDNode_; // helice derecha (AspasMolino)

    int numAspas_;

    AspasMolino* aspasI = nullptr;
    AspasMolino* aspasD = nullptr;
};