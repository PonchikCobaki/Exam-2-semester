#include <iostream>

using namespace std;

using someFnc = double (*)(someFnc SomeFunction, findMaxFnc FindMax, int n, ...);
using findMaxFnc = double (*)(int n);

double SomeFunction(someFnc SomeFunction, findMaxFnc FindMax, int n, ...) {
    
    double val = FindMax(n);
    return val;
}

double FindMax(int n) {
    double accuracity = 1e-16;
    double max = -1e16;
    for (int* ptr = &n, int i = 0; n; --n, ++i) {
        if (*(ptr + i) > max) {
            max = *(ptr + i);
        }
    }

    return max;
}

int main()
{
    cout << "max number: " << SomeFunction(SomeFunction, FindMax, 3, 1, 2, 3) << endl;
}
