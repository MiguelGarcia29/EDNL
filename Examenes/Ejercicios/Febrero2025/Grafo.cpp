#include "../Grafos/alg_grafoMA.h"
#include "../Grafos/alg_grafoPMC.h"

struct Coordenada
{
    int x, y;
};

int coordenadaToVertice(Coordenada c, int n)
{
    return c.x * n + c.y;
}

int distanciaEuclidea(Coordenada c1, Coordenada c2)
{
    return sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2));
}

GrafoP<int> construirIsla(const Grafo &carreteras, const vector<Coordenada> &ciudades)
{

    GrafoP<int> isla(ciudades.size());

    for (int i = 0; i < isla.numVert(); i++)
    {
        for (int j = 0; j < isla.numVert(); j++)
        {
            if (carreteras[i][j] || carreteras[j][i])
            {
                isla[i][j] = isla[j][i] = distanciaEuclidea(ciudades[i], ciudades[j]);
            }
        }
    }

    return isla;
}

// CIUDAD FOBOS, DEIMOS
std::pair<Coordenada, Coordenada> mejorPuente(const Grafo &carreterasF, const vector<Coordenada> &ciudadesF, const vector<Coordenada> &costerasF,
                                              const Grafo &carreterasD, const vector<Coordenada> &ciudadesD, const vector<Coordenada> &costerasD)
{
    GrafoP<int> Feibos = construirIsla(carreterasF, ciudadesF);
    GrafoP<int> Deimos = construirIsla(carreterasD, ciudadesD);

    // SUPER GRAFO CON LAS DOS ISLA
    GrafoP<int> arch(ciudadesF.size() * ciudadesD.size());
    for (int i = 0; i < ciudadesF.size(); i++)
    {
        for (int j = 0; j < ciudadesF.size(); j++)
        {
            arch[i][j] = Feibos[i][j];
        }
    }

    for (int i = 0; i < ciudadesD.size(); i++)
    {
        for (int j = 0; j < ciudadesD.size(); j++)
        {
            arch[i + ciudadesF.size()][j + ciudadesF.size()] = Deimos[i][j];
        }
    }

    int costeMin = arch.INFINITO;

    Coordenada costF, costD;

    for (int i = 0; i < costerasF.size(); i++)
    {
        for (int j = 0; j < costerasD.size(); j++)
        {
            size_t cordF = coordenadaToVertice(costerasF[i],ciudadesF.size());
            size_t cordD = coordenadaToVertice(costerasD[i],ciudadesD.size());

            int coste = distanciaEuclidea(costerasF[i],costerasD[i]);

            arch[cordF][cordD+ciudadesF.size()]=arch[cordD+ciudadesF.size()][cordF]=coste;

            matriz<size_t> P;
            matriz<int> floyd = Floyd(arch,P);

            int acumulado = 0;

            for(int i=0;i<arch.numVert();i++){
                for(int j=0;j<arch.numVert();j++){
                    acumulado = suma(floyd[i][j],acumulado);
                }
            }

            if(acumulado<costeMin){
                costeMin = acumulado;
                costF=costerasF[i];
                costD=costerasD[j];
            }


            arch[cordF][cordD+ciudadesF.size()]=arch[cordD+ciudadesF.size()][cordF]=arch.INFINITO;

        }
    }

    return std::make_pair(costF,costD);

}
