#include "../Grafos/alg_grafoPMC.h"

template <typename tCoste>
vector<bool> viajesPosibles(const GrafoP<tCoste> &Tren, const GrafoP<tCoste> &Bus, const GrafoP<tCoste> &Avion,
                            char Alergia, typename GrafoP<tCoste>::vertice origen)
{

    GrafoP<tCoste> A, B;

    if (strcmp(Alergia, "Avion"))
    {
        A = Tren;
        B = Bus;
    }

    else if (strcmp(Alergia, "Tren"))
    {
        A = Avion;
        B = Bus;
    }

    else if (strcmp(Alergia, "Bus"))
    {
        A = Tren;
        B = Avion;
    }

    vector<tCoste> lineaA = Dijkstra(A, origen, vector<typename GrafoP<tCoste>::vertice>(A.numVert()));
    vector<tCoste> lineaB = Dijkstra(B, origen, vector<typename GrafoP<tCoste>::vertice>(A.numVert()));
    vector<bool> viajable(A.numVert(),false);
    viajable[origen]=true;

    for(int i=0;i<A.numVert();i++){
        if(lineaA[i]!=A.INFINITO||lineaB[i]!=B.INFINITO){
            viajable[i]=true;
        }
    }

    return viajable;

}
