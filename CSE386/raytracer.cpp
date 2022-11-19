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
	const IScene& theScene) const {
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
			Ray ray = camera.getRay(x, y); // get the rayfor the pixel at (x, y)
			OpaqueHitRecord theHit;
			VisibleIShape::findIntersection(ray, theScene.opaqueObjs, theHit);
            // If there's a texture, get the color from it.
            // compute color in the usual way
            // color based on the shape we hit
            color c;
            // call illuminate
            // add lights
            // clip colors
            for (PositionalLightPtr light : lights) {
                if (theHit.t != FLT_MAX) {
                    if (theHit.texture != nullptr) {
                        color texel = theHit.texture->getPixelUV(theHit.u, theHit.v);
                        frameBuffer.setColor(x, y, texel);
                    } else {
                        bool shadow = light->pointIsInAShadow(theHit.interceptPt, theHit.normal, objs, camera.getFrame());
                        c += light->PositionalLight::illuminate(theHit.interceptPt, theHit.normal, theHit.material, camera.getFrame(), shadow);
                        frameBuffer.setColor(x, y, c);
                    }
                } else {
                    c += defaultColor;
                }
            }
                
            c.r = std::max(0.0, std::min(c.r, 1.0));
            c.g = std::max(0.0, std::min(c.g, 1.0));
            c.b = std::max(0.0, std::min(c.b, 1.0));

            frameBuffer.showAxes(x, y, ray, 0.25);			// Displays R/x, G/y, B/z axes
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
    recursionLevel = 0;
	return black;
}
