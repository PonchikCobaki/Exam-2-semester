#pragma once
#include "Square.h"
class Rhombus : public Square
{
private:
	double alpha;
public:
	Rhombus(double a, double alpha);
	virtual double area();
	virtual ~Rhombus() { };
};

