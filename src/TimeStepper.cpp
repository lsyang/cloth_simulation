#include "TimeStepper.h"

///TODO: implement Explicit Euler time integrator here
void ForwardEuler::takeStep(ParticleSystem* particleSystem, float stepSize)
{
	vector<Vector3f> currentState=particleSystem->getState();
	vector<Vector3f> derivative=particleSystem->evalF(currentState);

	vector<Vector3f> newState;
	for (int i=0; i<derivative.size(); i++) {
		newState.push_back(currentState[i]+stepSize*derivative[i]);
  	}
  	//printf("%zi",newState.size());

	particleSystem->setState(newState);

}

///TODO: implement Trapzoidal rule here
void Trapzoidal::takeStep(ParticleSystem* particleSystem, float stepSize)
{
	vector<Vector3f> currentState=particleSystem->getState();
	vector<Vector3f> f0=particleSystem->evalF(currentState);
	vector<Vector3f> middleState;
	for (int i=0; i<currentState.size(); i++) {
		middleState.push_back(currentState[i]+stepSize*f0[i]);
  	}
	vector<Vector3f> f1=particleSystem->evalF(middleState);
	vector<Vector3f> newState;
	for (int i=0; i<currentState.size(); i++) {
		newState.push_back(currentState[i]+stepSize/2*(f0[i]+f1[i]));
  	}
  	//printf("%zi",newState.size());
	particleSystem->setState(newState);

}
