/*
 * Basics of Computer Graphics Exercise
 */
 
#include "assignment.h"
using namespace std;


// add your team members names and matrikel numbers here:
void printStudents()
{
	cout << "Julian Arnold,  293370" << endl;
	cout << "Marius Lipka,   334336" << endl;
	cout << "Florian George, 234236" << endl;
	cout << "Houman Biglari, 279942" << endl;
}

void drawScene(int scene, float runTime) {
  
	drawScaledCircle(0.9,0.9,glm::vec3(0.0f,0.0f,1.0f));
	drawScaledCircle(0.89,0.89,glm::vec3(0.2f,0.2f,0.2f));
	drawScaledCircle(0.7,0.7,glm::vec3(0.0f,0.0f,1.0f));
	drawScaledCircle(0.69,0.69,glm::vec3(0.0f,0.0f,0.0f));
	drawScaledTranslatedCircle(0.02,0.8,-0.95,0,glm::vec3(0.4f,0.4f,0.4f));

	for (int i = 0; i < 9; i++)
	{
		drawScaledTranslatedCircle(0.006,0.03,(-0.874f+((float)i/50.0f)),0,glm::vec3(1.0f,1.0f,1.0f));
	}

	for(int i=0;i<360;i+=10)
	{
		drawTranslatedScaledRotatedCircle(0.008,0.04,(-0.795f),0,(float)i,glm::vec3(1.0f,1.0f,1.0f));
	}
	
	drawTranslatedScaledRotatedCircle(0.01,0.06,(-0.85f),0,fmodf(((float)-runTime*12),360),glm::vec3(0.0f,1.0f,0.0f));

	drawTranslatedScaledRotatedCircle(0.01,0.06,(-0.75f),0,fmodf(((float)-runTime*6),360),glm::vec3(1.0f,1.0f,0.0f));


}

void initCustomResources()
{
}

void deleteCustomResources()
{
}

void drawScaledCircle(float scaleX,float scaleY,glm::vec3 color)
{
	drawCircle( color, glm::mat4(scaleX,0.0f,0.0f,0.0f,0.0f,scaleY,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f) );

}
void drawScaledTranslatedCircle(float scaleX,float scaleY,float transX, float transY,glm::vec3 color)
{

	// 
	drawCircle( color,  ( glm::mat4(1.0f,0.0f,0.0f,0.0f,  0.0f,1.0f,0.0f,0.0f,   0.0f,0.0f,1.0f,0.0f,   transX,transY,0.0f,1.0f) * glm::mat4(scaleX,0.0f,0.0f,0.0f,0.0f,scaleY,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f)  ) ); 

}

void drawTranslatedScaledRotatedCircle(float scaleX,float scaleY,float transX, float transY,float rot,glm::vec3 color)
{

	// 
	drawCircle( color, (glm::mat4(cos((rot/360.0f)*2*M_PI),sin((rot/360.0f)*2*M_PI),0.0f,0.0f,-sin((rot/360.0f)*2*M_PI),cos((rot/360.0f)*2*M_PI),0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f) * glm::mat4(1.0f,0.0f,0.0f,0.0f,  0.0f,1.0f,0.0f,0.0f,   0.0f,0.0f,1.0f,0.0f,   transX,transY,0.0f,1.0f) * glm::mat4(scaleX,0.0f,0.0f,0.0f,0.0f,scaleY,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f) ) ); 

}
