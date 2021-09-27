#pragma once
#include "Obj.h"
class Aspa :
	public Obj
{
public: 
	Aspa(Ogre::SceneNode* mNode, double largo, double ancho, double prof, bool orn);
	virtual ~Aspa() {};

protected:
	double largo_, ancho_, prof_;
};

