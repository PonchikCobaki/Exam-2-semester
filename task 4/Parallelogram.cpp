#include "Parallelogram.h"
#include <cmath>
#define _USE_MATH_DEFINES
Parallelogram::Parallelogram(double a, double b, double alpha) : Square(a), b(b), alpha(alpha *  3.14159 / 180.0 )
{
}

double Parallelogram::area()
{
	return a * b * sin(alpha);
}
