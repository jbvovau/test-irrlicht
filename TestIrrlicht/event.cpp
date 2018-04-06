#include "event.h"

using namespace irr;

using namespace scene;
using namespace video;

bool EventReceiver::OnEvent(const SEvent& event) {

	if (event.EventType == irr::EEVENT_TYPE::EET_KEY_INPUT_EVENT) {

		if (this->scene) {
			ISceneNode* recube =  this->scene->addCubeSceneNode(1, 0, 0, irr::core::vector3df(0, 1 , 0));
			recube->setMaterialFlag(E_MATERIAL_FLAG::EMF_LIGHTING, false);
			recube->setMaterialTexture(0,this->scene->getVideoDriver()->getTexture("Img/mur.png"));
		}



		return false;
	}

	return false;
}



void EventReceiver::setSceneManager(irr::scene::ISceneManager*  smgr) {
	this->scene = smgr;
}