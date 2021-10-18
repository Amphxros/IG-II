#pragma once
#include "Obj.h"
#include "RotorDron.h"
class BrazoDron :
    public OgreEntity
{
public:
    BrazoDron(Ogre::SceneNode* mNode, int largo, int rd, int numAspas, bool grueso);
    virtual ~BrazoDron();

    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
    void setOrientacion(int ori) { mRotor_->setOrientacion(ori); };
private:
    Ogre::SceneNode* mCilinder;
    Ogre::SceneNode* mMotor_;

    RotorDron* mRotor_;
};

