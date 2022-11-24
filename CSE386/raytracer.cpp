/****************************************************
 * 2016-2022 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * PLEASE NOTE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/
#include "raytracer.h"
#include "ishape.h"
#include "io.h"

 /**
  * @fn	RayTracer::RayTracer(const color &defa)
  * @brief	Constructs a raytracers.
  * @param	defa	The clear color.
  */

RayTracer::RayTracer(const color& defa)
	: defaultColor(defa) {
}

/**
 * @fn	void RayTracer::raytraceScene(FrameBuffer &frameBuffer, int depth, const IScene &theScene) const
 * @brief	Raytrace scene
 * @param [in,out]	frameBuffer	Framebuffer.
 * @param 		  	depth	   	The current depth of recursion.
 * @param 		  	theScene   	The scene.
 */

void RayTracer::raytraceScene(FrameBuffer& frameBuffer, int depth,
	const IScene& theScene, int N) const {
	const RaytracingCamera& camera = *theScene.camera;
	const vector<VisibleIShapePtr>& objs = theScene.opaqueObjs;
	const vector<PositionalLightPtr>& lights = theScene.lights;

	for (int y = 0; y < frameBuffer.getWindowHeight(); ++y) {
		for (int x = 0; x < frameBuffer.getWindowWidth(); ++x) {
			DEBUG_PIXEL = (x == xDebug && y == yDebug);
			if (DEBUG_PIXEL) {
				cout << "";
			}
			/* CSE 386 - todo  */
            color sum = black;
            // start at bottom right
            double pixelX;
            double pixelY = y + 1 / (2 * N);

            // Sum up all rays from NxN grid (requires another nested loop)
            for (int i = 0; i < N; i++) {
                pixelX = x + 1 / (2 * N);
                pixelX += 1.0 / N;
                for (int j = 0; j < N; j++) {
                    pixelY += 1.0 / N;
                    sum += traceIndividualRay(camera.getRay(pixelX, pixelY), theScene, depth);
                }
            }
            
            sum /= glm::pow(N, 2);
            sum.r = std::max(0.0, std::min(sum.r, 1.0));
            sum.g = std::max(0.0, std::min(sum.g, 1.0));
            sum.b = std::max(0.0, std::min(sum.b, 1.0));
            Ray r = camera.getRay(x, y);
            
            frameBuffer.setColor(x, y, sum);
            frameBuffer.showAxes(x, y, r, 0.25);			// Displays R/x, G/y, B/z axes
        }
	}

	frameBuffer.showColorBuffer();
}

/**
 * @fn	color RayTracer::traceIndividualRay(const Ray &ray,
 *											const IScene &theScene,
 *											int recursionLevel) const
 * @brief	Trace an individual ray.
 * @param	ray			  	The ray.
 * @param	theScene	  	The scene.
 * @param	recursionLevel	The recursion level.
 * @return	The color to be displayed as a result of this ray.
 */

color RayTracer::traceIndividualRay(const Ray& ray, const IScene& theScene, int recursionLevel) const {
	/* CSE 386 - todo  */
	// This might be a useful helper function.
    OpaqueHitRecord theHit;
    VisibleIShape::findIntersection(ray, theScene.opaqueObjs, theHit);
    color totalColor = black;
    const vector<VisibleIShapePtr>& objs = theScene.opaqueObjs;
    const vector<PositionalLightPtr>& lights = theScene.lights;
    // call illuminate
    // add lights
    // clip colors
    if (recursionLevel-- < 0) return totalColor;
    
    for (PositionalLightPtr light: lights) {
        if (theHit.t != FLT_MAX) {
            bool shadow = light->pointIsInAShadow(theHit.interceptPt, theHit.normal, objs, (*theScene.camera).getFrame());
            totalColor += light->PositionalLight::illuminate(theHit.interceptPt, theHit.normal, theHit.material, (*theScene.camera).getFrame(), shadow);
            if (theHit.texture != nullptr) {
                color texel = theHit.texture->getPixelUV(theHit.u, theHit.v);
                totalColor = 0.5 * (texel + totalColor);
            }
        } else {
            return defaultColor;
        }
    }
    
    // calculate the reflected ray
    color newOrigin = IShape::movePointOffSurface(theHit.interceptPt, theHit.normal);
    color newDir = ray.dir - 2 * (glm::dot(ray.dir, theHit.normal)) * theHit.normal;
    // get new color from reflected rays
    totalColor += 0.3 * traceIndividualRay(Ray(newOrigin, newDir), theScene, recursionLevel--);
    
	return totalColor;
}
