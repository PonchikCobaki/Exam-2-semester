#pragma once


class Square
{
protected:
	double a;
public:
	Square(double a) : a(a){  }
	virtual double area();
	virtual ~Square() { };
	// ������ ���, ����������� ���������� ����� ��� ���� ��� ��
	// ��������� ����� ������� ����������� ���� ������� ����� ������� ���������
};

