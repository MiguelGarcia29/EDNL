#include "alg_grafoMA.h"
#include "alg_grafoPMC.h"

typedef std::pair<size_t, size_t> Ciudad; // CHORD X Y

struct Isla
{
    vector<Ciudad> CiudadesIsla;
    matriz<size_t> CostesIslas;
};

typedef vector<Isla> Archipielago;

struct LineaAerea
{
    size_t Origen, Destino;
    size_t CosteLA;
};

typedef vector<LineaAerea> LineasAereas;

size_t DistancaiEuclidea(Ciudad A, Ciudad B)
{
    return sqrt(pow(A.first - B.first, 2) + pow(A.second - B.second, 2));
};

// ME DEVUELVE EL COSTE MINIMO DE UNA ISLA
matriz<size_t> CalcularCostesIslas(const std::vector<Ciudad> &ciudades)
{

    GrafoP<size_t> GIsla(ciudades.size());

    for (int i = 0; i < GIsla.numVert(); i++)
    {
        for (int j = 0; j < GIsla.numVert(); j++)
        {
            GIsla[i][j] = GIsla[j][i] = DistancaiEuclidea(ciudades[i], ciudades[j]);
        }
    }

    matriz<size_t> P;
    matriz<size_t> C = Floyd(GIsla, P);

    return C;
}

//CALCULA LAS LINEAS AEREAS ENTRE ARCHIPIELAGOS
LineasAereas Tumbuctu2(const Grafo&MA, const std::vector<Ciudad>&ciudades){
    Particion P(MA.numVert());
    for(int i=0;i<MA.numVert();i++){
        for(int j=0;j<MA.numVert();j++){
            if(MA[i][j]==true){
                if(P.encontrar(i)!=P.encontrar(j)){
                    P.unir(P.encontrar(i),P.encontrar(j));
                }
            }
        }
    }


    Isla islaaux;
    Archipielago archipielagoAux;

    size_t representanteActual = P.encontrar(0);
    for(int i=0;i<ciudades.size();i++){
        if(P.encontrar(representanteActual)==P.encontrar(i)){
            islaaux.CiudadesIsla.push_back(ciudades[i]);
        }else{
            islaaux.CostesIslas = CalcularCostesIslas(islaaux.CiudadesIsla);
            archipielagoAux.push_back(islaaux);

            islaaux.CiudadesIsla.clear();
            islaaux.CiudadesIsla.push_back(ciudades[i]);

            representanteActual = P.encontrar(i);
        }
    }

    islaaux.CostesIslas = CalcularCostesIslas(islaaux.CiudadesIsla);
    archipielagoAux.push_back(islaaux);

    size_t n= archipielagoAux.size()
    Apo<LineasAereas> A(n*(n-1)/2);

    for(int i=0, i<n;i++){
        for(int j=0;j<n;j++){
            if(P.encontrar(i)!=P.encontrar(j)){
                A.insertar({ciudades[i],ciudades[j],DistancaiEuclidea(ciudades[i][ciudades[j]])})
            }
        }
    }


    Matriz<bool> encontradaas(n,false);
    Vector<LineaAerea> vec(n*n(-1)/2);
    LineaAerea act;
    while(!A.vacio()&&indice<(n*(n-1)/2)){
        act=A.cima();
        A.suprimir()

        if(P.encontrar(act.cDest)!=P.encontrar(act.cOrige)&&encontrada[cDest][cOrig]){
            vec.push_back(act);
            encontrada[cDest][cOrig]=true
            indice ++;
        }
    }

}