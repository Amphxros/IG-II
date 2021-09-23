#pragma once
#include "Obj.h"

#include <OgreEntity.h>
class Aspa : public Obj
{
public:
	Aspa(Ogre::SceneNode* m, double largo, double ancho, double prof);

protected:
	double largo_, ancho_, prof_;
	Ogre::SceneNode* tabNode;
	Ogre::SceneNode* adornoNode;
};

