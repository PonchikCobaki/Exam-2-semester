#include <iostream>
#include "Square.h"
#include "Parallelogram.h"
#include "Rhombus.h"

int main()
{
    std::cout.precision(4);

    Square *figurePointer = new Square(12.2);
    std::cout << "Square area: " << figurePointer->area() << std::endl;
    delete figurePointer;
    std::cout << std::endl;

    figurePointer = new Parallelogram(1, 2, 30);
    std::cout << "Parallelogram area: " << figurePointer->area() << std::endl;
    delete figurePointer;
    std::cout << std::endl;

    figurePointer = new Rhombus(1, 45);
    std::cout << "Rhombus area: " << figurePointer->area() << std::endl;
    delete figurePointer;

}
