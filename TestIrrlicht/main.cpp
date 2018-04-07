
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
			video::EDT_DIRECT3D9,	//deviceType: Type of the device. This can currently be the Null-device, one of the two software renderers, D3D8, D3D9, or OpenGL. In this example we use EDT_SOFTWARE, but to try out, you might want to change it to EDT_BURNINGSVIDEO, EDT_NULL, EDT_DIRECT3D8, EDT_DIRECT3D9, or EDT_OPENGL.
			dimension2d<u32>(1900, 900), //windowSize: Size of the Window or screen in FullScreenMode to be created. In this example we use 640x480.
			32, //bits: Amount of color bits per pixel.This should be 16 or 32. The parameter is often ignored when running in windowed mode.
			false,	//fullscreen: Specifies if we want the device to run in fullscreen mode or not.
			false,	//stencilbuffer: Specifies if we want to use the stencil buffer (for drawing shadows).
			false,	//vsync : Specifies if we want to have vsync enabled, this is only useful in fullscreen mode.
			0);		//eventReceiver: An object to receive events. We do not want to use this parameter here, and set it to 0.

	if (!device)
		return 1;

	device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	//register scene manager
	receiver.setSceneManager(smgr);

	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
		rect<s32>(10, 10, 260, 22), true);

	IGUIButton* button = guienv->addButton(recti(10, 30, 50, 60), 0, 0, L"Test !!! Mdr");

	

	//
	SKeyMap keyMap[9];
	keyMap[0].Action = EKA_MOVE_FORWARD;
	keyMap[0].KeyCode = KEY_UP;
	keyMap[1].Action = EKA_MOVE_FORWARD;
	keyMap[1].KeyCode = KEY_KEY_Z;

	keyMap[2].Action = EKA_MOVE_BACKWARD;
	keyMap[2].KeyCode = KEY_DOWN;
	keyMap[3].Action = EKA_MOVE_BACKWARD;
	keyMap[3].KeyCode = KEY_KEY_S;

	keyMap[4].Action = EKA_STRAFE_LEFT;
	keyMap[4].KeyCode = KEY_LEFT;
	keyMap[5].Action = EKA_STRAFE_LEFT;
	keyMap[5].KeyCode = KEY_KEY_Q;

	keyMap[6].Action = EKA_STRAFE_RIGHT;
	keyMap[6].KeyCode = KEY_RIGHT;
	keyMap[7].Action = EKA_STRAFE_RIGHT;
	keyMap[7].KeyCode = KEY_KEY_D;

	//jump ?
	keyMap[8].Action = EKA_JUMP_UP;
	keyMap[8].KeyCode = KEY_SPACE;


	//add camera
	ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0, 
		70, //roateSpeed
		0.02f, //movespeed
		-1,	//id
		keyMap, //key map
		9,	//mapsize
		true, //noVerticalMovement ,
		0.03f, //jump speed
		false, //invert mouse
		true //make active
		
		);
	camera->setNearValue(0.1);
	camera->setPosition(vector3df(4, 0, 0));


	//texture wall
	ITexture* textureMur = driver->getTexture("Img/mur.png");
	ITexture* textureSol = driver->getTexture("Img/dry.png");



	//add a cube
	IMeshSceneNode* cube = smgr->addCubeSceneNode(1, 0, 0, vector3df(-16, 0, -16));
	cube->setMaterialFlag(E_MATERIAL_FLAG::EMF_LIGHTING, false);
	cube->setMaterialTexture(0, textureMur);

	IMeshSceneNode* cube2 = smgr->addCubeSceneNode(1, 0, 0, vector3df(16, 0, -16));
	cube2->setMaterialFlag(E_MATERIAL_FLAG::EMF_LIGHTING, false);
	cube2->setMaterialTexture(0, textureMur);

	IMeshSceneNode* cube3 = smgr->addCubeSceneNode(1, 0, 0, vector3df(16, 0, 16));
	cube3->setMaterialFlag(E_MATERIAL_FLAG::EMF_LIGHTING, false);
	cube3->setMaterialTexture(0, textureMur);

	IMeshSceneNode* cube4 = smgr->addCubeSceneNode(1, 0, 0, vector3df(-16, 0, 16));
	cube4->setMaterialFlag(E_MATERIAL_FLAG::EMF_LIGHTING, false);
	cube4->setMaterialTexture(0, textureMur);

	IMeshSceneNode* cube5 = smgr->addCubeSceneNode(1, 0, 0, vector3df(0, 0, 0));
	cube5->setMaterialFlag(E_MATERIAL_FLAG::EMF_LIGHTING, false);
	cube5->setMaterialTexture(0, textureMur);

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

	//test terrain
	/*
	ITerrainSceneNode* terrain = smgr->addTerrainSceneNode("Img/t64.png" ,	//map
		0,	//parent
		-1,	//id
		vector3df(-16,-2,-16),		//position
		vector3df(0, 0, 0),		//rotation
		vector3df(4.f, 1.f/2.f, 4.f),	//scale
		SColor(255, 255, 255, 255),
		5,
		ETPS_17,
		0	//smooth factor
	);
	terrain->scaleTexture(32.0f ,32.0f);
	terrain->setMaterialFlag(E_MATERIAL_FLAG::EMF_LIGHTING, false);
	terrain->setMaterialTexture(0, textureSol);
	
	terrain->setMaterialType(E_MATERIAL_TYPE::EMT_DETAIL_MAP); */

	//test obj
	IAnimatedMesh* meshBlob = smgr->getMesh("Map/blob.obj");
	ISceneNode * complix = smgr->addMeshSceneNode(meshBlob);
	complix->setPosition(vector3df(0, 0, 0));
	complix->setMaterialFlag(E_MATERIAL_FLAG::EMF_LIGHTING, false);
	//complix->setMaterialTexture(0, textureMur);
	//complix->setScale(vector3df(1, 1, 1) / 16);

	scene::IMeshSceneNode* q3node = 0;
	q3node = smgr->addOctreeSceneNode(meshBlob);
	ITriangleSelector* selector = smgr->createOctreeTriangleSelector(
		meshBlob, q3node, 128);
	q3node->setTriangleSelector(selector);

	scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(selector,
		camera,
		core::vector3df(1, 1, 1),	//size of body (camera)
		core::vector3df(0, -0.2f, 0),	//gravity
		core::vector3df(0, 1, 0)	//position
	);

	camera->addAnimator(anim);
	anim->drop();
	selector->drop();

	device->getCursorControl()->setVisible(false);


	while (device->run()) {
		//tmp
		driver->beginScene(true, true, SColor(255, 100, 101, 140));
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();
	}

	device->drop();

	return 0;
}