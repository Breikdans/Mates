#include <iostream>
#include "CArray.h"

using namespace std;

// ===== CONSTRUCTORES ======
CArray::CArray(int iD1, int iD2, int iD3)
{
	int tbl_Dims[3];
	int Dims = 0;
	if (iD1 >= 1)
	{
		tbl_Dims[Dims++] = iD1;
		if (iD2 >= 1)
		{
			tbl_Dims[Dims++] = iD2;
			if (iD3 >= 1)
				tbl_Dims[Dims++] = iD3;
		}
	}
	Construir(Dims, tbl_Dims);
}

CArray::CArray(const CArray& A)					// Constructor COPIA
{
	p_tblDims = NULL;
	pArray = NULL;
	iDims = 0;
	*this = A;
}

void CArray::Construir(int iDim, const int *p_tblDim)
{
	if (iDim < 1)
	{
		cerr << "Numero de Dimensiones invalidas!: " << iDim << endl;
		exit(-1);
	}

	// Asignamos numero de dimensiones
	iDims = iDim;

	// reservamos sitio para el array de subindices
	p_tblDims = new int[iDim];

	// copiamos Array de subindices
	for (int i = 0; i < iDim; i++)
		p_tblDims[i] = p_tblDim[i];

	// reservamos sitio para el array
	pArray = new double[TotalElementos()];
}
// ===== Fin CONSTRUCTORES ======

// ===== OPERADORES =====

CArray& CArray::operator=(const CArray& A)	// Operador =
{
	// si teniamos memoria asignada y algun valor antes, nos lo cargamos
	if (pArray!=NULL)
		delete[] pArray;
	if (p_tblDims!=NULL)
		delete[] p_tblDims;

	Construir(A.getDimensiones(), A.getTblDimensiones());

	memcpy(pArray, A.pArray, sizeof(A.pArray[0]) * A.TotalElementos());
	return *this;
}

// ===== Fin OPERADORES =====

// ===== Setters & Getters ======
int CArray::TotalElementos(void) const
{
	int iTot = p_tblDims[0];
	for(int i = 1; i < iDims; i++)
		iTot *= p_tblDims[i];

	return iTot;
}

void CArray::AsignarDato(double dDato, int i1, int i2, int i3)
{
	int i_tblSubs[] = { i1, i2, i3 };
	int i_indArray = 0;

	i_indArray = Desplazamiento(i_tblSubs);
	pArray[i_indArray] = (double)dDato;
}

double CArray::ObtenerDato(int i1, int i2, int i3) const
{
	int i_tblSubs[] = { i1, i2, i3 };
	int i_indArray = 0;

	i_indArray = Desplazamiento(i_tblSubs);
	if (i_indArray < 0)
		return i_indArray;

	return pArray[i_indArray];
}
// ===== Fin Setters & Getters ======

// Dados unos subindices en el Array pasado por parametros, calculara la posicion en el Array principal
int CArray::Desplazamiento(int *pSubInd) const	///< ENTRADA. Array de subindices donde queremos acceder.
{
/**
* Retval: retorna el indice en el array unidimensional correspondiente al array de subindices pasado por parametro.
* -1 si algun indice es erroneo.
*/
	int iResult = 0;
	// primero comprobamos si el array de subindices que nos han mandado esta dentro de los limites del nuestro
	for(int i = 0; i < iDims; i++)
	{
		if (pSubInd[i] < 0 || pSubInd[i] > p_tblDims[i])	// si el subindice es menor que 0 o mayor que el nuestro, retornamos error
		{
			cerr << "Subindice invalido!: " << pSubInd[i] << endl;
			return -1;
		}
	}
	switch(iDims)
	{
		case 1:
			return pSubInd[0];
		case 2:
			return (pSubInd[0] * p_tblDims[1]) + pSubInd[1];
		case 3:
			return ((pSubInd[0] * p_tblDims[1]) + pSubInd[1]) * p_tblDims[2] + pSubInd[2];
		default:
			cerr << "Dimensiones invalidas!: " << iDims << endl;
			return -1;
	}
}

CArray::~CArray()
{
	delete[] p_tblDims;
	delete[] pArray;
}