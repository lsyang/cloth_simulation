#ifndef SPRING_H
#define SPRING_H

#include <vector>
#include <vecmath.h>

using namespace std;

struct Spring
{
	int ind1=0;
	int ind2=0;
	float restLength=0.5;
	float stiffness=10;

};

#endif