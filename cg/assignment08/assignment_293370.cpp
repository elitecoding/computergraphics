/*
 * Basics of Computer Graphics Exercise
 */

#include "Tools/ABReader.hpp"
#include "Tools/PNGReader.hpp"
#include "Tools/TextureData.hpp"
#include "Tools/HelperFunctions.hpp"

#include "assignment.h"
using namespace std;

extern glm::mat4 g_ProjectionMatrix;

VertexArrayObject* g_vaoKilleroo;
ArrayBuffer*       g_abKilleroo;

ShaderProgram* shaderA; // you might need more than one program
ShaderProgram* shaderB;

GLuint tex;
GLuint tex2;
GLuint tex3;

// add your team members names and matrikel numbers here:
void printStudents() {
    cout << "Student Name 0, matrikel number 0" << endl;
    cout << "Student Name 1, matrikel number 1" << endl;
    cout << "Student Name 2, matrikel number 2" << endl;
    cout << "Student Name 3, matrikel number 3" << endl;
}

void drawScene(int scene, float runTime) {

    // Create model-view matrix
    glm::mat4 viewMatrix   = g_camera.getViewMatrix();
    glm::mat4 modelMatrix  = glm::scale( glm::vec3(1.5f) );
	
	if (scene == 1) {
		// ignore the color space and use a RGB texture for the diffuse and ambient material
		// the specular material should be white (set as a constant in the fragment shader:
		glm::mat4 modelViewMatrix    = viewMatrix * modelMatrix;
    	glm::mat4 invTranspModelView = glm::inverse(glm::transpose(modelViewMatrix));
		glDisable(GL_FRAMEBUFFER_SRGB);
		shaderA->use();
		shaderA->setUniform("uProjectionMatrix",          g_ProjectionMatrix );
    	shaderA->setUniform("uModelViewMatrix",           modelViewMatrix);
    	shaderA->setUniform("uInvTranspModelViewMatrix",  invTranspModelView);
		shaderA->setUniform("uLightPosition",             glm::vec3( modelViewMatrix*vLightPosition) );
		
		// todo: texturing
		shaderA->setUniform( "tex",    0);
		g_vaoKilleroo->render();
		
	} else if (scene == 2) {
		
		// use a sRGB texture for the diffuse and ambient material.
		// make sure the framebuffer is set to convert the linear content to sRGB!
		// the specular material should be white (set as a constant in the fragment shader:
		glm::mat4 modelViewMatrix    = viewMatrix * modelMatrix;
    	glm::mat4 invTranspModelView = glm::inverse(glm::transpose(modelViewMatrix));
		glEnable(GL_FRAMEBUFFER_SRGB);
		
		shaderA->use();
		shaderA->setUniform( "tex",    1);
		shaderA->setUniform("uProjectionMatrix",          g_ProjectionMatrix );
    	shaderA->setUniform("uModelViewMatrix",           modelViewMatrix);
    	shaderA->setUniform("uInvTranspModelViewMatrix",  invTranspModelView);
		shaderA->setUniform("uLightPosition",             glm::vec3( modelViewMatrix*vLightPosition) );
		
		// todo: texturing
		g_vaoKilleroo->render();
		
		
	} else if (scene == 3) {
		// use a sRGB texture for the diffuse and ambient material.
		// make sure the framebuffer is set to convert the linear content to sRGB!
		// the specular material should be read from a texture but should be gray scale (remember that this was defined in a linear space!)
		
		glm::mat4 modelViewMatrix    = viewMatrix * modelMatrix;
    	glm::mat4 invTranspModelView = glm::inverse(glm::transpose(modelViewMatrix));
		glEnable(GL_FRAMEBUFFER_SRGB);
		shaderB->use();
		shaderB->setUniform( "tex",    1);
		shaderB->setUniform( "tex2",    2);
		shaderB->setUniform("uProjectionMatrix",          g_ProjectionMatrix );
    	shaderB->setUniform("uModelViewMatrix",           modelViewMatrix);
    	shaderB->setUniform("uInvTranspModelViewMatrix",  invTranspModelView);
		shaderB->setUniform("uLightPosition",             glm::vec3( modelViewMatrix*vLightPosition) );
		
		// todo: texturing
		g_vaoKilleroo->render();
	}
}


void initCustomResources() {

    // Create your resources here, e.g. shaders, buffers,...

    ////////////////////////////////////////////////////////////////////////////
    // Shader:
    
    shaderA = new ShaderProgram("partA_293370.vsh", "partA_293370.fsh");
    if (!shaderA->link()) exit(0);
	shaderB = new ShaderProgram("partB_293370.vsh", "partB_293370.fsh");
    if (!shaderB->link()) exit(0);

    // Set uniforms that don't change:
    shaderA->use();
    shaderA->setUniform( "uLightColor",             vLightColor);
    shaderA->setUniform( "uSpecularityExponent",    fSpecularityExponent);
	shaderA->setUniform( "tex",    0);
	shaderB->use();
    shaderB->setUniform( "uLightColor",             vLightColor);
    shaderB->setUniform( "uSpecularityExponent",    fSpecularityExponent);
	shaderB->setUniform( "tex",    0);
	shaderB->setUniform( "tex2",    0);

    ////////////////////////////////////////////////////////////////////////////
    // Define geometry:

    ABReader abreader;
	g_abKilleroo  = abreader.readABFile("killeroo.ab");
    g_vaoKilleroo = new VertexArrayObject();
    g_vaoKilleroo->attachAllMatchingAttributes(g_abKilleroo, shaderA);

    ////////////////////////////////////////////////////////////////////////////
    // Read textures:
	
	glGenTextures(1, &tex);
	g_vaoKilleroo->bind();

	PNGReader pngReader;
	TextureData* textureData = pngReader.readPNGFile("killerooDiffuse.png");

	
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureData->getWidth(), textureData->getHeight(), 0, textureData->getFormat(), textureData->getType(), textureData->getData());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glGenTextures(1, &tex2);


	glBindTexture(GL_TEXTURE_2D, tex2);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, textureData->getWidth(), textureData->getHeight(), 0, textureData->getFormat(), textureData->getType(), textureData->getData());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	
	textureData = pngReader.readPNGFile("killerooSpecular.png");

	glGenTextures(1, &tex3);


	glBindTexture(GL_TEXTURE_2D, tex3);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, textureData->getWidth(), textureData->getHeight(), 0, textureData->getFormat(), textureData->getType(), textureData->getData());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glActiveTexture(GL_TEXTURE0+1);
	glBindTexture(GL_TEXTURE_2D, tex2);
	glActiveTexture(GL_TEXTURE0+2);
	glBindTexture(GL_TEXTURE_2D, tex3);

	glEnable(GL_DEPTH_TEST);
}

void deleteCustomResources() {

    // Don't forget to delete your OpenGL resources (shaders, buffers, etc.)!

    delete shaderA;
    delete g_vaoKilleroo;
    delete g_abKilleroo;
}

