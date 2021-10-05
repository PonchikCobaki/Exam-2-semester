#include "Rhombus.h"
#include <cmath>
#define _USE_MATH_DEFINES

Rhombus::Rhombus(double a, double alpha) : Square(a), alpha(alpha * 3.14159 / 180.0)
{
}

double Rhombus::area() {
	return a * a * sin(alpha);
}