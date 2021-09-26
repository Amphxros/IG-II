#pragma once
#include "Obj.h"
class Aspa :
	public Obj
{
public: 
	Aspa(Ogre::SceneNode* mNode, double largo, double ancho, double prof);
	virtual ~Aspa() {};

protected:
	double largo_, ancho_, prof_;
};

