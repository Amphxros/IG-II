#pragma once
#include "EntidadIG.h"
#include "RotorDron.h"
class BrazoDron : public EntidadIG
{
public:
    BrazoDron(Ogre::SceneNode* mNode, int largo, int rd, int numAspas, bool grueso);
    virtual ~BrazoDron();

    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
    void setOrientacion(int ori) { mRotor_->setOrientacion(ori); };
    virtual void receiveEvent(EntidadIG* entidad);
private:
    Ogre::SceneNode* mCilinder_;
    Ogre::SceneNode* mMotor_;

    RotorDron* mRotor_;
};

