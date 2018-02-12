// Calculator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stack>
#include<iostream>
using namespace std;

void calculator()
{
	stack<double> calc;
	double a, b;
	char str[1];
	cout << "Простейший калькулятор\n";
	cout << "Для выхода введите q\n";
	do
	{
		cout << ":";
		cin >> str;
		switch (*str)
		{
		case '+':
			{ a = calc.top(); calc.pop(); }
			{ b = calc.top(); calc.pop(); }
			cout << a + b << endl;
			calc.push(a + b);
			break;
		case '/':
			{ a = calc.top(); calc.pop(); }
			{ b = calc.top(); calc.pop(); }
			if (!a)
			{
				cout << "Деление на 0\n";
				break;
			}
			cout << b / a << endl;
			calc.push(b / a);
			break;
		case '.': //содержимое вершины стека
			if (!calc.empty()) {
				a = calc.top();
				//calc.push(a);
				cout << "Текущее значение в вершине стека:";
				cout << a << endl;
			}
			break;		default:
			calc.push(atof(str));
		}
	} while (*str != 'q');
}

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Rus");
	calculator();
	return 0;
}

