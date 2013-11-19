/*
 * Basics of Computer Graphics Exercise
 */
 
#include "assignment.h"
using namespace std;

extern int g_numberOfBunnyVertices;
extern int g_bunnyStrideSize;
extern float g_bunnyMesh[];
extern int g_bunnyColorStrideSize;
extern unsigned char g_bunnyColor[];

// add your team members names and matrikel numbers here:
void printStudents()
{
	cout << "Julian Arnold, 293370" << endl;
	cout << "Student Name 1, matrikel number 1" << endl;
	cout << "Student Name 2, matrikel number 2" << endl;
	cout << "Student Name 3, matrikel number 3" << endl;
}

glm::mat4 g_ModelViewMatrix;
glm::mat4 g_ProjectionMatrix;

glm::mat4 buildFrustum( float phiInDegree, float aspectRatio, float nearin, float farin) {

    float phiHalfInRadians = 0.5f*phiInDegree * (M_PI/180.0f);
    float t = nearin * tan( phiHalfInRadians );
    float b = -t;
    float left = b*aspectRatio;
    float right = t*aspectRatio;

	return glm::frustum( left, right, b, t, nearin, farin );
}

void resizeCallback( int newWidth, int newHeight )
{
	// define the part of the screen OpenGL should draw to (in pixels):
    glViewport( 0, 0, newWidth, newHeight );
    g_ProjectionMatrix = buildFrustum(90.0f, (newWidth/(float)newHeight), 0.1f, 100.0f);
}


// ==============================================
// Global varibles for binding the vbo
// ==============================================
GLuint bunny_vbo;
GLuint bunny_color_vbo;

// ==============================================
// Global varibles for the shaders.
// ==============================================
GLuint vs_a, fs_a, prog_a;
GLuint vs_b, fs_b, prog_b;
GLuint vs_c, fs_c, prog_c;

void drawScene(int scene, float runTime) {
	
	// glm::lookAt needs the eye position, the center to look at and the up vector, so it works a bit different 
	// than our lookAt from last week:
	glm::vec3 pos = glm::vec3(1.5f*cos(runTime), 0.0f, 1.5f*sin(runTime) );
	g_ModelViewMatrix = glm::lookAt( pos, glm::vec3(0,0,0), glm::vec3(0,1,0) );
	glm::mat4 modelMatrix = glm::translate( 0.0f, 0.0f, 0.35f );
	g_ModelViewMatrix = g_ModelViewMatrix * modelMatrix;
	
	if (scene == 1) {

        // ====================================================================
        // assignment part a
        // Add your code here:
        // ====================================================================

		glUseProgram(prog_a);

		glDrawArrays( GL_TRIANGLES, 0, g_numberOfBunnyVertices );

        // ====================================================================
        // End Exercise code
        // ====================================================================

	} else if (scene == 2) {
		
        // ====================================================================
        // assignment part b
        // Add your code here:
        // ====================================================================

		glUseProgram(prog_b);

		GLint uniformLocation = glGetUniformLocation( prog_b, "uModelViewMatrix" );
		glUniformMatrix4fv( uniformLocation,1,false, (const GLfloat*)&g_ModelViewMatrix);
		GLint uniformLocation2 = glGetUniformLocation( prog_b, "uProjectionMatrix" );
		glUniformMatrix4fv( uniformLocation2,1,false, (const GLfloat*)&g_ProjectionMatrix);
	
		glDrawArrays( GL_TRIANGLES, 0, g_numberOfBunnyVertices );

        // ====================================================================
        // End Exercise code
        // ====================================================================


	} else if (scene == 3) {
		
        // ====================================================================
        // assignment part c
        // Add your code here:
        // ====================================================================

		glUseProgram(prog_c);

		GLint uniformLocation = glGetUniformLocation( prog_c, "uModelViewMatrix" );
		glUniformMatrix4fv( uniformLocation,1,false, (const GLfloat*)&g_ModelViewMatrix);
		GLint uniformLocation2 = glGetUniformLocation( prog_c, "uProjectionMatrix" );
		glUniformMatrix4fv( uniformLocation2,1,false, (const GLfloat*)&g_ProjectionMatrix);
	
		glDrawArrays( GL_TRIANGLES, 0, g_numberOfBunnyVertices );

        // ====================================================================
        // End Exercise code
        // ====================================================================
	}
}

void createShaderProgram( GLuint &vs, GLuint &fs, GLuint &prog, const std::string &vsFileName, const std::string &fsFileName ) {

    // =========================================================================
    // create your shaders here
    //
    // Input are the filenames of the vertex and the fragment shader.
    //
    // You have to return the handles of the vertex shader, fragment shader
    // and the final program.
    //
    // Code required for a,b,c
    //
    // Add your code here:
    // ====================================================================
	std::string vShaderProgramA = getFileContent(vsFileName);
	std::string fShaderProgramA = getFileContent(fsFileName);
	
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	vs = glCreateShader(GL_VERTEX_SHADER);
	prog = glCreateProgram();
	
	const GLchar* vs1String = vShaderProgramA.c_str();
	glShaderSource(vs,1,&vs1String,NULL);
	glCompileShader(vs);

	const GLchar* fs1String = fShaderProgramA.c_str();
	glShaderSource(fs,1,&fs1String,NULL);
	glCompileShader(fs);

	glAttachShader(prog,vs);
	glAttachShader(prog,fs);

	glBindAttribLocation( prog, 0, "aPosition" );
	glBindAttribLocation( prog, 1, "aNormal" );

	glBindAttribLocation( prog, 3, "aColor" );

	glLinkProgram(prog);


    // ====================================================================
    // End Exercise code
    // ====================================================================
}

void initCustomResources()
{

    // =========================================================================
    // create your ressources here, e.g. buffers,...
    //
    // Code required for a,b,c
    //
    // Add your code here:
    // ====================================================================
	glGenBuffers(1,&bunny_vbo);
	glBindBuffer(GL_ARRAY_BUFFER,bunny_vbo);
	glBufferData( GL_ARRAY_BUFFER,g_bunnyStrideSize*g_numberOfBunnyVertices,g_bunnyMesh,GL_STATIC_DRAW );

	

	glVertexAttribPointer( 0, 4, GL_FLOAT,GL_FALSE, g_bunnyStrideSize, 0 );
	glVertexAttribPointer( 1, 3, GL_FLOAT,GL_FALSE, g_bunnyStrideSize,(const GLvoid*)( 4*sizeof(float) ) );
	glVertexAttribPointer( 2, 2, GL_FLOAT,GL_FALSE, g_bunnyStrideSize, (const GLvoid*)( 7*sizeof(float) ) );
	
	glGenBuffers(1,&bunny_color_vbo);
	glBindBuffer(GL_ARRAY_BUFFER,bunny_color_vbo);
	glBufferData( GL_ARRAY_BUFFER,3*g_numberOfBunnyVertices , g_bunnyColor ,GL_STATIC_DRAW );


	glVertexAttribPointer( 3, 3, GL_UNSIGNED_BYTE ,GL_TRUE, g_bunnyColorStrideSize, 0); //(const GLvoid*)( 9*sizeof(float) ) 
	

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(3);
	
    // ====================================================================
    // End Exercise code
    // ====================================================================


	// create the shaders:
	createShaderProgram( vs_a, fs_a, prog_a, "shader_293370_a.vsh", "shader_293370_a.fsh" );

	printGLSLCompileLog(vs_a);
	printGLSLCompileLog(fs_a);
	printGLSLLinkLog(prog_a);

	createShaderProgram( vs_b, fs_b, prog_b, "shader_293370_b.vsh", "shader_293370_b.fsh" );
	
	printGLSLCompileLog(vs_b);
	printGLSLCompileLog(fs_b);
	printGLSLLinkLog(prog_b);
	
	createShaderProgram( vs_c, fs_c, prog_c, "shader_293370_c.vsh", "shader_293370_c.fsh" );

	printGLSLCompileLog(vs_c);
	printGLSLCompileLog(fs_c);
	printGLSLLinkLog(prog_c);
}

void deleteCustomResources()
{


    // ====================================================================
    // don't forget to delete your OpenGL ressources (shaders, buffers, etc.)!
    // Add your code here:
    // ====================================================================
	glDeleteBuffers(1,&bunny_vbo);
	glDeleteBuffers(1,&bunny_color_vbo);
	
	glDeleteShader(fs_a);
	glDeleteShader(vs_a);

	glDeleteShader(fs_b);
	glDeleteShader(vs_b);

	glDeleteShader(fs_c);
	glDeleteShader(vs_c);

	glDeleteProgram(prog_a);
    glDeleteProgram(prog_b);
	glDeleteProgram(prog_c);
	// ====================================================================
    // End Exercise code
    // ====================================================================
}

