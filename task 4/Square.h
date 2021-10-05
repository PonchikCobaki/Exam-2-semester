#pragma once


class Square
{
protected:
	double a;
public:
	Square(double a) : a(a){  }
	virtual double area();
	virtual ~Square() { };
	// Смотри лог, виртуальный деструктор нужен для того что бы
	// состовные части классов наследников были удалены через базовый указатель
};

