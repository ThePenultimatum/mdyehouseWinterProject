#include <stdint.h>
#include "trilateration.h"

float newX(uint32_t x1, uint32_t y1, uint32_t r1,uint32_t x2, uint32_t y2, uint32_t r2,uint32_t x3, uint32_t y3, uint32_t r3) {
	//(-2* x1 + 2 * x2) * x + (-2 * y1 + 2 * y2) * y = (r1)^2 - (r2)^2 - (x1)^2 + (x2)^2 - (y1)^2 + (y2)^2
	//(-2* x2 + 2 * x3) * x + (-2 * y2 + 2 * y3) * y = (r2)^2 - (r3)^2 - (x2)^2 + (x3)^2 - (y2)^2 + (y3)^2
	float a = (-2* x1 + 2 * x2);
	float b = (-2 * y1 + 2 * y2);
	float c = (r1)^2 - (r2)^2 - (x1)^2 + (x2)^2 - (y1)^2 + (y2)^2;
	float d = (-2* x2 + 2 * x3);
	float e = (-2 * y2 + 2 * y3);
	float f = (r2)^2 - (r3)^2 - (x2)^2 + (x3)^2 - (y2)^2 + (y3)^2;
	return (c*e-f*b) / (e*a-b*d);
}

float newY(uint32_t x1, uint32_t y1, uint32_t r1,uint32_t x2, uint32_t y2, uint32_t r2,uint32_t x3, uint32_t y3, uint32_t r3) {
	//(-2* x1 + 2 * x2) * x + (-2 * y1 + 2 * y2) * y = (r1)^2 - (r2)^2 - (x1)^2 + (x2)^2 - (y1)^2 + (y2)^2
	//(-2* x2 + 2 * x3) * x + (-2 * y2 + 2 * y3) * y = (r2)^2 - (r3)^2 - (x2)^2 + (x3)^2 - (y2)^2 + (y3)^2
	float a = (-2* x1 + 2 * x2);
	float b = (-2 * y1 + 2 * y2);
	float c = (r1)^2 - (r2)^2 - (x1)^2 + (x2)^2 - (y1)^2 + (y2)^2;
	float d = (-2* x2 + 2 * x3);
	float e = (-2 * y2 + 2 * y3);
	float f = (r2)^2 - (r3)^2 - (x2)^2 + (x3)^2 - (y2)^2 + (y3)^2;
	return (c*d-a*f) / (b*d-a*e);
}