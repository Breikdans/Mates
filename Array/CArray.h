class CArray{
private:
	double *pArray;		// Array lineal de elementos de tipo double
	int iDims;			// Numero de dimensiones para p_tblDims
	int *p_tblDims;		// puntero a array con el valor de cada dimension

	void Construir(int iDim, const int *p_tblDim);
	int Desplazamiento(int *pSubInd) const;
	int getDimensiones(void) const { return iDims; }
	int TotalElementos(void) const;
public:
	CArray::CArray(int iD1 = 0, int iD2 = 0, int iD3 = 0);
	CArray(const CArray& A);									// Constructor Copia
	CArray& CArray::operator=(const CArray&);					// Operador =
	CArray::~CArray();											// Destructor
	const int *getTblDimensiones(void) const { return p_tblDims; }
	void AsignarDato(double dDato = 0, int i1 = 0, int i2 = 0, int i3 = 0);
	double ObtenerDato(int i1 = 0, int i2 = 0, int i3 = 0) const;
};