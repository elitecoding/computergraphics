/*
 * Basics of Computer Graphics Exercise
 */
 
#include "assignment.h"

extern int g_bunnyStrideSize;
extern float g_bunnyMesh[];
extern int g_bunnyColorStrideSize;
extern int g_numberOfBunnyVertices;
extern unsigned char g_bunnyColor[];

glm::mat4 g_VPMatrix;
glm::mat4 g_ModelViewMatrix;
glm::mat4 g_ProjectionMatrix;

int g_windowHeight = 512;
int g_windowWidth  = 512;

glm::vec3 g_eyePos = glm::vec3(0, 0, -2.3);
glm::vec3 g_viewDir;

using namespace std;

// add your team members names and matrikel numbers here:
void printStudents()
{
	cout << "Julian Arnold,  293370" << endl;
	cout << "Marius Lipka,   334336" << endl;
	cout << "Florian George, 234236" << endl;
	cout << "Houman Biglari, 279942" << endl;
}

// Implicit edge representation for one triangle edge.
// p1 and p2 define the edge.
// Evaluate the function at point.
// If the result is negative, you are inside the triangle edge otherwise outside
int evaluateF(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& point)
{

    // =========================================================================
    // Rasterization based on Pineda
    // Assignment section a
    // Add your code here:
    // ====================================================================
    
    // Calculate 2-dimensional cross product
    const int result = static_cast<int>((p2.x - p1.x)*(point.y - p1.y) - (p2.y - p1.y)*(point.x - p1.x));
    return result;

    // ====================================================================
    // End Exercise code
    // ====================================================================
}


// Rasterize one triangle
// the input points are given in counterclockwise order
void drawTriangle( const glm::vec4& p0_in, const glm::vec4& p1_in, const glm::vec4& p2_in, const glm::vec3& normal) {

    // We use a hardcoded color
    const glm::vec3 color = glm::vec3(0.6,0.6,0.6);

    // We work in 2D when rasterizing, ... so we switch to 2D vectors
    const glm::vec2 v0 = glm::vec2(p0_in[0],p0_in[1]);
    const glm::vec2 v1 = glm::vec2(p1_in[0],p1_in[1]);
    const glm::vec2 v2 = glm::vec2(p2_in[0],p2_in[1]);

    // rasterizer initialized from minX to maxX and minY to MaxY
    int minX = 0;
    int minY = 0;
    int maxX = g_windowWidth;
    int maxY = g_windowHeight;

    // Diffuse lighting coefficient
    float diffuse = 1.0;

    // =========================================================================
    // Rasterization based on Pineda. Restrict rasterization range to bounding box and screen
    // Assignment section b
    // Add your code here:
    // ====================================================================

    // Set min/max to opposite
    minX = g_windowWidth;
    minY = g_windowHeight;
    maxX = 0;
    maxY = 0;

    // Set min/max to min/max of triangle points
    minX = std::min(minX, static_cast<int>(v0.x));
    minX = std::min(minX, static_cast<int>(v1.x));
    minX = std::min(minX, static_cast<int>(v2.x));

    maxX = std::max(maxX, static_cast<int>(v0.x)+1);
    maxX = std::max(maxX, static_cast<int>(v1.x)+1);
    maxX = std::max(maxX, static_cast<int>(v2.x)+1);

    minY = std::min(minY, static_cast<int>(v0.y));
    minY = std::min(minY, static_cast<int>(v1.y));
    minY = std::min(minY, static_cast<int>(v2.y));

    maxY = std::max(maxY, static_cast<int>(v0.y)+1);
    maxY = std::max(maxY, static_cast<int>(v1.y)+1);
    maxY = std::max(maxY, static_cast<int>(v2.y)+1);

    // Clip to Screen
    minX = std::max(minX, 1);
    maxX = std::min(maxX, g_windowWidth  - 1);
    minY = std::max(minY, 1);
    maxY = std::min(maxY, g_windowHeight - 1);

    // ====================================================================
    // End Exercise code
    // ====================================================================



    // =========================================================================
    // Rasterization based on Pineda
    // Assignment section f
    // Add your code here:
    // ====================================================================

    const float dotproduct = glm::dot(g_viewDir, normal);
    if (dotproduct <= 0)
      return;
    
    diffuse = dotproduct;

    // ====================================================================
    // End Exercise code
    // ====================================================================


    // Rasterization
    glm::vec2 p;
    for (p[1] = minY; p[1] < maxY; p[1]++) {
        for (p[0] = minX; p[0] < maxX; p[0]++) {

            // =========================================================================
            // Draw current pixel?
            // Assignment section c
            // Add your code here:
            // ====================================================================

		// Use this function to draw the pixel
		// Do not modify it, just call it if you want to draw the pixel given by p
		
          if ( (evaluateF(v0, v1, p) >= 0) && (evaluateF(v1, v2, p) >= 0) && (evaluateF(v2, v0, p) >= 0) )
                setPixel(p[0],p[1],  diffuse * color );


            // ====================================================================
            // End Exercise code
            // ====================================================================

        }
    }

    // ====================================================================
    // End Exercise code
    // ====================================================================

}

glm::mat4 buildFrustum(float phiInDegree, float aspectRatio, float near, float far) {

    float phiHalfInRadians = 0.5f * phiInDegree * (M_PI / 180.0f);
    float t = near * tan(phiHalfInRadians);
    float b = -t;
    float left = b * aspectRatio;
    float right = t * aspectRatio;

    return glm::frustum(left, right, b, t, near, far);
}

void drawScene(int _scene, float _runTime) {

     g_viewDir = glm::normalize(glm::vec3(0, 0, 0) - g_eyePos);

    // =========================================================================
    // Clear Screen by using the setPixel Function
    // Assignment section e
    // Add your code here:
    // ====================================================================

    const int minX = 0;
    const int minY = 0;
    const int maxX = g_windowWidth;
    const int maxY = g_windowHeight;
    
    for (int x = minX; x < maxX; x++)
    {
      for (int y = minY; y < maxY; y++)
      {
        setPixel(x, y, glm::vec3(0, 0, 0));
      }
    }

    // ====================================================================
    // End Exercise code
    // ====================================================================


    // Viewport transformation
    g_VPMatrix = glm::scale( glm::mat4(), glm::vec3(g_windowWidth/2.0, g_windowHeight/2.0,1.0) ) *  glm::translate( glm::mat4(), glm::vec3(1.0,1.0,0.0)  ) ;

    // Create modelview matrix
    // First: Create transformation into eye-space
    // glm::lookAt needs the eye position, the center to look at and the up vector
    g_ModelViewMatrix = glm::lookAt(g_eyePos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    // Create a projection matrix
    g_ProjectionMatrix = buildFrustum(70.0f, (g_windowWidth / (float) g_windowHeight), 0.1f, 100.0f);

	// one vertex consists of 9 floats:
    g_bunnyStrideSize = 9;

    if ( (_scene == 2) || (_scene == 3) ) {

        // =========================================================================
        // Let the bunny rotate around y-Axis
        // Assignment section d
        // Add your code here:
        // ====================================================================

        const float angle = -2.0f*M_PI*_runTime/10.0f;

        glm::mat4 r;
        r[0][0] =  cos(angle);
        r[2][0] =  sin(angle);
        r[1][1] = 1.0;
        r[0][2] =  -sin(angle);
        r[2][2] =  cos(angle);
        r[3][3] = 1.0;
  
        g_ModelViewMatrix = g_ModelViewMatrix * r;

        // ====================================================================
        // End Exercise code
        // ====================================================================

    }

    glm::mat4 transformation = g_ProjectionMatrix * g_ModelViewMatrix;

    // Iterate over all triangles in the bunny
    for ( int i = 0; i < g_numberOfBunnyVertices ; i += 3 ) {

        // Get points and normals from bunny data array:
        glm::vec4 p1 = glm::vec4(g_bunnyMesh[ (i + 0) * g_bunnyStrideSize + 0],
                                 g_bunnyMesh[ (i + 0) * g_bunnyStrideSize + 1],
                                 g_bunnyMesh[ (i + 0) * g_bunnyStrideSize + 2],
                                 g_bunnyMesh[ (i + 0) * g_bunnyStrideSize + 3]);

        glm::vec4 n1 = glm::vec4(g_bunnyMesh[ (i + 0) * g_bunnyStrideSize + 4],
                                 g_bunnyMesh[ (i + 0) * g_bunnyStrideSize + 5],
                                 g_bunnyMesh[ (i + 0) * g_bunnyStrideSize + 6], 0.0);

        glm::vec4 p2 = glm::vec4(g_bunnyMesh[ (i + 1) * g_bunnyStrideSize + 0],
                                 g_bunnyMesh[ (i + 1) * g_bunnyStrideSize + 1],
                                 g_bunnyMesh[ (i + 1) * g_bunnyStrideSize + 2],
                                 g_bunnyMesh[ (i + 1) * g_bunnyStrideSize + 3]);

        glm::vec4 n2 = glm::vec4(g_bunnyMesh[ (i + 1) * g_bunnyStrideSize + 4],
                                 g_bunnyMesh[ (i + 1) * g_bunnyStrideSize + 5],
                                 g_bunnyMesh[ (i + 1) * g_bunnyStrideSize + 6], 0.0);

        glm::vec4 p3 = glm::vec4(g_bunnyMesh[ (i + 2) * g_bunnyStrideSize + 0],
                                 g_bunnyMesh[ (i + 2) * g_bunnyStrideSize + 1],
                                 g_bunnyMesh[ (i + 2) * g_bunnyStrideSize + 2],
                                 g_bunnyMesh[ (i + 2) * g_bunnyStrideSize + 3]);

        glm::vec4 n3 = glm::vec4(g_bunnyMesh[ (i + 2) * g_bunnyStrideSize + 4],
                                 g_bunnyMesh[ (i + 2) * g_bunnyStrideSize + 5],
                                 g_bunnyMesh[ (i + 2) * g_bunnyStrideSize + 6], 0.0);

        // Apply transformations to points
        p1 = transformation * p1;
        p2 = transformation * p2;
        p3 = transformation * p3;

        // Compute normal of the current triangle
        glm::vec3 normal = glm::normalize(glm::cross(  glm::vec3(p2 - p1) , glm::vec3(p3 - p1) ));

        // Transform normals by transposed inverse Modelview
        glm::mat4 invMod = glm::transpose( glm::inverse( g_ModelViewMatrix ) );
        n1 = invMod * n1;
        n2 = invMod * n2;
        n3 = invMod * n3;

        // Dehomogenization
        if (p1.w != 0.0 )
            p1 /= p1.w;
        if (p2.w != 0.0 )
            p2 /= p2.w;
        if (p3.w != 0.0 )
            p3 /= p3.w;

        //Apply Viewport transformation
        p1 = g_VPMatrix * p1;
        p2 = g_VPMatrix * p2;
        p3 = g_VPMatrix * p3;

        if ( _scene <= 2 ) {
            normal = g_viewDir;
        }


        // Rasterize Triangle
        // triangles are defined in counterclockwise order
        drawTriangle(p1,p2,p3,normal);

    }
}

void initCustomResources() {
}

void deleteCustomResources() {
}

