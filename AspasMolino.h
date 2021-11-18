#pragma once
#include "EntidadIG.h"
#include "Aspa.h"

class AspasMolino : public EntidadIG
{
public:
	AspasMolino(Ogre::SceneNode* mNode, int numAspas, double largo, bool orn, int ori);
	virtual ~AspasMolino();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	void setOrientacion(int ori){ orientacion_ = ori ; };
	virtual void receiveEvent(EntidadIG* entidad);
	void rotaAspas();

	void eraseAll() {
	
		mContainer->detachAllObjects();
		mCenter->detachAllObjects();

		for (int i = 0; i < numAspas_; i++) {
			mAspas_vec[i]->getAdornoNode()->detachAllObjects();
			mAspas_vec[i]->getTabNode()->detachAllObjects();
			
			vec[i]->detachAllObjects();
		}
	}
public:
	Ogre::SceneNode* mContainer;
	Ogre::SceneNode* mCenter;
	
	std::vector<Aspa*> mAspas_vec;
	std::vector<Ogre::SceneNode*> vec;
	int numAspas_;
	int orientacion_;
};