#include <iostream>
#include "matriz.h"

int main(void)
{
	CMatriz matriz2(3, 3);
	matriz2.AsignarValores();
	matriz2.Menor(2,1).Visualizar();
//	matriz2.Visualizar();

	std::cin.get();
	return 0;
}