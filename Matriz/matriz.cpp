#include <iostream>
#include "matriz.h"

using namespace std;

CMatriz::CMatriz(unsigned int uiFilas, unsigned int uiCols) : CArray(uiFilas, uiCols)
{
}

CMatriz::CMatriz(const CMatriz& M) : CArray(M)
{
	// Si nuestra clase tuviese propiedades que copiar, descomentariamos la siguiente linea
	// Donde operator= copiaria las propiedades de esta clase de un objeto a otro.
	// Esta clase al no tener propiedades "extra" sobre la clase base, no necesitamos llamar a operator= y ralentizar ejecucion
	//*this = M;
}

CMatriz& CMatriz::operator=(const CMatriz& M)
{
	CArray::operator=(M);
	return *this;
}

CMatriz CMatriz::operator+(const CMatriz& M) const
{
	const int *p_Dims;
	p_Dims = M.getTblDimensiones();
	double dDato = 0;

	CMatriz Matriz(M);
	for (int i = 0; i < p_Dims[FILAS]; i++)	// Filas
	{
		for (int j = 0; j < p_Dims[COLUMNAS]; j++)	// Columnas
		{
			dDato = ObtenerDato(i, j) + M.ObtenerDato(i, j);
			Matriz.AsignarDato(dDato, i, j);
		}
	}
	return Matriz;
}

/*
MULTIPLICACION DE MATRICES
===========================
Se trata de multiplicar cada fila de la matriz A por cada columna de la matriz B:
Tienen que ser iguales: A(m filas * n columnas) * B(n filas * p columnas) ¡¡¡debe ser n==n!!!

El resultado es una matriz de m filas * p columnas

A=	1	2	3			B=	0	-1	2
	4	5	6				3	0	1
							-2	1	-1
Resultado
	1*0 + 2*3 + 3*-2		1*-1 + 2*0 + 3*1		1*2 + 2*1 + 3*-1
	4*0 + 5*3 + 6*-2		4*-1 + 5*0 + 6*1		4*2 + 5*1 + 6*-1
*/
CMatriz CMatriz::operator*(const CMatriz& M) const
{
	// Primero comprobamos que sean iguales: A(m filas * n columnas) * B(n filas * p columnas) ¡¡¡debe ser n==n!!!
	const int *i_MisDims = getTblDimensiones();
	const int *i_MDims = M.getTblDimensiones();

	double dNum = 0;

	if (i_MisDims[COLUMNAS] == i_MDims[FILAS])
	{
		// La matriz resultado sera de m filas * p columnas
		CMatriz R(i_MisDims[FILAS], i_MDims[COLUMNAS]);

		for (int iFilas = 0; iFilas < i_MisDims[FILAS]; iFilas++)
		{
			for (int iCols = 0; iCols < i_MisDims[COLUMNAS]; iCols++)
			{
				for (int iElem = 0; iElem < i_MisDims[COLUMNAS]; iElem++)
					dNum += this->ObtenerDato(iFilas, iElem) * M.ObtenerDato(iElem, iCols);
				R.AsignarDato(dNum, iFilas, iCols);
				dNum = 0;
			}
		}
		return R;
	}
	return 0;
}


/*
MULTIPLICACION DE UN NUMERO POR UNA MATRIZ
===========================================
Se multiplica el numero por todos los elementos de la matriz

	3	*	2	0	==>		6	0
			1	4			3	12
*/
CMatriz CMatriz::operator*(const int N) const
{
	const int *i_MisDims = getTblDimensiones();

	double dNum = 0;

	// La matriz resultado sera de las mismas dimensiones que la multiplicada
	CMatriz R(i_MisDims[FILAS], i_MisDims[COLUMNAS]);

	for (int iFilas = 0; iFilas < i_MisDims[FILAS]; iFilas++)
		for (int iCols = 0; iCols < i_MisDims[COLUMNAS]; iCols++)
			R.AsignarDato(this->ObtenerDato(iFilas, iCols) * N, iFilas, iCols);

	return R;
}

/*
DIVISION DE UNA MATRIZ ENTRE OTRA MATRIZ
=========================================
Division como tal A/B no hay... Se multiplica A por la inversa de B
*/
CMatriz CMatriz::operator/(const CMatriz& M) const
{
	return 0;
}

// Asigna todos los valores de la Matriz
void CMatriz::AsignarValores(void)
{
	int dims = getDimensiones();
	const int *p_Dims = getTblDimensiones();
	// comprobamos que haya algo en la Matriz
	if (dims > 0)
	{
		system("cls");
		cout << "Matriz de " << p_Dims[FILAS] << " filas X " << p_Dims[COLUMNAS] << " Columnas" << endl;
		for (int i = 0; i < p_Dims[FILAS]; i++)	// Filas
		{
			for (int j = 0; j < p_Dims[COLUMNAS]; j++)	// Columnas
			{
				int iElem = 0;
				cout << "Introduce elemento Fila(" << i + 1 << ") Colummna(" << j + 1 << "): ";
				cin >> iElem;
				AsignarDato(iElem, i, j);
			}
		}
	}
}

void CMatriz::Visualizar() const
{
	int dims = getDimensiones();
	const int *p_Dims = getTblDimensiones();
	// comprobamos que haya algo en la Matriz
	if (dims > 0)
	{
		system("cls");
		cout << "Matriz: filas " << p_Dims[FILAS] << " X " << p_Dims[COLUMNAS] << " columnas" << endl;

		for (int i = 0; i < p_Dims[FILAS]; i++)	// Filas
		{
			for (int j = 0; j < p_Dims[COLUMNAS]; j++)	// Columnas
				cout << '\t' << ObtenerDato(i, j) << '\t';
			cout << endl;
		}
		cin.ignore();
	}
}

// La matriz traspuesta es coger cada fila de la matriz y escribirla como columna:
/*
	2	-1				2	3	4
	3	0		==>		-1	0	-2
	4	-2
*/
CMatriz CMatriz::Traspuesta() const
{
	const int *p_Dims = getTblDimensiones();
	CMatriz M(p_Dims[COLUMNAS], p_Dims[FILAS]);

	for (int i = 0; i < p_Dims[FILAS]; i++)
	{
		for (int j = 0; j < p_Dims[COLUMNAS]; j++)
			M.AsignarDato(ObtenerDato(i, j), j, i);	// Cogemos por columna y asignamos por fila
	}

	return M;
}
