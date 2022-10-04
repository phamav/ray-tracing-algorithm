/****************************************************
 * 2016-2022 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * PLEASE NOTE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#include <ctime>
#include <vector>
#include "defs.h"
#include "utilities.h"
#include "framebuffer.h"
#include "colorandmaterials.h"
#include "rasterization.h"
#include "io.h"

FrameBuffer frameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

void render() {
	frameBuffer.clearColorBuffer();
	drawLine(frameBuffer, 0, 0, 100, 100, red);
	drawLine(frameBuffer, 100, 100, 200, 100, blue);
	frameBuffer.showColorBuffer();
}

void resize(int width, int height) {
	frameBuffer.setFrameBufferSize(width, height);
	glutPostRedisplay();
}

void f(int v) {
    v++;
}

// compute the hypothenus of two numbers
double hypot(double a, double b) {
    return sqrt(a*a);
}

// change both values to the maximum value
void makeMax(int &a, int &b) {
    if (a > b) b = a;
    else a = b;
}

double mystery(double a, double b) {
   return (1.0 + sqrt(a - 3.0)) / b;
}

bool closeEnough(double a, double b) {
    return abs(b - a) >= -0.001;
}

int main(int argc, char* argv[]) {
    cout << pointingVector(dvec3(3.0, 4.0, 5.0), dvec3(1.0, 0.0, 0.0)) << endl;
    cout << pointingVector(dvec3(1.0, 1.0, 1.0), dvec3(0.0, 1.0, 0.0)) << endl;
    cout << pointingVector(dvec3(1.0, 0.0, 0.0), dvec3(1.0, 1.0, 1.0)) << endl;
    cout << pointingVector(dvec3(-1.0, -2.0, -3.0), dvec3(-2.0, -3.0, -4.0)) << endl;
	return 0;
}
