#pragma once
#include "Obj.h"
#include "BrazoDron.h"
#include <vector>

class Dron : public Obj
{
public:
    Dron(Ogre::SceneNode* mNode, int numBrazos, int numAspas, int rd);
    virtual ~Dron();

    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
private:
    Ogre::SceneNode* mContainer_;
    std::vector<BrazoDron*> mBrazos_;
    int numBrazos_;
    int numAspas_;
};