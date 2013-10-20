/*
 * Basics of Computer Graphics Exercise
 */
 
#include "assignment.h"
using namespace std;

// add your team members names and matrikel numbers here:
void printStudents()
{
	cout << "Julian Arnold, 293370" << endl;
	cout << "Marius Lipka, 334336" << endl;
	cout << "Student Name 2, matrikel number 2" << endl;
	cout << "Student Name 3, matrikel number 3" << endl;
}

void drawScene( int scene, float runTime )
{
    
}

void initCustomResources()
{
	//
    // Print some general information about the supported OpenGL, the GPU vendor and sometimes the driver version:
    //
    cout << "OpenGL context version: " << glGetString(GL_VERSION)  << endl;
    cout << "OpenGL vendor:          " << glGetString(GL_VENDOR)   << endl;
    cout << "OpenGL renderer:        " << glGetString(GL_RENDERER) << endl;
    cout << "GLSL version:           " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

void deleteCustomResources()
{
}

