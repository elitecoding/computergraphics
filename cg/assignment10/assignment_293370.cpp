/*
 * Basics of Computer Graphics Exercise
 */

#include "assignment.h"

using namespace std;

extern glm::mat4 g_ProjectionMatrix;

// add your team members names and matrikel numbers here:
void printStudents() {
    cout << "Julian Arnold,  293370" << endl;
	cout << "Marius Lipka,   334336" << endl;
    cout << "Florian George, 234236" << endl;
    cout << "Houman Biglari, 279942" << endl;
}

//16 queries
GLuint query[16];

// for part D
bool performQuery = true;
int  framesWaited = 0;


void drawScene(int scene,double) {
	static int lastScene = 0;

	if (scene == 1) {
		for (int i = 0; i < 16; i++) {
                     // =======================================================================
                     // =======================================================================
                     // Assignment code:
                     // Part A:
                     //  one query per bunny, render the bounding box with a query, if that
                     //  would generate fragments draw the bunny
                     //
                     //  Use g_bunnyVisibility[i]=true/false to pass information to the
                     //  drawScenePreview function
                     // =======================================================================
                     // ======================================================================
			glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
			glDepthMask(GL_FALSE);
			
			
			glBeginQuery(GL_SAMPLES_PASSED,query[i]);
			drawBoundingObject(i);
			glEndQuery(GL_SAMPLES_PASSED);
			
			GLint fragmentCount;
			glGetQueryObjectiv(query[i],GL_QUERY_RESULT,&fragmentCount);
			if(fragmentCount>0)
				g_bunnyVisibility[i] = true;
			else
				g_bunnyVisibility[i] = false;
			
			glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
			glDepthMask(GL_TRUE);

			if(g_bunnyVisibility[i])
			{
				drawBunny(i);
			}

					 // =======================================================================
                     // End assignment code
                     // =======================================================================
		}
	} else if (scene == 2) {
                // =======================================================================
                // =======================================================================
                // Assignment code:
                // Part B:
                //
		// assume all bunnies to be visible in the first frame
		// start 16 occlusion queries, render the bounding objects
		// in case the bunny was not visible before and the bunny in case it was visible.
		// one frame later evaluate the results.
                //
                // =======================================================================
                // =======================================================================
				
				if(lastScene != 2)
				{
						for (int i = 0; i < 16; i++) {
							g_bunnyVisibility[i] = true;
						}
				}else
				{
					for (int i = 0; i < 16; i++) {
					GLint fragmentCount;
					glGetQueryObjectiv(query[i],GL_QUERY_RESULT,&fragmentCount);
					if(fragmentCount>0)
						g_bunnyVisibility[i] = true;
					else
						g_bunnyVisibility[i] = false;
					}
				}
		
				for (int i = 0; i < 16; i++) {
					
					glBeginQuery(GL_SAMPLES_PASSED,query[i]);
					if(g_bunnyVisibility[i])	
					{
						drawBunny(i);
					}else
					{
						glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
						glDepthMask(GL_FALSE);
						drawBoundingObject(i);
						glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
						glDepthMask(GL_TRUE);
					}
					glEndQuery(GL_SAMPLES_PASSED);

				}
 
                // =======================================================================
                // End assignment code
                // =======================================================================
			
	} else if (scene == 3) {
		
		for (int i = 0; i < 16; i++) {

                  // =======================================================================
                  // =======================================================================
                  // Assignment code:
                  // Part C:
                  //
                  // generate a query and render the bounding boxes, depending on the result 
                  // render the bunny.
                  // let the GPU decide and never actually query the result.
                  // never reading the result back from the GPU helps to avoid stalls.
                  //
                  // =======================================================================
                  // =======================================================================
				
				glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
				glDepthMask(GL_FALSE);
			
			
				glBeginQuery(GL_SAMPLES_PASSED,query[i]);
					drawBoundingObject(i);
				glEndQuery(GL_SAMPLES_PASSED);
			
				glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
				glDepthMask(GL_TRUE);

				glBeginConditionalRender(query[i],GL_QUERY_WAIT);
					drawBunny(i);
				glEndConditionalRender();

                  // =======================================================================
                  // End assignment code
                  // =======================================================================

		}
	} else {
		// =======================================================================
                // =======================================================================
                // Assignment code:
                // Part D:
		// 
		// render all bunnies each frame starting a query at the first frame and check if it is
		// available each frame. if it is available, print the frames that have passed and
		// start a new query in the next frame.
		// 
		// if a result would be available directly, the output would be 0,
		// if it is available after one frame, it would be 1 etc.
		// actual wait times are dependent on the GPU, OS and whether vsync is active.
                // =======================================================================
                // =======================================================================
				
					
					
					if(performQuery)
					{
						glBeginQuery(GL_SAMPLES_PASSED,query[0]);
							for (int i = 0; i < 16; i++) {
								drawBunny(i);
							}
						glEndQuery(GL_SAMPLES_PASSED);
						performQuery = false;
					}else
					{
						for (int i = 0; i < 16; i++) {
								drawBunny(i);
							}
					}

					GLint res;
					glGetQueryObjectiv(query[0],GL_QUERY_RESULT_AVAILABLE,&res);
				
					if(res!=0)
					{
						performQuery = true;
						std::cout<<"Querry result available after: "<<framesWaited<<" frames"<<endl;
						framesWaited = 0;
					}else
					{
						framesWaited++;
					}
	
                // =======================================================================
                // End assignment code
                // =======================================================================	        
	}
	
	lastScene = scene;
}

//
// draw a preview on the right of the window
// we can use the g_bunnyVisibility array to get visibility information from 
// drawScene to here.
// for part B we can use also conditional rendering with the same queries as in drawScene
// for part D just draw all bunnies
//
void drawScenePreview(int scene,double)
{
	if (scene <= 2) {
		for (int i = 0; i < 16; i++) {
                       // =======================================================================
                       // =======================================================================
                       // Assignment code:
                       // Part A/B:
                       //
                       //  Use g_bunnyVisibility[i] an render the boundingbox or the bunny
                       // =======================================================================
                       // =======================================================================
			if(g_bunnyVisibility[i])
			{
				drawBunny(i);
			}else
			{
				drawBoundingObject(i);
			}

                        // =======================================================================
                        // End assignment code
                        // =======================================================================

		}		
	} else if (scene == 3) {
		for (int i = 0; i < 16; i++) {
                   // =======================================================================
                   // =======================================================================
                   // Assignment code:
                   // Part C:
                   //
                   //  Remember to use conditional rendering for the bunny here as well!
                   //
                   // =======================================================================
                   // =======================================================================
				glBeginConditionalRender(query[i],GL_QUERY_WAIT);
					drawBunny(i);
				glEndConditionalRender();

		   // =======================================================================
                   // End assignment code
                   // =======================================================================

		}
	} else {
		for (int i = 0; i < 16; i++) {
			drawBunny( i );
		}
	}
}

void initCustomResources() {
	// Create your resources here, e.g. shaders, buffers,...
    glGenQueries(16, query);
}

void deleteCustomResources() {
    // Don't forget to delete your OpenGL resources (shaders, buffers, etc.)!
    glDeleteQueries( 16, query );
}

