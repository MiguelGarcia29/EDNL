#include "../Grafos/alg_grafoPMC.h"

template <typename tCoste>
vector<bool> visitables(GrafoP<tCoste> &A, GrafoP<tCoste> &T,
                        GrafoP<tCoste> B, char *alergia, typename GrafoP<tCoste>::vertice origen, tCoste cantidad)
{

    GrafoP<tCoste> T1, T2;

    if (strcmp(alergia, "Avion")==0)
    {
        T1 = T;
        T2 = B;
    }
    else if (strcmp(alergia, "Tren")==0)
    {
        T1 = A;
        T2 = B;
    }
    else
    {
        T1 = T;
        T2 = A;
    }

    vector<bool> visitable(A.numVert(), false);

    vector<typename GrafoP<tCoste>::vertice> P;
    vector<tCoste> idaT1 = Dijkstra(T1, origen, P);
    vector<tCoste> idaT2 = Dijkstra(T2, origen, P);

    for(int i=0;i<A.numVert();i++){
        if(idaT1[i]!=T1.INFINITO&&idaT1[i]<=tCoste||idaT2[i]!=T2.INFINITO&&idaT2[i]<=tCoste)
            visitable[i]=true;
    }

    return visitable;
}