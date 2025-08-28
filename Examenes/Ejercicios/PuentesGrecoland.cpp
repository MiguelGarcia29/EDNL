#include "Grafos/alg_grafoPMC.h"

typedef std::pair<size_t, size_t> Ciudad; // ciudad con las coordenadas x,y.

double DistanciaEuclidea(Ciudad A, Ciudad B)
{
    return sqrt(pow(A.first - B.first, 2) + pow(A.second - B.second, 2));
}

template <typename T>
GrafoP<T> superGrafo(const GrafoP<T> &F, const GrafoP<T> &D)
{

    GrafoP<T> arch(F.numVert() + D.numVert());

    for (int i = 0; i < F.numVert(); i++)
    {
        for (int j = 0; j < F.numVert(); j++)
        {
            arch[i][j] = F[i][j];
        }
    }

    for (int i = 0; i < D.numVert(); i++)
    {
        for (int j = 0; j < D.numVert(); j++)
        {
            arch[i + F.numVert()][j + F.numVert()] = D[i][j];
        }
    }
}

template <typename T>
GrafoP<T> reconstruirGreco(vector<Ciudad> &cFobos, vector<Ciudad> &cDeimos, vector<typename GrafoP<T>::vertice> &costerasFobos, vector<typename GrafoP<T>::vertice> &costerasDeimos)
{

    GrafoP<T> Fobos(cFobos.size());
    GrafoP<T> Deimos(cFobos.size());

    // UN PUENTE SERA LA DISTANCIA + LA SUMA DEL MAS CARO
    double factorCoste = 0;

    // RELLENO FOBOS CON SUS CIUDADES
    for (int i = 0; i < cFobos.size(); i++)
    {
        for (int j = i + 1; j < cFobos.size(); j++)
        {
            Fobos[i][j] = Fobos[j][i] = DistanciaEuclidea(cFobos[i], cFobos[j]);
            factorCoste = std::max(factorCoste, Fobos[i][j]);
        }
    }

    // RELLENOS DEIMOS CON CIUDADES
    for (int i = 0; i < cDeimos.size(); i++)
    {
        for (int j = i + 1; j < cDeimos.size(); j++)
        {
            Deimos[i][j] = Deimos[j][i] = DistanciaEuclidea(cDeimos[i], cDeimos[j]);
            factorCoste = std::max(factorCoste, Deimos[i][j]);
        }
    }

    GrafoP<T> arch = superGrafo(Fobos, Deimos);

    // PONEMOS UN PUENTE ENTRE CADA ISLAS COSTERAS
    for (int i = 0; i < costerasFobos.size(); i++)
    {
        for (int j = 0; j < costerasDeimos.size(); j++)
        {
            double costeP = DistanciaEuclidea(cFobos[i], cDeimos[j]) + factorCoste;
            arch[i][j + Fobos.numVert()] = arch[j + Fobos.numVert()][i] = costeP;
        }
    }

    // NOS QUEDAMOS CON LO-S MEJORES PUENTES
    arch = Kruskall(arch);

    // ELIMINO EL INCREMENTO DE USAR PUENTE
    for (int i = 0; i < arch.numVert(); i++)
    {
        for (int j = 0; j < arch.numVert(); j++)
        {
            if (arch[i][j] > factorCoste)
            {
                arch[i][j] - factorCoste;
            }
        }
    }
}

template <typename T>
T costeMin(vector<Ciudad> &cFobos, vector<Ciudad> &cDeimos, vector<typename GrafoP<T>::vertice> &costerasFobos, vector<typename GrafoP<T>::vertice> &costerasDeimos, typename GrafoP<T>::vertice Origen, typename GrafoP<T>::vertice Destino)
{

    GrafoP<T> Grecolandia = reconstruirGreco(cFobos, cDeimos, costerasFobos, costerasDeimos);
    vector<typename GrafoP<T>::vertice> p;
    vector<T> coste = Dijkstra(Grecolandia, Origen, p);

    return coste[Destino];
}
