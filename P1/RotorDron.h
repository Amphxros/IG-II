#pragma once
#include "Obj.h"
#include "AspasMolino.h"
class RotorDron :
    public Obj
{
public:
    RotorDron(Ogre::SceneNode* mNode,double rd, int numAspas, int largoAspas);
    virtual ~RotorDron();

    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
    void setOrientacion(int ori) { mAspas_->setOrientacion(ori); };
protected:
    Ogre::SceneNode* mAspasNode_;
    AspasMolino* mAspas_;
};