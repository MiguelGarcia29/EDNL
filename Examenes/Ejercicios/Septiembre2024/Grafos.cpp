#include "../Grafos/alg_grafoPMC.h"



int coordToVertice(int x,int y){

    return x*8+y;

}




int minMovimientos(size_t entrada, size_t salida){

    GrafoP<int> tablero(8*8);

    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            size_t actual = coordToVertice(i,j);
            tablero[actual][actual]=0;
            if (j - 2 >= 0 && i + 1 < 8)
                tablero[actual][coordToVertice(i + 1, j - 2)] = tablero[coordToVertice(i + 1, j - 2)][actual] = 1;
            if (j - 1 >= 0 && i - 2 >= 0)
                tablero[actual][coordToVertice(i - 2, j - 1)] = tablero[coordToVertice(i - 2, j - 1)][actual] = 1;
            if (j + 1 < 8 && i - 2 >= 0)
                tablero[actual][coordToVertice(i - 2, j + 1)] = tablero[coordToVertice(i - 2, j + 1)][actual] = 1;
            if (j + 2 < 8 && i - 1 >= 0)
                tablero[actual][coordToVertice(i - 1, j + 2)] = tablero[coordToVertice(i - 1, j + 2)][actual] = 1;
            if (j + 2 < 8 && i + 1 < 8)
                tablero[actual][coordToVertice(i + 1, j + 2)] = tablero[coordToVertice(i + 1, j + 2)][actual] = 1;
            if (j + 1 < 8 && i + 2 < 8)
                tablero[actual][coordToVertice(i + 2, j + 1)] = tablero[coordToVertice(i + 2, j + 1)][actual] = 1;
            if (j - 1 >= 0 && i + 2 < 8)
                tablero[actual][coordToVertice(i + 2, j - 1)] = tablero[coordToVertice(i + 2, j - 1)][actual] = 1;
            if (j - 2 >= 0 && i - 1 >= 0)
                tablero[actual][coordToVertice(i - 1, j - 2)] = tablero[coordToVertice(i - 1, j - 2)][actual] = 1;
        }
    }

    vector<size_t> P;
    vector<int> coste = Dijkstra(tablero,entrada,P);

    return coste[salida];

}