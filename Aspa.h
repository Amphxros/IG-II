#pragma once
//#include "EntidadIG.h"
#include "EntidadIG.h"

using namespace Ogre;

class Aspa : public EntidadIG
{
public: 
	Aspa(Ogre::SceneNode* mNode, double largo, double ancho, double prof, bool orn);
	virtual ~Aspa() {};
	Ogre::SceneNode* getAdornoNode() { return adornoNode; }
	Ogre::SceneNode* getTabNode() { return tabNode; }

protected:
	double largo_, ancho_, prof_;
	Ogre::SceneNode* adornoNode;
	Ogre::SceneNode* tabNode;
};