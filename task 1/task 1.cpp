#include <iostream>
#include <stdio.h>
#include <stdarg.h>

using namespace std;

using someFnc = double (*)(someFnc, findMaxFnc, int n, ...);
using findMaxFnc = void (*)(double& max, int& num);

double SomeFunction(someFnc SomeFunction, findMaxFnc FindMax, int n, ...);
void FindMax(double& max, int& num);



int sum(int n, ...)
{
    int result = 0;
    // получаем указатель на параметр n
    for (int* ptr = &n; n > 0; n--)
    {
        result += *(++ptr);
    }
    return result;
}

int main()
{
    cout << "sum number: " << sum(3, 1, 2, 3) << endl;
    //cout << "max number: " << SomeFunction(SomeFunction, FindMax, 3, 1, 2, 3) << endl;
}

double SomeFunction(someFnc SomeFunction, findMaxFnc FindMax, int n, ...) {
    double max = -1e16;
    for (int i = 0, int* ptr = &n; n > 0; n--, ++i) {
        FindMax(max, *(ptr + i));
    }
    return max;
}

void FindMax(double& max, int& num) {
    if (num > max) {
        max = num;
    }
}