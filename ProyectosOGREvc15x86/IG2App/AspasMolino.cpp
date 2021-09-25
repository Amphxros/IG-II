#include "AspasMolino.h"

AspasMolino::AspasMolino(Ogre::SceneNode* mNode, int numAspas): Obj(mNode,"")
{
	mAspas_ = std::vector<Aspa*>(numAspas);

	Ogre::SceneNode* mContainer = mSM->createSceneNode();

	float angle = 90.0f;
	for (int i = 0; i < numAspas; i++) {
		//float x = Ogre::Math::Cos(Ogre::Degree(angle));
		//float z = Ogre::Math::Sin(Ogre::Degree(angle));

		Aspa* a = new Aspa(mContainer, 10, 10, 2);
		//a->getNode()->setPosition(Ogre::Vector3(10 * x, 0, 10 * z));
		
		a->getNode()->roll(Ogre::Degree(angle));
		mAspas_[i] = a;

		angle += 360.0f / numAspas;
	}

}
