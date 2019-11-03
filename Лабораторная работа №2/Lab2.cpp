#include <cmath>
#include <iostream>
#include <windows.h>
using namespace std;

double z1(double x) {
	return (abs(x));
}
double z2(double x) {
	return (abs(x) + cos(x));
}
double z3(double x) {
	return (tan(x));
}

int main()
{
	setlocale(LC_ALL, "Russian");

	double a, b, x, x1, x2, d, temp, zmax, zmin;
	cout << " a=";
	cin >> a;

	cout << " b=";
	cin >> b;

	cout << " xнач=";
	cin >> x1;

	cout << " xкон=";
	cin >> x2;

	cout << " d=";
	cin >> d;

	if (x1 > x2) {
		x1 = x1 + x2;
		x2 = x1 - x2;
		x1 = x1 - x2;
	}

	zmax = 0;
	zmin = 100;

	cout << "|\t" << "x  "  << "\t|\t " << "y  " << "    \t |" << endl;

	for (int i = 0; i <= (x2 - x1) / d; i++) {
		x = x1 + d * i;

		if (x <= a)
		{
			temp = z1(x);
			cout << "|\t  " << x << "\t|\t " << temp << "    \t |";
			if (zmin > temp) zmin = temp;
			if (zmax < temp) zmax = temp;
		}
		if ((a < x) && (x < b))
		{
			temp = z2(x);
			cout << "|\t  " << x << "\t|\t " << temp << "  \t |";
			if (zmin > temp) zmin = temp;
			if (zmax < temp) zmax = temp;
		}
		if (x >= b)
		{
			temp = z3(x);
			cout << "|\t  " << x << "\t|\t " << temp << "  \t |";
			if (zmin > temp) zmin = temp;
			if (zmax < temp) zmax = temp;
		}
		cout << endl;

	}
	cout << "zmax" << zmax << endl;
	cout << "zmin" << zmin << endl;
	return 0;
}
