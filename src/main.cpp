#include "util.h"
#include "lectura.cpp"
#include "pca.h"
#include <algorithm>
#include <vector>

int main(int argc, char const *argv[]) {


	ifstream imagenesTrain;
	imagenesTrain.open("../data/train.dat");
	Matriz etiquetasTrain = Matriz(42000, 1);
	Matriz imagenesTrainM = lecturaTrain(imagenesTrain, etiquetasTrain);
	imagenesTrain.close();

	//	ifstream imagenesTest;
	//	imagenesTest.open("../data/test.dat");
	//	Matriz etiquetasTest = Matriz(28000, 1);
	//	Matriz imagenesTestM = lecturaTest(imagenesTest, etiquetasTest);
	//	imagenesTest.close();

	ifstream testfile;
	testfile.open("../tests/testSimple1.in");
	string ruta = "";
	int vecinos = 0;
	int alpha = 0;
	int folds = 0;
	testfile >> ruta >> vecinos >> alpha >> folds;
	cout << "ruta: " << ruta << " - vecinos: " << vecinos << " - alpha: " << alpha << " - folds: " << folds << endl;
	int flag = 0;
	matrizReal trainmatrix;
	vectorEntero trainlabels;

	for (int x = 0; x < folds; x++) {
		cout << "la de tu hermana en bolas" << endl;
		trainmatrix.clear();
		trainlabels.clear();
		for (int y = 0; y < 42000; y++) {
			testfile >> flag;
			if (flag == 1) {
				trainmatrix.push_back(imagenesTrainM.ObtenerFila(y + 1));
				trainlabels.push_back(etiquetasTrain.ObtenerFila(y + 1)[0]);
			}
			//cout << flag << "-";
		}
		PCA metodo(trainmatrix, trainlabels, alpha, vecinos, 100, (10^-6));
		for (int y = 0; y < metodo.autovalores.size(); y++) {
			cout << metodo.autovalores[y] << endl;
		}

	}
	testfile.close();
	//PCA(matrizReal &imagenes, vectorEntero &labels, int alfa, int vecinos, int niter, double epsilon);





	//leerParametros(argc, argv);



	return 0;

}