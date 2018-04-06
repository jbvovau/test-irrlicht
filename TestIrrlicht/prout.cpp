#include "prout.h"
#include <irrlicht.h>



void glurb(int a) {
	a = a + 1;
}

void blorb(const int& a) {
	int b = a;
	b++;
}


void zjd(int & a) {
	int b = a;

	int c = a;

	a++;

	b++;
}

void zlip(int* a) {
	//*a++;

	int b = *a;

	b++;

	(*a)++;
}

Prout::Prout() {
	this->nombre = 44;
}


int Prout::getTrenteDeux() {
	return 32;
}


int Prout::getNimp() {

	int a = 36;

	int *b;

	b = &a;

	this->nombre = *b;

	return this->nombre;
}

void Prout::nimp() {

	int a = 12;

	glurb(a);
	blorb(a);
	zlip(&a);
	zjd(a);

	a++;

}