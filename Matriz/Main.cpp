#include <iostream>
#include "matriz.h"

int main(void)
{
	CMatriz matriz1(2, 3);
	matriz1.AsignarValores();
	matriz1.Visualizar();

	CMatriz matriz2(3, 3);
	matriz2.AsignarValores();
	matriz2.Visualizar();

	CMatriz Result = matriz1 * matriz2;
	Result.Visualizar();

	std::cin.get();
	return 0;
}