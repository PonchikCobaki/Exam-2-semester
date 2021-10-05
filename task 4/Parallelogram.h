#pragma once

#include "Square.h"


class Parallelogram : public Square
{
private:
	double alpha;		// in radian
	double b;
public:
	Parallelogram(double a, double b, double alpha);		// alpha in deg
	virtual double area() override;
	virtual ~Parallelogram() { };
};

