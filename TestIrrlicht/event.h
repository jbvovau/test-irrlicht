#pragma once

#include <irrlicht.h>

using namespace irr;

class EventReceiver : public irr::IEventReceiver {

public :
	//ISceneManager * scene;

	virtual bool OnEvent(const SEvent& event);

};