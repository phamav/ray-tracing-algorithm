/****************************************************
 * 2016-2022 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#include <ctime>
#include "defs.h"
#include "io.h"
#include "ishape.h"
#include "framebuffer.h"
#include "raytracer.h"
#include "iscene.h"
#include "light.h"
#include "image.h"
#include "camera.h"
#include "rasterization.h"

PositionalLightPtr posLight1 = new PositionalLight(dvec3(5, 5, 5), white);
PositionalLightPtr posLight2 = new PositionalLight(dvec3(10, 10, 10), white);
PositionalLightPtr posLight3 = new PositionalLight(dvec3(10, 10, 10), white);
PositionalLightPtr posLight4 = new PositionalLight(dvec3(10, 10, 10), white);
vector<PositionalLightPtr> lights = { posLight1, posLight2, posLight3, posLight4 };

FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);
RayTracer rayTrace(paleGreen);

dvec3 cameraPos(1, 2, 0);
dvec3 cameraFocus(4, 2, 0);
dvec3 cameraUp = Y_AXIS;
double cameraFOV = PI_2;

IScene scene;

void render() {
	int frameStartTime = glutGet(GLUT_ELAPSED_TIME);
	int width = frameBuffer.getWindowWidth();
	int height = frameBuffer.getWindowHeight();

	scene.camera = new PerspectiveCamera(cameraPos, cameraFocus, cameraUp, cameraFOV, width, height);
    
	rayTrace.raytraceScene(frameBuffer, 0, scene);

	int frameEndTime = glutGet(GLUT_ELAPSED_TIME); // Get end time
	double totalTimeSec = (frameEndTime - frameStartTime) / 1000.0;
	cout << "Render time: " << totalTimeSec << " sec." << endl;
}

void resize(int width, int height) {
	frameBuffer.setFrameBufferSize(width, height);
	glutPostRedisplay();
}

void buildScene() {
    // Mathematical definitions of your shapes
    IShape* plane = new IPlane(dvec3(-5.0, 0.0, 4.0), dvec3(0.0, 0.0, 0.0)); // point, normal vector
    IConeY* cone1 = new IConeY(dvec3(1.0, 1.0, 0.0), 4.0, 2.0);
    IConeY* cone2 = new IConeY(dvec3(4.0, 1.0, 0.0), 4.0, 2.0);
    ICylinderY* cyl = new ICylinderY(dvec3(2.5, 1.0, 0.0), 4.0, 3.0);
    // we need at least one visibleIShape or transparentIShape
	scene.addOpaqueObject(new VisibleIShape(plane, greenPlastic));
    scene.addOpaqueObject(new VisibleIShape(cone1, ruby));
    scene.addOpaqueObject(new VisibleIShape(cone2, turquoise));
    scene.addOpaqueObject(new VisibleIShape(cyl, yellowRubber));
    // add light
	scene.addLight(lights[0]);
    scene.addLight(lights[1]);
    scene.addLight(lights[2]);
    scene.addLight(lights[3]);
    
}


int main(int argc, char* argv[]) {
	graphicsInit(argc, argv, __FILE__);

	glutDisplayFunc(render);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboardUtility);
	glutMouseFunc(mouseUtility);

	buildScene();

	glutMainLoop();

	return 0;
}
