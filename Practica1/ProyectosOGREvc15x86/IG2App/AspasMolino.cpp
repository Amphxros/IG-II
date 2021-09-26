#include "AspasMolino.h"

AspasMolino::AspasMolino(Ogre::SceneNode* mNode, int numAspas): Obj(mNode)
{
	mAspas_ = std::vector<Aspa*>(numAspas);

	Ogre::SceneNode* mContainer = mNode_->createChildSceneNode();
	Ogre::SceneNode* mCenter = mNode_->createChildSceneNode();

	float angle = 90.0f;
	for (int i = 0; i < numAspas; i++) {
		//float x = Ogre::Math::Cos(Ogre::Degree(angle));
		//float z = Ogre::Math::Sin(Ogre::Degree(angle));

		Aspa* a = new Aspa(mContainer->createChildSceneNode(), 2, 20, 0.5);
		//a->getNode()->setPosition(Ogre::Vector3(10 * x, 0, 10 * z));
	
		a->getNode()->roll(Ogre::Degree(angle));
		mAspas_[i] = a;

		angle += 360.0f / numAspas;
	}

	Ogre::Entity* centro = mSM->createEntity("sphere.mesh");
	mCenter->setScale(0.6, 0.6, 0.6);
	mCenter->attachObject(centro);


}

AspasMolino::~AspasMolino()
{
	for (int i = 0; i < mAspas_.size(); i++) {
		delete mAspas_[i];
	}
	
}
