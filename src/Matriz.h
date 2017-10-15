#include <vector>
#include <iostream>
#include <math.h>
#include <cassert>
#include <stdlib.h>
#include <algorithm>
#include <stdexcept>

using namespace std;

class Matriz {
public:

	Matriz();
	Matriz(int al, int an);

	Matriz(vector<vector<double> > v);


	void Definir(int i, int j, double s);


	double Obtener(int i, int j) const;

	void insertarEnColumna(Matriz a, int c);
	Matriz Traspuesta();
	Matriz multiMatricial(const Matriz& b) const;
	void multiEscalar(double a);
	void sumaMatricial(const Matriz& b);
	void restaMatricial(Matriz& b);
	double multi(const Matriz& b, int i, int j)const;
	Matriz copiarMatriz() const;

	double norma2Vectorial() const;
	double norma2Cuadrado() const;
	ostream& mostrarMatriz(ostream&) const;
	void mostrar() const;
	void randomizar(int m, int n);

	Matriz& operator=(const Matriz& a);
	int Alto() const;
	int Ancho() const;



	double sumatoria(const Matriz& a, int i, int j);

	double media(int k) const;
	void centrarConMedia();
	void restarFila(double media, int k);

	void cambiarBaseX(int alfa);
	Matriz cambiarIesima(const Matriz& mb, int j);
	void insertarEnFila(Matriz& a, int f);

	void DefinirFila(int, vector<double>);
	vector<double> ObtenerFila(int f);
	void insertarEnFila2(Matriz& a, int f);
	void insertarEnFila1(Matriz& a, int f, int source);
	void cambiarBaseX2(int alfa, Matriz cambioBase);

	double productoEscalar(Matriz& a, Matriz& b);

	Matriz multiXtrans() const;


	vector<double> dameVectorMedias();

	void centrarConMediaNuevo(vector<double>, int);

	void cambiarBaseNuevo(Matriz&);

	void mezclarMatriz();



private:


	int _alto;
	int _ancho;
	vector<vector<double> > _matriz;



};

Matriz::Matriz() {
	_alto = 0;
	_ancho = 0;
	_matriz = (std::vector<std::vector<double> > ());
}

Matriz::Matriz(int al, int an) : _alto(al), _ancho(an) {
	std::vector<double> v;
	for (int i = 0; i < an; i++) {
		v.push_back(0);
	}

	vector<vector<double> > prueba(al, v);
	_matriz = prueba;
}

Matriz::Matriz(vector<vector<double> > v) {
	_matriz = v;
	_alto = v.size();
	_ancho = v[0].size();
}

Matriz& Matriz::operator=(const Matriz& a) {

	_alto = a._alto;
	_ancho = a._ancho;
	_matriz = a._matriz;
	return *this;


}

int Matriz::Ancho() const {
	return _ancho;
}

int Matriz::Alto() const {
	return _alto;
}

void Matriz::Definir(int i, int j, double s) {
	assert(i <= _alto && j <= _ancho);

	_matriz[i - 1][j - 1] = s;

}

void Matriz::DefinirFila(int f, vector<double> filaNueva) {
	_matriz[f - 1] = filaNueva;
}

vector<double> Matriz::ObtenerFila(int f) {
	return _matriz[f - 1];
}

double Matriz::Obtener(int i, int j) const {
	return _matriz[i - 1][j - 1];

}

Matriz Matriz::Traspuesta() {
	Matriz result(_ancho, _alto);
	double aux;
	for (int i = 0; i < _alto; i++) {
		for (int j = 0; j < _ancho; j++) {
			//cout<<"par i j: "<<i<<" , "<<j<<endl;
			aux = _matriz[i][j];
			result.Definir(j + 1, i + 1, aux);


		}
	}


	return result;
}

ostream& operator<<(ostream& out, const Matriz a) {
	return a.mostrarMatriz(out);
}

ostream& Matriz::mostrarMatriz(ostream& os) const {
	cout << "------------------" << endl;

	for (int i = 0; i < _alto; i++) {
		os << "[";
		for (int j = 0; j < _ancho; j++) {
			if (j != _ancho - 1) {
				os << _matriz[i][j] << ",";
			} else {
				os << _matriz[i][j] << "]" << endl;
			}
		}
	}
	cout << "------------------";

}

void Matriz::mostrar() const {

	cout << "------------------" << endl;
	for (int i = 0; i < _alto; i++) {
		cout << "[";
		for (int j = 0; j < _ancho; j++) {
			if (j != _ancho - 1) {
				cout << _matriz[i][j] << ",";
			} else {
				cout << _matriz[i][j] << "]" << endl;
			}
		}


	}
	cout << "------------------";
}

double Matriz::sumatoria(const Matriz& a, int i, int j) {
	double sum = 0;
	for (int k = 1; k <= j - 1; k++) {
		sum = sum + Obtener(i, k) * Obtener(j, k);
	}
	return sum;

}

Matriz randomFold(int k) {
	Matriz fold(42000, k);
	for (int i = 1; i <= k; ++i) {
		//srand(time(NULL));
		for (int j = 1; j <= 42000 / k; ++j) {
			int indice = (rand() % 42000) + 1;
			fold.Definir(indice, i, 1);
		}
	}
	return fold;
}

Matriz Matriz::multiXtrans() const {
	Matriz result(Alto(), Alto());
	int fila1 = 1;
	while (fila1 <= Alto()) {
		//if(fila1 % 100==0){
		cout << "iteracion " << fila1 << endl;
		// }
		int fila2 = 1;
		while (fila2 <= Alto()) {
			int i = 1;
			double r = 0;
			while (i <= Ancho()) {
				double aux = (_matriz[fila1 - 1][i - 1]);
				if (fila1 == fila2) {
					r = r + (aux * aux);
				} else {
					r = r + (aux)*(_matriz[fila2 - 1][i - 1]);
				}
				i++;

			}
			result.Definir(fila1, fila2, r);
			r = 0;
			fila2++;
		}
		fila1++;
	}
	return result;


}

Matriz Matriz::multiMatricial(const Matriz& b) const {
	int m = this->Alto();
	int n = this->Ancho();
	int k = b.Ancho();
	assert(n == b.Alto());

	Matriz resultante(m, k);
	double aij;
	for (int i = 1; i <= m; ++i) {

		for (int j = 1; j <= k; ++j) {

			resultante.Definir(i, j, this->multi(b, i, j));
		}
	}
	return resultante;
}

void Matriz::multiEscalar(double a) {
	int m = _alto; //m filas
	int n = _ancho; //n columnas
	double aux;
	//Matriz resultante = Matriz(m, n);
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			aux = a * this->Obtener(i, j);
			this->Definir(i, j, aux);
		}

	}

}

void Matriz::sumaMatricial(const Matriz& b) {
	int m = this->Alto();
	int n = this->Ancho();
	assert(b.Alto() == m && b.Ancho() == n);
	//Matriz resultante = Matriz(m, n);
	double resta;
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			resta = this->Obtener(i, j) + b.Obtener(i, j);
			this->Definir(i, j, resta);
		}
	}
}

void Matriz::restaMatricial(Matriz& b) {
	b.multiEscalar(-1);
	//Matriz copia = this*;

	this->sumaMatricial(b);
}

double Matriz::norma2Vectorial() const {
	int m = _alto;
	int n = _ancho;
	assert(n * m == n || n * m == m); //son vectores
	double norma = 0;
	double aux;
	if (n * m == n) { //vector fila
		for (int i = 1; i <= n; ++i) {
			aux = this->Obtener(1, i);
			norma = norma + (aux * aux);
		}
		norma = sqrt(norma);
	} else { //vector columna
		for (int i = 1; i <= m; ++i) {
			aux = this->Obtener(i, 1);
			norma = norma + (aux * aux);
		}
		norma = sqrt(norma);

	}
	return norma;

}

double Matriz::norma2Cuadrado() const {
	int m = _alto;
	int n = _ancho;
	assert(n * m == n || n * m == m); //son vectores
	double norma = 0;
	double aux;
	if (n * m == n) { //vector fila
		for (int i = 1; i <= n; ++i) {
			aux = this->Obtener(1, i);
			norma = norma + (aux * aux);
		}
	} else { //vector columna
		for (int i = 1; i <= m; ++i) {
			aux = this->Obtener(i, 1);
			norma = norma + (aux * aux);
		}

	}
	return norma;

}

Matriz Matriz::copiarMatriz()const {
	int m = _alto;
	int n = _ancho;
	Matriz copia = Matriz(m, n);
	double aux;
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			aux = this->Obtener(i, j);
			copia.Definir(i, j, aux);
		}
	}
	return copia;
}

double Matriz::multi(const Matriz& b, int i, int j)const { //fila i (this) * col j(b);
	double res = 0;
	int n = _ancho;
	double aik;
	double bkj;
	for (int k = 1; k <= n; ++k) {

		aik = this->Obtener(i, k);
		bkj = b.Obtener(k, j);
		res = res + (aik * bkj);
	}
	return res;
}

void Matriz::insertarEnColumna(Matriz a, int c) {
	int m = this->Alto();
	assert(a.Alto() == m);
	for (int i = 1; i <= m; ++i) {
		double aux = a.Obtener(i, 1);
		this->Definir(i, c, aux);
	}

}

void Matriz::randomizar(int m, int n) {
	srand(time(NULL));
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			double randi = rand();
			this->Definir(i, j, randi);
		}
	}
}

double Matriz::media(int k) const { //media de la fila k de la matriz
	double media = 0;
	int n = this->Ancho();

	for (int i = 1; i <= n; ++i) {
		media = media + this->Obtener(k, i);
	}
	media = media / n;
	return media;
}

void Matriz::centrarConMedia() { //ojo que tambien me modifica this
	int n = this->Alto();
	int m = this->Ancho();
	double media;
	double raiz = sqrt(n - 1);
	raiz = pow(raiz, -1);

	for (int i = 1; i <= n; ++i) {
		media = this->media(i); //media de la fila i
		this->restarFila(media, i);
	}
	this->multiEscalar(raiz);
}

void Matriz::restarFila(double media, int k) {
	int m = this->Ancho();
	double aux;
	for (int i = 1; i <= m; ++i) {
		aux = this->Obtener(k, i);
		aux = aux - media;
		this->Definir(k, i, aux);
	}
}

void Matriz::insertarEnFila1(Matriz& a, int f, int source) {
	int n = this->Ancho();
	for (int i = 1; i <= n; ++i) {
		a.Definir(f, i, this->Obtener(source, i));
	}

}

void Matriz::insertarEnFila(Matriz& a, int f) {
	int n = this->Ancho();
	for (int i = 1; i <= n; ++i) {
		a.Definir(f, i, this->Obtener(1, i));
	}

}

Matriz Matriz::cambiarIesima(const Matriz& mb, int j) { //tengo que multiplicar la fila j-esima de this por la matriz mb
	//mas vale que mb tenga m filas
	Matriz resultante(1, this->Ancho());

	int m = mb.Ancho();
	for (int i = 1; i <= m; ++i) {
		//cout<<"iteracion cambiar "<<i<<endl;
		double rji = this->multi(mb, j, i);
		resultante.Definir(1, i, rji);
	}
	return resultante; //la j-esima columna de this cambiada de base
}

struct tuplaDistanciaEtiq {
	int etiqueta;
	double distancia;

	tuplaDistanciaEtiq(int e, double d) : etiqueta(e), distancia(d) {
	}; //puede que no sea de ints

	tuplaDistanciaEtiq() {
	};

};

void selectionSortVoid(std::vector<tuplaDistanciaEtiq>& v, int k) {
	int actual = 0;
	while (actual < k) {
		int minimo = actual;
		int j = actual + 1;
		while (j < v.size()) {
			if (v[j].distancia < v[minimo].distancia) {
				minimo = j;
			}
			j++;
		}
		tuplaDistanciaEtiq aux = v[actual];
		v[actual] = v[minimo];
		v[minimo] = aux;
		actual++;

	}

}

int lugarMaximo(std::vector<int> v) {
	int max = 0;
	for (int i = 0; i <= 9; ++i) {
		if (v[i] > v[max]) {
			max = i;
		}
	}

	return max;

}

double normaResta(Matriz& a, Matriz& b, int f) {

	double aux;
	double res = 0;
	for (int i = 1; i <= a.Ancho(); ++i) {
		aux = a.Obtener(1, i) - b.Obtener(f, i);
		res = res + aux*aux;
	}
	res = sqrt(res);
	return res;
}

int moda(std::vector <tuplaDistanciaEtiq> v, int k) {

	vector<int> contadores;
	for (int i = 0; i <= 9; ++i) {
		contadores.push_back(0);
	}

	for (int i = 0; i < k; ++i) {
		int aux = v[i].etiqueta;
		contadores[aux]++;
	}

	return lugarMaximo(contadores);

}

int knn(Matriz& e, Matriz& etiquetasT, Matriz& t, int k) {
	int n = t.Alto();
	vector<tuplaDistanciaEtiq> distancias;
	double aux;
	for (int i = 1; i <= n; ++i) {


		aux = normaResta(e, t, i);
		distancias.push_back(tuplaDistanciaEtiq(etiquetasT.Obtener(i, 1), aux));
	}
	selectionSortVoid(distancias, k);
	if (distancias[0].distancia == 0) {
		return distancias[0].etiqueta;
	} else {
		return moda(distancias, k);
	}
}

int knniesimo(Matriz& imagenes, Matriz& etiquetasT, Matriz& t, int k, int l) {
	int n = t.Alto();
	vector<tuplaDistanciaEtiq> distancias;
	double aux;
	for (int i = 1; i <= n; ++i) {
		for (int k = 1; k <= imagenes.Ancho(); ++k) {
			aux = imagenes.Obtener(l, k) - t.Obtener(i, k);
			aux = aux*aux;
		}
		distancias.push_back(tuplaDistanciaEtiq(etiquetasT.Obtener(i, 1), aux));

	}
	selectionSortVoid(distancias, k);

	return moda(distancias, k);
}

double promedio(vector<double> v) {
	double media = 0;
	int n = v.size();

	for (int i = 0; i < n; ++i) {
		media = media + v[i];
	}
	media = media / n;
	return media;
}

double productoEscalar(Matriz& a, Matriz& b) {
	double res = 0;
	double aux;
	int f = a.Alto();

	for (int i = 0; i < f; ++i) {
		aux = a.Obtener(i, 1) * b.Obtener(1, i);
		res = res + aux;
	}
	return res;
}




