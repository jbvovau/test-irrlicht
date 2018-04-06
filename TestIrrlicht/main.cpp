
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include <irrlicht.h>
#include "prout.h"
#include "event.h"

using namespace irr;


using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main() {
	//http://irrlicht.sourceforge.net/docu/example001.html

	EventReceiver receiver;

	IrrlichtDevice *device =
		createDevice(
			video::EDT_SOFTWARE,	//deviceType: Type of the device. This can currently be the Null-device, one of the two software renderers, D3D8, D3D9, or OpenGL. In this example we use EDT_SOFTWARE, but to try out, you might want to change it to EDT_BURNINGSVIDEO, EDT_NULL, EDT_DIRECT3D8, EDT_DIRECT3D9, or EDT_OPENGL.
			dimension2d<u32>(600, 480), //windowSize: Size of the Window or screen in FullScreenMode to be created. In this example we use 640x480.
			16, //bits: Amount of color bits per pixel.This should be 16 or 32. The parameter is often ignored when running in windowed mode.
			false,	//fullscreen: Specifies if we want the device to run in fullscreen mode or not.
			false,	//stencilbuffer: Specifies if we want to use the stencil buffer (for drawing shadows).
			false,	//vsync : Specifies if we want to have vsync enabled, this is only useful in fullscreen mode.
			&receiver);		//eventReceiver: An object to receive events. We do not want to use this parameter here, and set it to 0.

	if (!device)
		return 1;

	device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
		rect<s32>(10, 10, 260, 22), true);

	//add camera
	ICameraSceneNode* camera = smgr->addCameraSceneNode(0, vector3df(2, 1, 1), vector3df(0, 0, 0));
	camera->setNearValue(0.1);

	//texture wall
	ITexture* textureMur = driver->getTexture("Img/mur.png");
	ITexture* textureSol = driver->getTexture("Img/dry.png");

	//mesh ground
	IAnimatedMesh* meshSol = smgr->addHillPlaneMesh("sol", dimension2df(1, 1), dimension2du(32, 32), 0, 0, dimension2df(0, 0));
	IMeshSceneNode* sol = smgr->addMeshSceneNode(meshSol);
	sol->setPosition(vector3df(0, -0.5, 0));
	sol->setMaterialFlag(E_MATERIAL_FLAG::EMF_LIGHTING, false);
	sol->setMaterialTexture(0, textureSol);

	//add a cube
	IMeshSceneNode* cube = smgr->addCubeSceneNode(1, 0, 0, vector3df(0, 0, 0));
	cube->setMaterialFlag(E_MATERIAL_FLAG::EMF_LIGHTING, false);
	cube->setMaterialTexture(0, textureMur);

	//animator
	ISceneNodeAnimator* animator = smgr->createRotationAnimator(vector3df(0, 0.1f, 0));
	cube->addAnimator(animator);
	animator->drop();
	animator = 0;

	Prout* p = new Prout();
	int v = p->getTrenteDeux();
	int a = p->getNimp();
	p->nimp();

	ISceneCollisionManager* collManager = smgr->getSceneCollisionManager();

	float rotation = 0;

	while (device->run()) {
		//tmp
		camera->setTarget(vector3df(0, rotation, 0));
		driver->beginScene(true, true, SColor(255, 100, 101, 140));
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();
	}

	device->drop();

	return 0;
}