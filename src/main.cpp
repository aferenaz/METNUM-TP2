
#include "lectura.cpp"
#include <algorithm>  
#include <vector>

int main(int argc, char const *argv[])
{

	
	ifstream imagenesTrain;
	imagenesTrain.open("../data/train.dat");
	Matriz etiquetasTrain = Matriz(42000, 1);
	Matriz imagenesTrainM = lecturaTrain(imagenesTrain, etiquetasTrain);
	Matriz imagenesTrainMCopia=imagenesTrainM;
	imagenesTrain.close();
	
    ifstream imagenesTest;
	imagenesTest.open("../data/test.dat");
	Matriz etiquetasTest = Matriz(28000, 1);
	Matriz imagenesTestM = lecturaTest(imagenesTest, etiquetasTest);
	
	cout<<" TEST "<<endl; 
	
	mostrarImagen(imagenesTestM,1);
	mostrarImagen(imagenesTestM,2);
/*	mostrarImagen(imagenesTestM,3);
	mostrarImagen(imagenesTestM,4);
	mostrarImagen(imagenesTestM,5);
	mostrarImagen(imagenesTestM,6);
*/	
		cout<<" TRAIN "<<endl; 
		
	mostrarImagen(imagenesTrainM,1);
	mostrarImagen(imagenesTrainM,2);
/*	mostrarImagen(imagenesTrainM,3);
	mostrarImagen(imagenesTrainM,4);
	mostrarImagen(imagenesTrainM,5);
	mostrarImagen(imagenesTrainM,6);
	*/
	
	Matriz imagenesTestMCopia=imagenesTestM;
	imagenesTest.close();


	cout<<"knn"<<endl; 
	
	
	int eti;
	
	Matriz Imagen_Test = Matriz(1,784);
		    
  for ( int i = 1  /* recorro 12*/
  ;  i<12
  ; ++i )
  {
       Imagen_Test = copiarFilaiesima(imagenesTestMCopia,i);

       mostrarImagen(Imagen_Test,1);
       
       eti= knn(Imagen_Test,etiquetasTrain,imagenesTrainM, 10
        );

       
    cout<<"El numero es: "<<eti<<endl;
    
	
}
return 0;

}
