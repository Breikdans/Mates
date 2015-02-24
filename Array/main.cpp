#include <iostream>
#include "CArray.h"

using namespace std;

#define DIMENSION1	5
#define DIMENSION2	10

void main()
{
	int i = 0, j = 0, conta = 1;
	CArray MiArray(DIMENSION1,DIMENSION2);	// Array de 2 dimensiones (DIMENSION1 * DIMENSION2)

	// Asignar datos al array
	for(i=0;i<DIMENSION1;i++)
		for(j=0;j<DIMENSION2;j++,conta++)
			MiArray.AsignarDato(conta,i,j);

	// Visualizar el array
	for(i=0;i<DIMENSION1;i++)
	{
		for(j=0;j<DIMENSION2;j++)
			cout << MiArray.ObtenerDato(i, j) << " ";
		cout << endl;
	}

	exit(0);
}