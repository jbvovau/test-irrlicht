
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
			dimension2d<u32>(1920, 1080), //windowSize: Size of the Window or screen in FullScreenMode to be created. In this example we use 640x480.
			32, //bits: Amount of color bits per pixel.This should be 16 or 32. The parameter is often ignored when running in windowed mode.
			true,	//fullscreen: Specifies if we want the device to run in fullscreen mode or not.
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

	//skybox
	ISceneNode * skybox = smgr->addSkyBoxSceneNode(
		driver->getTexture("Img/hw_lagoon/lagoon_up.tga"),	//top
		driver->getTexture("Img/hw_lagoon/lagoon_dn.tga") ,	//bottom
		//
		driver->getTexture("Img/hw_lagoon/lagoon_rt.tga") ,//left ok
		driver->getTexture("Img/hw_lagoon/lagoon_lf.tga") ,//right
		
		driver->getTexture("Img/hw_lagoon/lagoon_ft.tga"), // front ok
		driver->getTexture("Img/hw_lagoon/lagoon_bk.tga") //back 
		
	);


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
	camera->setNearValue(0.1f);
	camera->setPosition(vector3df(4, 0, 0));

	//fog
	driver->setFog(SColor(128, 32, 32,32), E_FOG_TYPE::EFT_FOG_LINEAR, 80.f, 300.0f, 0.05f, false);

	//texture wall
	ITexture* textureMur = driver->getTexture("Img/mur.png");
	ITexture* textureSol = driver->getTexture("Img/dry.png");

	//test scene irrlicht
	//bool loaded = smgr->loadScene("scene.irr");

	auto p = new Prout();
	s32 v = p->getTrenteDeux();
	s32 a = p->getNimp();
	p->nimp();

	ISceneCollisionManager* collManager = smgr->getSceneCollisionManager();

	//light
	smgr->setAmbientLight(SColor(255, 255, 255, 255));
	driver->setAmbientLight(SColor(255, 100, 255, 255));

	//test obj
	IAnimatedMesh* meshBlob = smgr->getMesh("Map/blob2.obj");
	ISceneNode * complix = smgr->addMeshSceneNode(meshBlob);
	complix->setPosition(vector3df(0, 0, 0));
	complix->setMaterialFlag(E_MATERIAL_FLAG::EMF_LIGHTING, true);
	complix->setMaterialFlag(E_MATERIAL_FLAG::EMF_FOG_ENABLE, true);
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

          

	bool alive = true;

	while (device->run() && alive) {
		//tmp
		driver->beginScene(true, true, SColor(255, 100, 101, 140));
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();

		if (camera->getPosition().Y < -300.f) {
			alive = false;
		}

	}

	device->drop();

	return 0;
}