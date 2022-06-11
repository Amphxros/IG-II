#include "Plano.h"
#include "Bomba.h"

#include <OgreMovablePlane.h>
#include <OgreRenderTargetListener.h>

#include <OgreRenderTexture.h>
#include <OgreTextureManager.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreSubEntity.h>
#include <OgreTechnique.h>

#include <OgreCamera.h>
#include <OgreViewport.h>

Plano::Plano(Ogre::SceneNode* mNode, std::string mat): 
	EntidadIG(mNode), material(mat)
{
	createMesh();
	mPlano = mSM->createEntity("mPlane1080x800" + material);
	mPlano->setMaterialName(material);
	mNode_->attachObject(mPlano);

	mTimer = new Ogre::Timer();
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
	if (dynamic_cast<Bomba*>(entidad) != nullptr) {
		changingMat = true;
		mTimer->reset();
	}
}

void Plano::frameRendered(const Ogre::FrameEvent& evt)
{
	if (changingMat && mTimer->getMilliseconds()>=DELTA) {
		mPlano->setMaterialName("RioPiedras");
		changingMat = false;
	}
}

void Plano::setReflejo(Ogre::Camera* cam) {
	//creamos un plano 
	Ogre::MeshManager::getSingleton().createPlane("reflejo",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::Plane(Ogre::Vector3::UNIT_Y, 0),
		1080, 800, 100, 80, true, 1, 1.0, 1.0, Ogre::Vector3::UNIT_Z);

	//cargamos la malla y iniciamos el nodo
	Ogre::Entity* mRef_ = mSM->createEntity("reflejo");
	Ogre::SceneNode* mRefNode = mNode_->createChildSceneNode();
	mRef_->setMaterialName(material);
	mRefNode->attachObject(mRef_);

	//creamos el plano del reflejo
	Ogre::MovablePlane* mpRef = new Ogre::MovablePlane(Ogre::Vector3::UNIT_Y, 0);
	mRefNode->attachObject(mpRef);
	cam->enableReflection(mpRef);
	cam->enableCustomNearClipPlane(mpRef);

	//creamos la textura
	Ogre::TexturePtr rttRef = Ogre::TextureManager::getSingleton().createManual(
		"rttReflejo" + material,
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::TEX_TYPE_2D,
		1080,
		800,
		0,
		Ogre::PF_R8G8B8,
		Ogre::TU_RENDERTARGET
	);
	Ogre::RenderTexture* mRenderTexture_ = rttRef->getBuffer()->getRenderTarget();
	Ogre::Viewport* vp = mRenderTexture_->addViewport(cam);
	vp->setClearEveryFrame(true);
	vp->setBackgroundColour(Ogre::ColourValue::Black);

	//asignamos la textura
	Ogre::TextureUnitState* mTU_ = mRef_->
		getSubEntity(0)->
		getMaterial()->
		getTechnique(0)->
		getPass(0)->createTextureUnitState("rttReflejo" + material);
	mTU_->setColourOperation(Ogre::LBO_ADD); // puede ser LBO_MODULATE, LBO_REPLACE o LBO_ALPHA_BLEND tambien
	mTU_->setTextureAddressingMode(Ogre::TextureUnitState::TAM_CLAMP);
	mTU_->setProjectiveTexturing(true, cam);
}

void Plano::setEspejo(Ogre::Camera* cam)
{
	//creamos un plano 
	Ogre::MeshManager::getSingleton().createPlane("espejo" + material,
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::Plane(Ogre::Vector3::UNIT_Y, 0),
		1080, 800, 100, 80, true, 1, 1.0, 1.0, Ogre::Vector3::UNIT_Z);

	//cargamos la malla y iniciamos el nodo
	Ogre::Entity* mMirror_ = mSM->createEntity("espejo" + material);
	Ogre::SceneNode* mMirrorNode = mNode_->createChildSceneNode();
	mMirror_->setMaterialName(material);
	mMirrorNode->attachObject(mMirror_);

	//creamos el plano espejo
	Ogre::MovablePlane* mpRef = new Ogre::MovablePlane(Ogre::Vector3::UNIT_Y, 0);
	mMirrorNode->attachObject(mpRef);

	cam->enableReflection(mpRef);
	cam->enableCustomNearClipPlane(mpRef);

	//creamos la textura
	Ogre::TexturePtr rttRef = Ogre::TextureManager::getSingleton().createManual(
		"rttRef" + material,	//nombre unico por eso el + material
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::TEX_TYPE_2D,
		1080,
		800,
		0,
		Ogre::PF_R8G8B8,
		Ogre::TU_RENDERTARGET);

	Ogre::RenderTexture* mRenderTexture_ = rttRef->getBuffer()->getRenderTarget();
	Ogre::Viewport* vp = mRenderTexture_->addViewport(cam);
	vp->setClearEveryFrame(true);
	vp->setBackgroundColour(Ogre::ColourValue::Black);

	//asignamos la textura
	Ogre::TextureUnitState* mTU_ = mMirror_->
		getSubEntity(0)->
		getMaterial()->
		getTechnique(0)->
		getPass(0)->createTextureUnitState("rttRef" + material); //nombre igual al rttRef
	mTU_->setColourOperation(Ogre::LBO_ADD); // puede ser LBO_MODULATE, LBO_REPLACE o LBO_ALPHA_BLEND tambien
	mTU_->setTextureAddressingMode(Ogre::TextureUnitState::TAM_CLAMP);
	mTU_->setProjectiveTexturing(true, cam);
}