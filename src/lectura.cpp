#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <stdlib.h> 
#include "Matriz.h"
using namespace std;

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */



Matriz lecturaTrain(istream& is, Matriz& etiquetas){
	string etiq;
	double pixel;
	int etiqueta;
	string delim;


	Matriz result = Matriz(42000, 784);

	for (int j = 1; j <= 42000; ++j)	

	{
		getline (is, etiq, '_');
		etiqueta= atof(etiq.c_str());
		for (int i = 1; i <= 783; ++i)
		{
			getline(is, delim, ' ');
			pixel =atof(delim.c_str());
			result.Definir(j,i,pixel);
		}

	getline(is, delim, '/' );
	pixel = atof(delim.c_str());
	result.Definir(j, 784, pixel);
	etiquetas.Definir(j,1,etiqueta);
	}

	return result;
}



Matriz lecturaTest(istream& is, Matriz& etiquetas){
	Matriz resultante = Matriz(28000, 784);
	
	string etiq;
	double pixel;
	string delim;


	for (int j = 1; j <= 28000; ++j)	
	{		
		for (int i = 1; i <= 784; ++i)
		{
			getline(is, delim, ' ');
			pixel =atof(delim.c_str());
			resultante.Definir(j, i, pixel);
		}
	getline(is, delim , '/' );
	etiquetas.Definir(j, 1, 10);
    	
	}



	return resultante;	
}





 
Matriz copiarFilaiesima(Matriz b, int i) {
    int m = i;
    int n = 784;
    Matriz copia = Matriz(1, 784);
    double aux;
     for (int j = 0; j <= n; ++j)
        {
            copia.Definir(1,j, b.Obtener(m,j));                      
        }
    
    return copia;
}


void mostrarImagen(const Matriz& i, int fila ){
	
	double aux;
	int m = i.Ancho();
	
	for (int t = 0; t < 50; ++t){
		cout<<"-";
	}

	cout<<endl;
	
	for (int j = 1; j<m; ++j){
		aux = i.Obtener(fila, j); 
				if(aux != 0){
			cout  <<RED<<"0"<<RESET;
		}else{
			cout<<GREEN<<"0"<<RESET;	
		}
		
		if( j % 28 == 0 && j != 0){cout<<endl;}
	}
	cout<<endl;
	for (int f = 0; f < 50; ++f){
		cout<<"-";
	}
	cout<<endl;
	

}



