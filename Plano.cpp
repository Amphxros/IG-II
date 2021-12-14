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
	/*
	Ogre::SceneNode* espejoNode = mNode_->createChildSceneNode();
	Ogre::MovablePlane* mpRef = new Ogre::MovablePlane(Ogre::Vector3::UNIT_Z, 20);
	espejoNode->attachObject(mpRef);

	Ogre::TexturePtr rttRef = Ogre::TextureManager::getSingleton().createManual(
		"rttReflejo" + material, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::TEX_TYPE_2D,
		(Ogre::Real)(cam->getViewport()->getActualWidth()), // ejemplo
		(Ogre::Real)(cam->getViewport()->getActualHeight()), // ejemplo
		0, Ogre::PF_R8G8B8, Ogre::TU_RENDERTARGET);

	cam->enableReflection(mpRef);
	cam->enableCustomNearClipPlane(mpRef);

	Ogre::RenderTexture* renderTexture = rttRef->getBuffer()->getRenderTarget();
	Ogre::Viewport* vpt = renderTexture->addViewport(cam);
	vpt->setClearEveryFrame(true);
	vpt->setBackgroundColour(Ogre::ColourValue::Black);

	Ogre::TextureUnitState* tu = mPlano->getSubEntity(0)->getMaterial()->getTechnique(0)->getPass(0)->createTextureUnitState("rttReflejo");
	tu->setColourOperation(Ogre::LBO_MODULATE); // (i) hay otros modos
	tu->setTextureAdressingMode(Ogre::TextureUnitState::TAM_CLAMP);
	tu-> setProjectiveTexturing(true, cam);
	*/

	// añadir la nueva unidad de textura al material del reflejo-espejo
	//"..."
	//...
	//... //// sin esto no funciona: algo sobre la perspectiva

	//
	//// aqui se gira la cara perturbadora: pone la textura boca abajo en el pre render y lo restaura en el post render
	//...
	//...
}

/*
// añadir un puerto de vista al RenderTarget con la nueva cámara
RenderTexture* renderTexture = rttRef->getBuffer()->getRenderTarget();
Viviewport* vpt = renderTexture->addViewport(camRef);
vpt->setClearEveryFrame(true);
vpt->setBackgroundColour(ColourValue::Black);
*/