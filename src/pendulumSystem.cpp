
#include "pendulumSystem.h"
#include "Spring.h"

PendulumSystem::PendulumSystem(int numParticles):ParticleSystem(numParticles)
{
	m_numParticles = numParticles;
	vector<Vector3f> state;

	// fill in code for initializing the state based on the number of particles
	for (int i = 0; i < m_numParticles; i++) {
		state.push_back(Vector3f(0.01*i,0,0));
		state.push_back(Vector3f(0));
		// for this system, we care about the position and the velocity
	}
	for (int i = 0; i < m_numParticles-1; i++) {
		Spring spring1;
		spring1.ind1=i;
		spring1.ind2=i+1;
		addSpring(spring1);
	}
	setState(state);

}


// TODO: implement evalF
// for a given state, evaluate f(X,t)
vector<Vector3f> PendulumSystem::evalF(vector<Vector3f> state)
{
	vector<Vector3f> f;
	f.push_back(Vector3f(0));
	f.push_back(Vector3f(0)); //fix one end
	vector<Vector3f> springForce;
	for(int i=0; i<m_numParticles; i++){
		springForce.push_back(Vector3f(0)); //initalize the forces to 0
	}
	vector<Spring> springs=getSpring();
	for(int i=0; i<springs.size(); i++){
		int ind1=springs[i].ind1;
		int ind2=springs[i].ind2;
		float k=springs[i].stiffness;
		float r=springs[i].restLength;

		Vector3f x1=state[ind1*2];
		Vector3f x2=state[ind2*2];
		Vector3f d1=x2-x1;
		Vector3f d2=x1-x2;

		springForce[ind2]=springForce[ind2]+Vector3f(-1*k*(d1.abs()-r)*1/d1.abs()*d1);
		springForce[ind1]=springForce[ind1]+Vector3f(-1*k*(d2.abs()-r)*1/d2.abs()*d2);
	}

	for (int i=2; i<state.size()-1; i=i+2){
		f.push_back(state[i+1]);
		float mass=0.3;
		Vector3f gravity=Vector3f(0,-9.8*mass,0);

		float drag=0.3; //0.5
		Vector3f drafForce=-1*drag*state[i+1];

		// Vector3f x0=state[i-2];
		// float k=5;
		// Vector3f d=state[i]-x0;
		// float r=0.5;

		// Vector3f spring=Vector3f(-1*k*(d.abs()-r)*1/d.abs()*d);

		f.push_back(1/mass*(gravity+drafForce+springForce[i/2]));


	}

	return f;
}

// render the system (ie draw the particles)
void PendulumSystem::draw()
{
	for (int i = 0; i < m_numParticles; i++) {
		vector<Vector3f> state=getState();

		Vector3f pos =state[i*2];//  position of particle i. YOUR CODE HERE
		drawSpring(0);
		glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2] );
		glutSolidSphere(0.075f,10.0f,10.0f);
		glPopMatrix();
	}
}

void PendulumSystem::drawSpring(int index)
{
	GLfloat thickness=5.0;
	vector<Spring> springs=getSpring();
	for(int i=0; i<springs.size(); i++){
		if(springs[i].ind1==index||springs[i].ind2==index){
				Vector3f state0=getState()[springs[i].ind1*2];
				Vector3f state1=getState()[springs[i].ind2*2];
				glLineWidth(thickness);
				glBegin(GL_LINES);
			    glVertex3f(state0[0],state0[1],state0[2]);
			    glVertex3f(state1[0],state1[1],state1[2]);
				glEnd();

		}
	}



	// Vector3f state0=getState()[i*2-2];
	// Vector3f state1=getState()[i*2];
	// glLineWidth(thickness);

	// glBegin(GL_LINES);
	// //glColor3f(1.0f,0.0,0.0);

 //    glVertex3f(state0[0],state0[1],state0[2]);
 //    glVertex3f(state1[0],state1[1],state1[2]);
	// glEnd();
}
