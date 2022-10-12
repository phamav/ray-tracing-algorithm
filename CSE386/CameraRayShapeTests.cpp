#include "camera.h"
#include "ishape.h"
#include "io.h"

/*
 Experimenting with cameras and with viewing rays
 */
void cameraRayTests() {
    dvec3 camPos(0, 0, 0);
    dvec3 camLookPt(0, 0, -2);
    dvec3 up(0, 1, 0);
    double fov = glm::radians(45.0); // only for perspective cameras
    int scale = 1; // only for orthographic cameras (PPWW on worksheet)
    int nx = 200;
    int ny = 200;
    
//    PerspectiveCamera cam(camPos, camLookPt, up, fov, nx, ny);
    OrthographicCamera cam(camPos, camLookPt, up, nx, ny, scale);
    
    // Check that the frame is what we expect (pos, u, v, w)
    Frame frame = cam.getFrame();
    cout << frame;
    
    // Check that the image plane is what we expect (top, bottom, left, right)
    // (and distToPlane for perspective cameras)
//    cout << cam.getDistToPlane() << endl;
    cout << cam.getTop() << endl;
    cout << cam.getRight() << endl;
    cout << cam.getLeft() << endl;
    cout << cam.getBottom() << endl;

    
    
    //*******************************************
    //Ray experiments...set aside camera for a moment
    
    // Create a ray with origin at (0, 0, 0) and direction (7, 0, 0) (dir is normalized)
    // How is a ray different from a vector?
//    Ray ray(dvec3(0, 0, 0), dvec3(7, 0, 0));
//    cout << ray.origin << " " << ray.dir << endl;
    // Check its origin and direction
    // Note that these are relative to WORLD coordinates and frame (not camera frame)
    
    
    
    // The parametric equation of the ray is:
    // p(t) = origin + t * dir       (dir is normalized)
//    cout << ray.getPoint(0.0) << endl;
//    cout << ray.getPoint(1.0) << endl;
//    cout << ray.getPoint(27.0) << endl;
    
    //*******************************************
    // Our camera gives us back rays.
    // Each pixel in the rendering window has a corresponding ray through the image plane
    // WARNING: getRay() requires that map() is correctly implemented in utilities.cpp
    
    
    
    // **** Stop for some math ****
    // 1. How do we take a pixel (x,y) in the rendering window and
    // compute its corresponding coordinates in the image plane?
    // (calculations are the same for both camera types)
    Ray r = cam.getRay(100, 100); // gets the viewing ray for pixel (0, 0)
    cout << r.origin << endl;
    cout << r.dir << endl;
    cout << r.getPoint(0) << endl;
    cout << r.getPoint(1) << endl;
    
    // 2. How do we take a pixel (x,y) in the rendering window and
    // compute its corresponding viewing ray through the image (origin and angle)?
    // (perspective calculations are different from orthographic calculations)
    
}

/*
 Experimenting with viewing rays to see if they intersect spheres.
 */
void rayShapeTests() {
    
    dvec3 camPos(0, 0, 0);
    dvec3 camLookPt(20, 0, 0);
    dvec3 up(0, 1, 0);
    double fov = glm::radians(45.0); // only for perspective cameras
    int scale = 1; // only for orthographic cameras
    int nx = 200;
    int ny = 200;
    
    PerspectiveCamera cam(camPos, camLookPt, up, fov, nx, ny);

    
    // ******* Ignore the camera for now
    
    // Ray - Object intersection: spheres
    // Create a sphere at (20, 0, 0) with a radius of 5
    ISphere sphere(dvec3(20, 0, 0), 5);
    
    // Create a ray with origin (0, 0, 0) looking in the direction (1, 0, 0)
    Ray ray(dvec3(0, 0, 0), dvec3(1, 0, 0));
    
    // Intuitively: Does this ray intersect this sphere?
    // How can we check with code?
    // WARNING: only works if quadratic(a, b, c, double[2]) is working
    HitRecord hits[2]; // stores data about the hits including t, and intersection pt.
    int hitCount = sphere.findIntersections(ray, hits);
    cout << hitCount << endl;
    cout << hits[1].interceptPt << endl;
    
    // can my camera see the sphere?
    cout << sphere.findIntersections(cam.getRay(100, 100), hits) << endl;
    
}


//int main(int argc, char* argv[]) {
////    cameraRayTests();
////    rayShapeTests();
//    dvec3 up(0, 1, 0);
//    dvec3 w(0.8, 0.6, 0);
//    dvec3 u = glm::normalize(glm::cross(up, w));
//    cout << u << endl;
//    
//    return 0;
//    
//}
