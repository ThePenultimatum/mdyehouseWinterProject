#include <stdint.h>
	// (-2* x1 + 2 * x2) * x + (-2 * y1 + 2 * y2) * y = (r1)^2 - (r2)^2 - (x1)^2 + (x2)^2 - (y1)^2 + (y2)^2 (-2* x2 + 2 * x3) * x + (-2 * y2 + 2 * y3) * y = (r2)^2 - (r3)^2 - (x2)^2 + (x3)^2 - (y2)^2 + (y3)^2
	// =>
	// Ax + By = C 
	// Dx + Ey = F
	// x = (CE - FB)/(EA - BD) 
	// y = (CD - AF)/(BD - AE)
// x1, y1, r1, x2, y2, r2, x3, y3, r3
float newX(float, float, float, float, float, float, float, float, float);
float newY(float, float, float, float, float, float, float, float, float);