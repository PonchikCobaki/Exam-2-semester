#include <iostream>
#include <stdarg.h>

using namespace std;

// указатели на функции
using findMaxFnc = void (*)(const double& num, double& max);
using someFnc = double (*)(const findMaxFnc& FindMax, double n, ...);

// прототипы функциий
void FindMax(const double& num, double& max);
double SomeFunction(const findMaxFnc& FindMax, double n, ...);;

int main()
{
    cout << "max number: " << SomeFunction(FindMax, 3, SomeFunction, 0.0042, 0.003) << endl;
    cout << "max number: " << SomeFunction(FindMax, 5, SomeFunction, 0.0042, 0.003, 55544.0, 0, 0) << endl;
}

double SomeFunction(const findMaxFnc& FindMax, double n, ...) {

    someFnc SomeFunctionPtr;
    va_list Arguments;
    va_start(Arguments, n);
    SomeFunctionPtr = va_arg(Arguments, someFnc);  // указатель функции на саму себя
    --n;

    double max = -1e16;
    // поск максимума
    for (; n > 0; n--)
       FindMax(va_arg(Arguments, double), max);
    
    va_end(Arguments);

    return max;
}

void FindMax(const double& num, double& max) {
    if (num > max) {
        max = num;
    }
}
