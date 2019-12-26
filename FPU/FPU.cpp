#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	float a = 0, b = 0;
	float x = 0, y = 0, z = 0, three = 3;

	cout << "Введите x = "; cin >> x; cout << "\n";
	cout << "Введите y = "; cin >> y; cout << "\n";
	cout << "Введите z = "; cin >> z; cout << "\n";

	cout << endl << endl << endl;

	_asm
	{
		fld[y] // st(2) = y
		fld[three] // st(1) = three
		fld[x] //st(0) = x

		fst st(3) // st(0) -> st(3)
		fmul st(0), st(0) // x*x
		fmul st(0), st(3) // x*x
		fabs // чтобы сбросить знак, если число будет отрицательное
		fdiv st(0), st(1) // x^3 / 3
		fadd st(0), st(2) // (x^3 / 3) + y
		fstp st(2) // значение из st(0) -> st(2)
		fld[x] // st(0) = x
		fmul st(0), st(0) // x*x
		fabs
		fdiv st(0), st(2)// x^2 / (x^3 / 3) + y
		fabs
		fstp st(2)// значение из st(0) -> st(2)
		fld[y] // st(0) = y
		fmul st(0), st(0)
		fabs
		fadd st(0), st(2)
		fstp st(2)
		fld[x] // st(0) = x
		fdiv st(0), st(2)
		fstp st(2)
		fld[y]
		fadd st(0), st(2)
		fst[a]
	}

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	system("pause");
	return 0;
}