
#include "simpleSystem.h"

using namespace std;

SimpleSystem::SimpleSystem()
{
	vector<Vector3f> state;
	state.push_back(Vector3f(1,1,2));

	//m_vVecState.push_back(Vector3f(0));
	setState(state);
}

// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> SimpleSystem::evalF(vector<Vector3f> state)
{
	vector<Vector3f> f;
	f.push_back(Vector3f(-1*state[0][1],state[0][0],0));

	return f;
}

// render the system (ie draw the particles)
void SimpleSystem::draw()
{
		Vector3f pos=getState()[0] ;//YOUR PARTICLE POSITION
	    glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2] );
		glutSolidSphere(0.075f,10.0f,10.0f);
		glPopMatrix();
}
