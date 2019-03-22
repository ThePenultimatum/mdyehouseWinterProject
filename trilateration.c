#include <stdint.h>
#include "trilateration.h"

float newXVal(float x1, float y1, float r1,float x2, float y2, float r2,float x3, float y3, float r3) {
	//(-2* x1 + 2 * x2) * x + (-2 * y1 + 2 * y2) * y = (r1)^2 - (r2)^2 - (x1)^2 + (x2)^2 - (y1)^2 + (y2)^2
	//(-2* x2 + 2 * x3) * x + (-2 * y2 + 2 * y3) * y = (r2)^2 - (r3)^2 - (x2)^2 + (x3)^2 - (y2)^2 + (y3)^2
	float a = (-2* x1 + 2 * x2);
	float b = (-2 * y1 + 2 * y2);
	float c = (r1*r1) - (r2*r2) - (x1*x1) + (x2*x2) - (y1*y1) + (y2*y2);
	float d = (-2* x2 + 2 * x3);
	float e = (-2 * y2 + 2 * y3);
	float f = (r2*r2) - (r3*r3) - (x2*x2) + (x3*x3) - (y2*y2) + (y3*y3);
	return (c*e-f*b) / (e*a-b*d);
}

float newYVal(float x1, float y1, float r1,float x2, float y2, float r2,float x3, float y3, float r3) {
	//(-2* x1 + 2 * x2) * x + (-2 * y1 + 2 * y2) * y = (r1)^2 - (r2)^2 - (x1)^2 + (x2)^2 - (y1)^2 + (y2)^2
	//(-2* x2 + 2 * x3) * x + (-2 * y2 + 2 * y3) * y = (r2)^2 - (r3)^2 - (x2)^2 + (x3)^2 - (y2)^2 + (y3)^2
	float a = (-2* x1 + 2 * x2);
	float b = (-2 * y1 + 2 * y2);
	float c = (r1*r1) - (r2*r2) - (x1*x1) + (x2*x2) - (y1*y1) + (y2*y2);
	float d = (-2* x2 + 2 * x3);
	float e = (-2 * y2 + 2 * y3);
	float f = (r2*r2) - (r3*r3) - (x2*x2) + (x3*x3) - (y2*y2) + (y3*y3);
	return (c*d-a*f) / (b*d-a*e);
}