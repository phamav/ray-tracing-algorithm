#include <iostream>
#include "defs.h"
#include "io.h"
#include "ishape.h"

void checkIntersection(IShape& shape, Ray& ray) {
	HitRecord hit;
	shape.findClosestIntersection(ray, hit);
	cout << "ray: " << ray.origin << " " << ray.dir << endl;
	cout << " ** RESULT: ";
	if (hit.t < FLT_MAX) {
		cout << "hit.t=" << hit.t << ", hit.interceptPt=" << hit.interceptPt << endl;
	}
	else {
		cout << "NO HIT" << endl;
	}
}

int main(int argc, char* argv[]) {
//
//	// right/left pointing rays
//	Ray r1(dvec3(-5, 0, 0), dvec3(1, 0, 0));
//	Ray r2(dvec3(-5, 0, 0), dvec3(-1, 0, 0));
//	Ray r3(dvec3(0, 5.1, 0), dvec3(1, 0, 0));
//	Ray r4(dvec3(0, -5.1, 0), dvec3(1, 0, 0));
//
//
//	// up pointing ray
//	Ray r5(dvec3(0, 0, 0), dvec3(0, 1, 0));
//
//	// other rays
//	Ray r6(dvec3(-3.1, 4.0, 0), dvec3(1, 1, 0));
//	Ray r7(dvec3(-3.1, 6.0, 0), dvec3(1, -1, 0));
//	Ray r8(dvec3(10, 3, -3), dvec3(-1, 0, 0));
//
//	ICylinderY cyl1(dvec3(0, 0, 0), 3.0, 10.0);
//	cout << "***** CYLINDER #1 TESTS: "
//		<< cyl1.center << " "
//		<< cyl1.radius << " "
//		<< cyl1.length << endl;
//	checkIntersection(cyl1, r1);
//	checkIntersection(cyl1, r2);
//	checkIntersection(cyl1, r3);
//	checkIntersection(cyl1, r4);
//	checkIntersection(cyl1, r5);
//	checkIntersection(cyl1, r6);
//	checkIntersection(cyl1, r7);
//	checkIntersection(cyl1, r8);
//
//	ICylinderY cyl2(dvec3(0, 2, 0), 3.0, 10.0);
//	cout << "\n***** CYLINDER #2 TESTS: "
//		<< cyl2.center << " "
//		<< cyl2.radius << " "
//		<< cyl2.length << endl;
//	checkIntersection(cyl2, r1);
//	checkIntersection(cyl2, r2);
//	checkIntersection(cyl2, r3);
//	checkIntersection(cyl2, r4);
//	checkIntersection(cyl2, r5);
//	checkIntersection(cyl2, r6);
//	checkIntersection(cyl2, r7);
//	checkIntersection(cyl2, r8);
//
//	IConeY cone(dvec3(0, 5, 0), 3.0, 10.0);
//	cout << "\n***** CONE TESTS: "
//		<< cone.center << " "
//		<< cone.radius << " "
//		<< cone.height << endl;
//	checkIntersection(cone, r1);
//	checkIntersection(cone, r2);
//	checkIntersection(cone, r3);
//	checkIntersection(cone, r4);
//	checkIntersection(cone, r5);
//	checkIntersection(cone, r6);
//	checkIntersection(cone, r7);
//	checkIntersection(cone, r8);

    
    IConeY cone(dvec3(3, 10, 0), 2.0, 6.0);
    Ray r(dvec3(-5, 0, 0), dvec3(1, 0, 0));
    cout << "\n***** CONE TESTS: "
            << cone.center << " "
            << cone.radius << " "
            << cone.height << endl;
    checkIntersection(cone, r);
    
	return 0;
    
}

/*
***** CYLINDER #1 TESTS: [ 0 0 0 ] 3 10
ray: [ -5 0 0 ] [ 1 0 0 ]
 ** RESULT: hit.t=2, hit.interceptPt=[ -3 0 0 ]
ray: [ -5 0 0 ] [ -1 0 0 ]
 ** RESULT: NO HIT
ray: [ 0 5.1 0 ] [ 1 0 0 ]
 ** RESULT: NO HIT
ray: [ 0 -5.1 0 ] [ 1 0 0 ]
 ** RESULT: NO HIT
ray: [ 0 0 0 ] [ 0 1 0 ]
 ** RESULT: NO HIT
ray: [ -3.1 4 0 ] [ 0.7071067812 0.7071067812 0 ]
 ** RESULT: hit.t=0.1414213562, hit.interceptPt=[ -3 4.1 0 ]
ray: [ -3.1 6 0 ] [ 0.7071067812 -0.7071067812 0 ]
 ** RESULT: hit.t=8.62670273, hit.interceptPt=[ 3 -0.1 0 ]
ray: [ 10 3 -3 ] [ -1 0 0 ]
 ** RESULT: hit.t=9.999999866, hit.interceptPt=[ 1.34110449e-07 3 -3 ]

***** CYLINDER #2 TESTS: [ 0 2 0 ] 3 10
ray: [ -5 0 0 ] [ 1 0 0 ]
 ** RESULT: hit.t=2, hit.interceptPt=[ -3 0 0 ]
ray: [ -5 0 0 ] [ -1 0 0 ]
 ** RESULT: NO HIT
ray: [ 0 5.1 0 ] [ 1 0 0 ]
 ** RESULT: hit.t=3, hit.interceptPt=[ 3 5.1 0 ]
ray: [ 0 -5.1 0 ] [ 1 0 0 ]
 ** RESULT: NO HIT
ray: [ 0 0 0 ] [ 0 1 0 ]
 ** RESULT: NO HIT
ray: [ -3.1 4 0 ] [ 0.7071067812 0.7071067812 0 ]
 ** RESULT: hit.t=0.1414213562, hit.interceptPt=[ -3 4.1 0 ]
ray: [ -3.1 6 0 ] [ 0.7071067812 -0.7071067812 0 ]
 ** RESULT: hit.t=0.1414213562, hit.interceptPt=[ -3 5.9 0 ]
ray: [ 10 3 -3 ] [ -1 0 0 ]
 ** RESULT: hit.t=9.999999866, hit.interceptPt=[ 1.34110449e-07 3 -3 ]

***** CONE TESTS: [ 0 5 0 ] 3 10
ray: [ -5 0 0 ] [ 1 0 0 ]
 ** RESULT: hit.t=3.5, hit.interceptPt=[ -1.5 0 0 ]
ray: [ -5 0 0 ] [ -1 0 0 ]
 ** RESULT: NO HIT
ray: [ 0 5.1 0 ] [ 1 0 0 ]
 ** RESULT: NO HIT
ray: [ 0 -5.1 0 ] [ 1 0 0 ]
 ** RESULT: NO HIT
ray: [ 0 0 0 ] [ 0 1 0 ]
 ** RESULT: NO HIT
ray: [ -3.1 4 0 ] [ 0.7071067812 0.7071067812 0 ]
 ** RESULT: NO HIT
ray: [ -3.1 6 0 ] [ 0.7071067812 -0.7071067812 0 ]
 ** RESULT: hit.t=3.698712394, hit.interceptPt=[ -0.4846153846 3.384615385 0 ]
ray: [ 10 3 -3 ] [ -1 0 0 ]
 ** RESULT: NO HIT

*/
