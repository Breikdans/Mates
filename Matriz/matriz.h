#if !defined(_MATRIZ_H_)
#define _MATRIZ_H_

#include "cArray.h"

typedef enum
{
	 FILAS = 0
	,COLUMNAS
};

class CMatriz : public CArray
{
	private:
	public:
		CMatriz(unsigned int uiFilas = 1, unsigned int iCols = 1);
		CMatriz(const CMatriz&);
		CMatriz& operator=(const CMatriz&);
		CMatriz operator+(const CMatriz&) const;
		CMatriz operator*(const CMatriz&) const;
		CMatriz operator*(const int) const;
		CMatriz operator/(const CMatriz&) const;
		void Visualizar(void) const;
		void AsignarValores(void);
		CMatriz Traspuesta(void) const;
};

#endif