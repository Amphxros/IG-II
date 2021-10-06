#pragma once
#include "Obj.h"
#include "RotorDron.h"
class BrazoDron :
    public Obj
{
public:
    BrazoDron(Ogre::SceneNode* mNode, int largo, int rd, int numAspas);
    virtual ~BrazoDron();

    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
    void setOrientacion(int ori) { mRotor_->setOrientacion(ori); };
private:
    Ogre::SceneNode* mCilinder;
    Ogre::SceneNode* mMotor_;

    RotorDron* mRotor_;
};

