#include "event.h"


bool EventReceiver::OnEvent(const SEvent& event) {

	int a = 15;

	a = a * 32;

	a = a - 2;


	return false;
}