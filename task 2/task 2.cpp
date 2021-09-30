#include <iostream>
#include <math.h>
#include <string.h>

using namespace std;



char* ftoa(const float& n)
{
    char* charStr = new char[17];

    // защита от исключений
    if (isnan(n)) {
        strcpy_s(charStr, 3, "nan");
        return charStr;
    }
    else if (isinf(n)) {
        strcpy_s(charStr, 3, "inf");
        return charStr;
    }
    else if (n == 0.0) {
        strcpy_s(charStr, 4, "0,0");
        return charStr;
    }

    float number = n;   // копия числа, которая будет изменяться
    bool negative(false);   // флаг для отрицаткельного числа
    // случай с отрицательным числом;
    if (n < 0) {
        negative = true;
        number = -number;
        *(charStr) = '-';
    }
    int i = (negative ? 1 : 0); // щетчик
    int exp = log10(number);    // максимальная разряд числа

    if (exp < 1.0) {    // проверка для чисел с плавающей запятой
        exp = 0;
    }

    int digit;                  // одина цифра фисла
    float multiplier;           // множитель мантиссы
    float accuracity = 1e-6;    // точность сравнения

    while (number > accuracity || exp >= 0) {
        multiplier = pow(10.0, exp);    // вычисление  множителя мантиссы
        digit = floor(number / multiplier); // нахождение цифры;
        *(charStr + i) = '0' + digit;   // запись в массив
        number -= digit * multiplier;   // вычитание из основного числа

        if (exp == 0.0)     // проверка на запятую
            *(charStr + ++i) = ',';
        
        --exp;  // уменьшение степени
        ++i;    // учеличение индекса массива
    }

    if (exp == -1) {    // проверка для чисел без мантиссы
        *(charStr + i++) = '0';
    }
    *(charStr + i) = '\0';  // нуль детерменатор строки

    return charStr;
}


int main(int argc, char** argv) {


    char* stringOfDigit = new char[17];
    float number = 100;
    stringOfDigit = ftoa(number);
    cout << "number: " << number << " | " << "string: " << stringOfDigit << endl;

    number = 0.0;
    stringOfDigit = ftoa(number);
    cout << "number: " << number << " | " << "string: " << stringOfDigit << endl;

    number = -39;
    stringOfDigit = ftoa(number);
    cout << "number: " << number << " | " << "string: " << stringOfDigit << endl;

    number = 54.555;
    stringOfDigit = ftoa(number);
    cout << "number: " << number << " | " << "string: " << stringOfDigit << endl;

    number = 0.0076;
    stringOfDigit = ftoa(number);
    cout << "number: " << number << " | " << "string: " << stringOfDigit << endl;

    number = -0.00001;
    stringOfDigit = ftoa(number);
    cout << "number: " << number << " | " << "string: " << stringOfDigit << endl;

    number = -10000;
    stringOfDigit = ftoa(number);
    cout << "number: " << number << " | " << "string: " << stringOfDigit << endl;

    delete[] stringOfDigit;

    return 0;
}