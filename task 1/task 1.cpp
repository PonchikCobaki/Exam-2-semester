#include <iostream>
#include <stdarg.h>

using namespace std;

// указатели на функции
using findMaxFnc = double (*)(double num);
using someFnc = double (*)(const findMaxFnc& FindMax, double n, ...);

// прототипы функциий
double FindMax(double num);
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

    double max(0);
    // поск максимума
    for (; n > 0; n--)
        max = FindMax(va_arg(Arguments, double));
    
    va_end(Arguments);

    return max;
}

double FindMax(double num) {
    static double max = -1e16;
    if (num > max) {
        max = num;
    }
    return max;
}
