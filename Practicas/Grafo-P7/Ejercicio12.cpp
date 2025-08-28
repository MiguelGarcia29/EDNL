#include "../Grafos/alg_grafoPMC.h"

template <typename tCoste>
GrafoP<tCoste> superGrafo(const GrafoP<tCoste> &G1, const GrafoP<tCoste> &G2)
{

    GrafoP<tCoste> sGrafo(G1.numVert() + G2.numVert());

    for (int i = 0; i < G1.numVert(); i++)
    {
        for (int j = 0; j < G1.numVert(); j++)
        {
            sGrafo[i][j] = G1[i][j];
        }
    }

    for (int i = 0; i < G2.numVert(); i++)
    {
        for (int j = 0; j < G2.numVert(); j++)
        {
            sGrafo[i + G1.numVert()][j + G1.numVert()] = G2[i][j];
        }
    }

    return sGrafo;
}

template <typename tCoste>
std::pair<typename GrafoP<tCoste>::vertice, typename GrafoP<tCoste>::vertice>
mejorPuente(const GrafoP<tCoste> &G1, const GrafoP<tCoste> &G2,
            const vector<typename GrafoP<tCoste>::vertice> &costerasG1,
            const vector<typename GrafoP<tCoste>::vertice> &costerasG2)
{

    GrafoP<tCoste> sGrafo = superGrafo(G1, G2);

    tCoste min = G1.INFINITO;
    // PARA GUARDAR LA QUE TENGA MEJOR CONEXION CON LOS PUENTES
    typename GrafoP<tCoste>::vertice puente1, puente2;

    matriz<typename GrafoP<tCoste>::vertice> P;
    matriz<tCoste> coste;
    tCoste sumaT;

    for (int i = 0; i < costerasG1.size(); i++)
    {
        for (int j = 0; j < costerasG2.size(); j++)
        {
            //PONGO EL PUENTE
            sGrafo[costerasG1[i]][costerasG2[j]+G1.numVert()] = sGrafo[costerasG2[j]+G1.numVert()][costerasG1[i]] = 0;

            //CALCULO EL COSTE DE FLOYD DE PONER HAY EL PUENTE
            coste = Floyd(sGrafo,P);
            sumaT = sumaFloyd(coste);

            if(sumaT<min){
                min = sumaT;
                puente1 = costerasG1[i];
                puente2 = costerasG2[j];
            }

            //QUITO EL PUENTE
            sGrafo[costerasG1[i]][costerasG2[j]+G1.numVert()] = sGrafo[costerasG2[j]+G1.numVert()][costerasG1[i]] = G1.INFINITO;
        }
    }

    return std::make_pair(puente1,puente2);
}

// SUMA TODO LA MATRIZ DE COSTE MINIMOS
template <typename tCoste>
tCoste sumaFloyd(matriz<tCoste> S)
{
    tCoste sum = 0;
    for (int i = 0; i < S.dimension(); i++)
    {
        for (int j = 0; j < S.dimension(); j++)
        {
            sum = suma(S[i][j], sum);
        }
    }

    return sum;
}