#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	float a = 0, b = 0;
	float x = 0, y = 0, z = 0, three = 3, two = 2, one = 1, buf;

	cout << "Введите x = "; cin >> x;
	cout << "Введите y = "; cin >> y;
	cout << "Введите z = "; cin >> z; cout << "\n";

	_asm
	{
		fld[y] // st(2) = y
		fld[three] // st(1) = three
		fld[x] //st(0) = x

		// Вычислим значение a

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
		fstp[a]

		// Вычислим значение b

		fld[one] // st(2) = one
		fld[two] // st(1) = two
		fld[z] // st(0) = z
		fdiv st(0), st(1)
		fptan // st(0) = 1.0, st(1) = tg(st(0))
		fstp [buf] // освобождаем вершину стека
		fmul st(0), st(0)
		fadd st(0), st(2)
		fst [b]
	}

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	system("pause");
	return 0;
}