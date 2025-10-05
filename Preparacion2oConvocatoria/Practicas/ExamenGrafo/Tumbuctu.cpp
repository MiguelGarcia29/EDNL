#include "../Grafos/alg_grafoMA.h"
#include "../Grafos/alg_grafoPMC.h"

struct LineaAerea
{
    size_t ciudadA, ciudadB;
    double coste;
    LineaAerea(size_t a, size_t b,double c) : ciudadA(a), ciudadB(b), coste(c) {};

    bool operator<(LineaAerea B) { return coste < B.coste; };
};

struct Ciudad
{
    double x, y;
};


double distanciaEuclidea(Ciudad a, Ciudad b)
{

    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

vector<LineaAerea> Tumbuctu2(vector<Ciudad> &Ciudades, const Grafo &Tumbuctu)
{

    // Cada subconjunto resultante representara una isla
    int numIslas = Tumbuctu.numVert();
    Particion islas(Tumbuctu.numVert());

    for (int i = 0; i < Tumbuctu.numVert(); i++)
    {
        for (int j = 0; j < Tumbuctu.numVert(); j++)
        {
            if (Tumbuctu[i][j])
            {
                if (islas.encontrar(i) != islas.encontrar(j))
                {
                    numIslas--;
                    islas.unir(islas.encontrar(i), islas.encontrar(j));
                }
            }
        }
    }

    // OBTENGO TODAS LAS LINEAS AEREAS
    Apo<LineaAerea> lineasAeras((Tumbuctu.numVert() * (Tumbuctu.numVert() - 1)) / 2);
    for (int i = 0; i < Tumbuctu.numVert(); i++)
    {
        for (int j = 0; j < Tumbuctu.numVert(); j++)
        {
            if(islas.encontrar(i) != islas.encontrar(j)){
                lineasAeras.insertar(LineaAerea(i,j,distanciaEuclidea(Ciudades[i],Ciudades[j])));
            }
        }
    }

    //AÑADO LAS LINEAS NECESARIAS
    vector<LineaAerea> lineasCreadas ((numIslas * (numIslas - 1)) / 2);
    matriz<bool> islasConectadas(numIslas,false);

    for(int i=0;i<(numIslas * (numIslas - 1)) / 2;){
        LineaAerea cima = lineasAeras.cima();
        if(islas.encontrar(cima.ciudadA)!=islas.encontrar(cima.ciudadB)&&!islasConectadas[cima.ciudadA][cima.ciudadB]){
            lineasCreadas.push_back(cima);
            islas.unir(islas.encontrar(cima.ciudadA),islas.encontrar(cima.ciudadB));
            i++;
            islasConectadas[cima.ciudadA][cima.ciudadB]=islasConectadas[cima.ciudadB][cima.ciudadA] = true;
        }
        lineasAeras.suprimir();
    }


}