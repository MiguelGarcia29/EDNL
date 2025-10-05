#include "../Grafos/alg_grafoPMC.h"
#include "../Grafos/alg_grafoMA.h"

struct Puente
{
    size_t ciudadFobos;
    size_t ciudadDeimos;
    Puente(size_t a, size_t j) : ciudadFobos(a), ciudadDeimos(j) {};
};

struct Coordenada
{
    double x, y;
};

double distancaiEuclide(Coordenada a, Coordenada b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

GrafoP<double> construirIsla(const Grafo &conexiones, vector<Coordenada> &coords)
{
    GrafoP<double> isla(conexiones.numVert());

    for (int i = 0; i < conexiones.numVert(); i++)
    {
        for (int j = 0; j < conexiones.numVert(); j++)
        {
            if (conexiones[i][j])
            {
                isla[i][j] = distancaiEuclide(coords[i], coords[j]);
            }
        }
    }
}

GrafoP<double> reconstruirGrecoland(const GrafoP<double> &Fobos, const GrafoP<double> &Deimos)
{

    GrafoP<double> Grecoland(Fobos.numVert() + Deimos.numVert());

    // INSERTO FOBOS
    for (int i = 0; i < Fobos.numVert(); i++)
    {
        for (int j = 0; j < Fobos.numVert(); j++)
        {
            Grecoland[i][j] = Fobos[i][j];
        }
    }

    // INSERTO DEIMOS
    for (int i = 0; i < Deimos.numVert(); i++)
    {
        for (int j = 0; j < Deimos.numVert(); j++)
        {
            Grecoland[i + Fobos.numVert()][j + Fobos.numVert()] = Deimos[i][j];
        }
    }
}

double sumaTotal(matriz<double> &costesMinimos)
{

    double acumulado = 0;
    for (int i = 0; i < costesMinimos.dimension(); i++)
    {
        for (int j = 0; j < costesMinimos.dimension(); j++)
        {
            acumulado = suma(acumulado, costesMinimos[i][j]);
        }
    }
}

Puente mejorPuente(const Grafo &conexionesFobos, const Grafo &conexionesDeimos,
                   vector<Coordenada> &coordsFobos, vector<Coordenada> &coordsDeimos,
                   vector<size_t> &costeraFobos, vector<size_t> &costeraDeimos)
{
    GrafoP<double> Fobos = construirIsla(conexionesFobos, coordsFobos);
    GrafoP<double> Deimos = construirIsla(conexionesDeimos, coordsDeimos);

    GrafoP<double> Grecoland = reconstruirGrecoland(Fobos, Deimos);

    // PRUEBO LAS COMBINIACIONES DE PUENTES
    Puente mejorPuente(costeraFobos[0], costeraDeimos[0]);
    double costeMejorPuente = Grecoland.INFINITO;

    for (size_t cFobos : costeraFobos)
    {
        for (size_t cDeimos : costeraDeimos)
        {
            //PONGO PUENTE
            Grecoland[cFobos][cDeimos + Fobos.numVert()] = Grecoland[cDeimos + Fobos.numVert()][cFobos] = distancaiEuclide(coordsFobos[cFobos], coordsDeimos[cDeimos]);

            matriz<double> costesMin = Floyd(Grecoland, matriz<typename GrafoP<double>::vertice>(Grecoland.numVert()));

            double costeTotal = sumaTotal(costesMin);
            if (costeTotal < costeMejorPuente)
            {
                mejorPuente.ciudadFobos = cFobos;
                mejorPuente.ciudadDeimos = cDeimos;
                costeMejorPuente = costeTotal;
            }

            //QUITO PUENTE
            Grecoland[cFobos][cDeimos + Fobos.numVert()] = Grecoland[cDeimos + Fobos.numVert()][cFobos] = Grecoland.INFINITO;
        }
    }

    return mejorPuente;
}
