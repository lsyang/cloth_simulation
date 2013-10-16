#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <vector>
#include <vecmath.h>
#include "Spring.h"

using namespace std;

class ParticleSystem
{
public:

	ParticleSystem(int numParticles=0);

	int m_numParticles;

	
	// for a given state, evaluate derivative f(X,t)
	virtual vector<Vector3f> evalF(vector<Vector3f> state) = 0;
	
	// getter method for the system's state
	vector<Vector3f> getState(){ return m_vVecState; };

	//a list of particle indexes that each particle is attached to
	//vector<vector<int>> getSpring();
	//void setSpring(const vector<vector<int>>  & newSpring){m_springIndex=newSpring;};
	
	// setter method for the system's state
	void setState(const vector<Vector3f>  & newState) { m_vVecState = newState; };
	void addSpring(const Spring & newSpring){m_springs.push_back(newSpring);};
	vector<Spring> getSpring(){ return m_springs; };
	virtual void draw() = 0;
	
protected:

	vector<Vector3f> m_vVecState;
	vector<Spring> m_springs;
	
};

#endif
