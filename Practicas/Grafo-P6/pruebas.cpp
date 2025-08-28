#include "visualizacion_grafoPMC2.h"
#include "../Grafos/alg_grafoPMC.h"
#include <iostream>

int main(){

    //std::cout << "" << GrafoP<int>::INFINITO << "\n";
    
    GrafoP<int> G ("./GrafoEj3.dat");

    //std::cout << "" << G.numVert()<< "\n";

    visualizarGrafo(G,"Ej3");

}