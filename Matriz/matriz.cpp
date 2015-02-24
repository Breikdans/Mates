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
	const int *p_Dims = getTblDimensiones();
	// comprobamos que haya algo en la Matriz
	if (p_Dims[FILAS] > 0)
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
	const int *p_Dims = getTblDimensiones();
	// comprobamos que haya algo en la Matriz
	if (p_Dims[FILAS] > 0)
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


// Dada la posicion de un termino de una matriz, el MENOR es el resto de terminos, exceptuando la fila y columna dada:
/*
Teniendo la matriz A:
	2	3	8
	7	8	9
	2	0	1

El Menor del termino de A12(termino 7) seria:
	X	3	8
	X	X	X
	X	0	1
O sea:
		3	8
		0	1
*/
CMatriz CMatriz::Menor(unsigned int f, unsigned int c)
{
	int tot_filas_menor = 0, tot_cols_menor = 0;
	int men_fil = 0, men_col = 0;
	// Primero comprobamos que nos han pasado una posicion valida
	const int *p_Dims = getTblDimensiones();
	if ( (f == 0 || f > p_Dims[FILAS]) || 
		 (c == 0 || c > p_Dims[COLUMNAS]) )
	{
		cerr << "Dimensiones invalidas!: Filas=" << f << " Columnas=" << c << endl;
		exit(-1);
	}

	// La matriz resultado sera de m filas - 1 * p columnas - 1
	tot_filas_menor = p_Dims[FILAS] - 1;
	tot_cols_menor = p_Dims[COLUMNAS] - 1;

	CMatriz M(tot_filas_menor, tot_cols_menor);

	for (int j = 0; j < p_Dims[FILAS]; j++)
	{
		// si la FILA es DISTINTA a la FILA del TERMINO
		if (j != f-1)
		{
			for (int i = 0; i < p_Dims[COLUMNAS]; i++)
			{
				// si la COLUMNA es DISTINTA a la COLUMNA del TERMINO
				if (i != c-1)
				{
					// AHORA comprobamos si la FILA de la matriz donde guardamos el MENOR está llena
					if (men_fil < tot_filas_menor)
					{
						double dato = ObtenerDato(p_Dims[i], p_Dims[j]);
						M.AsignarDato(dato, men_fil, men_col);
						++men_fil;
					}
					else
					{
						// AHORA comprobamos si la COLUMNA de la matriz donde guardamos el MENOR está llena
						if (men_col < tot_cols_menor)
						{
							M.AsignarDato(this->ObtenerDato(p_Dims[i], p_Dims[j]), men_fil, men_col);
							++men_col;
						}
						else
							break;

					}
				}
			}
		}
	}
	return M;
}