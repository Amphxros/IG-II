#pragma once
#include "EntidadIG.h"
#include "AspasMolino.h"
#include <OgreTimer.h>

const bool OBAMA_SPH = 0;

class Avion : public EntidadIG
{
public:
    Avion(Ogre::SceneNode* mNode, float rd, float largo, int nAspas, bool Truco, int Altura, bool ate);
    virtual ~Avion();

    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
    virtual void frameRendered(const Ogre::FrameEvent& evt);
    void setRPressed();
private:

    void explode();

    Ogre::SceneNode* cuerpoNode_; // esfera de la nave
    Ogre::SceneNode* frenteNode_; // cilindro de la parte delantera
    Ogre::SceneNode* pilotoNode_; // ninja
    Ogre::SceneNode* alaINode_; // ala izquierda (cubo escalado)
    Ogre::SceneNode* alaDNode_; // ala derecha (cubo escalado)
    Ogre::SceneNode* heliceINode_; // helice derecha (AspasMolino)
    Ogre::SceneNode* heliceDNode_; // helice derecha (AspasMolino)
    Ogre::SceneNode* luzNode_; // foco
    Ogre::SceneNode* pointsNode_;
    Ogre::SceneNode* particleTrailNode_;
    Ogre::SceneNode* explosionNode_;
    Ogre::SceneNode* particleExplosionNode_;
    Ogre::Entity* alaA;     //entidad del  ala izq
    Ogre::Entity* alaB;     //entidad del ala der
    Ogre::Entity* body;     //entidad de la esfera central

    Ogre::ParticleSystem* particleTrailSys_;
    Ogre::ParticleSystem* particleExplosionSys_;

    bool r_pressed = false;
    int numAspas_;

    Ogre::Timer* mTimer_; // temporizador
    const int DELTA_DESPL = 1000 * 5;
    const int DELTA_PARADA = 500 * 1;
    bool estadoDeParada = false;

    AspasMolino* aspasI = nullptr;
    AspasMolino* aspasD = nullptr;

    // E2 mov. autónomo
    const bool TRUCO = -1;
    const int ALTURA = -1;

    // E3 mov. en torno a bomba y violación del tratado de Ginebra
    bool atentado;
};