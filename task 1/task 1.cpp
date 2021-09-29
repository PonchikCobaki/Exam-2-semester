#include <iostream>
#include <stdio.h>
#include <stdarg.h>

using namespace std;

using findMaxFnc = double (*)(double num);
using someFnc = double (*)(const findMaxFnc& FindMax, double n, ...);

double FindMax(double num);
double SomeFunction(const findMaxFnc& FindMax, double n, ...);;

int main()
{
    cout << "max number: " << SomeFunction(FindMax, 3, SomeFunction, 0.0042, 0.003) << endl;
}

double SomeFunction(const findMaxFnc& FindMax, double n, ...) {

    double (*SomeFunction)(const findMaxFnc & FindMax, double n, ...);
    va_list Arguments;
    va_start(Arguments, n);
    SomeFunction = va_arg(Arguments, someFnc);  // указатель функции на саму себя
    --n;

    double max(0);
    // поск максимума
    for (; n > 0; n--)
        max = FindMax(va_arg(Arguments, double));
    
    va_end(Arguments);
    return max;
}

double FindMax(double num) {
    cout << "number: " << num << endl;
    static double max = -1e16;
    if (num > max) {
        max = num;
    }
    return max;
}
