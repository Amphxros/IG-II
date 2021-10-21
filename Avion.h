#pragma once
#include "Obj.h"
#include "AspasMolino.h"
#include <OgreTimer.h>

class Avion : public EntidadIG
{
public:
    Avion(Ogre::SceneNode* mNode, float rd, float largo, int nAspas);
    virtual ~Avion();

    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
    virtual void frameRendered(const Ogre::FrameEvent& evt);
    void setRPressed() { r_pressed = !r_pressed; }
private:
    Ogre::SceneNode* cuerpoNode_; // esfera de la nave
    Ogre::SceneNode* frenteNode_; // cilindro de la parte delantera
    Ogre::SceneNode* pilotoNode_; // ninja
    Ogre::SceneNode* alaINode_; // ala izquierda (cubo escalado)
    Ogre::SceneNode* alaDNode_; // ala derecha (cubo escalado)
    Ogre::SceneNode* heliceINode_; // helice derecha (AspasMolino)
    Ogre::SceneNode* heliceDNode_; // helice derecha (AspasMolino)
    Ogre::SceneNode* luzNode_; // foco
    
    
    Ogre::Entity* alaA;     //entidad del  ala izq
    Ogre::Entity* alaB;     //entidad del ala der
    Ogre::Entity* body;     //entidad de la esfera central

    bool r_pressed = false;
    int numAspas_;


    Ogre::Timer* mTimerDespl_; // temporizador
    Ogre::Timer* mTimerParada_; // temporizador
    const int DELTA_DESPL = 1000 * 5;
    const int DELTA_PARADA = 500 * 1;
    bool estadoDeParada = false;


    AspasMolino* aspasI = nullptr;
    AspasMolino* aspasD = nullptr;
};