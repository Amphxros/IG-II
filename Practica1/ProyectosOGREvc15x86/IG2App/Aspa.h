#pragma once
#include "Obj.h"
class Aspa :
	public Obj
{
public: 
	Aspa(Ogre::SceneNode* mNode, double largo, double ancho, double prof, bool orn);
	virtual ~Aspa() {};
	Ogre::SceneNode* getAdornoNode() { return adornoNode; }

protected:
	double largo_, ancho_, prof_;
	Ogre::SceneNode* adornoNode;
	Ogre::SceneNode* tabNode;
};

