#include "Plano.h"
#include "Bomba.h"

Plano::Plano(Ogre::SceneNode* mNode, std::string mat): 
	EntidadIG(mNode), material(mat)
{
	this->addListener(this);
	createMesh();
	mPlano = mSM->createEntity("mPlane1080x800" + material);
	mPlano->setMaterialName(material);
	mNode_->attachObject(mPlano);

}

void Plano::createMesh()
{
	// definir mPlane1080x800
	Ogre::MeshManager::getSingleton().createPlane("mPlane1080x800" + material,
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::Plane(Ogre::Vector3::UNIT_Y, 0),
		1080, 800, 100, 80, true, 1, 1.0, 1.0, Ogre::Vector3::UNIT_Z);
}

void Plano::receiveEvent(EntidadIG* entidad)
{
	if (static_cast<Bomba*>(entidad) != nullptr) {
		changingMat = true;
		mTimer = new Ogre::Timer();
	}
}

void Plano::frameRendered(const Ogre::FrameEvent& evt)
{
	if (changingMat && mTimer->getMilliseconds()>=5000 && material=="RioAgua") {
		mPlano->setMaterialName("RioPiedras");
	}
}
