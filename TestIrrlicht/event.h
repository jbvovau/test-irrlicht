#pragma once

#include <irrlicht.h>

using namespace irr;

class EventReceiver : public irr::IEventReceiver {

public :
	//
	virtual bool OnEvent(const SEvent& event);

	void setSceneManager(irr::scene::ISceneManager* smgr);


private:
	irr::scene::ISceneManager * scene;

};