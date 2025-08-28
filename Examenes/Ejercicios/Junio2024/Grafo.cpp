#include "../Grafos/alg_grafoPMC.h"

struct Coordenada
{
    int x, y;
};

int distanciaEuclidea(Coordenada c1, Coordenada c2)
{

    return sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2));
}

int costeMin(vector<Coordenada> ciudadesFobos, vector<Coordenada> ciudadesDeimos, vector<Coordenada> ciudadesEuropa,
             vector<bool> costerasFobos, vector<bool> costerasDeimos, vector<bool> costerasEuropa, Coordenada origen, Coordenada destino)
{
    GrafoP<int> archipielago(ciudadesDeimos.size() + ciudadesEuropa.size() + ciudadesFobos.size());

    int puenteMasCaro = 0;

    // PUENTRE ENTRE DEIMOS Y EUROPA
    for (int i = 0; i < costerasDeimos.size(); i++)
    {
        for (int j = 0; j < costerasEuropa.size(); j++)
        {
            if (costerasDeimos[i] && costerasEuropa[i])
            {
                int distancia = distanciaEuclidea(ciudadesDeimos[i], ciudadesEuropa[j]);
                size_t verticeD = i;
                size_t verticeE = j;

                if (distancia > puenteMasCaro)
                    puenteMasCaro = distancia;

                archipielago[verticeD][verticeE + ciudadesDeimos.size()] = archipielago[verticeE + ciudadesDeimos.size()][verticeD] = distancia;
            }
        }
    }

    // PUENTRE ENTRE EUROPA Y FOBOS
    for (int i = 0; i < costerasEuropa.size(); i++)
    {
        for (int j = 0; j < costerasFobos.size(); j++)
        {
            if (costerasEuropa[i] && costerasFobos[i])
            {
                int distancia = distanciaEuclidea(ciudadesEuropa[i], ciudadesFobos[j]);
                size_t verticeD = i;
                size_t verticeE = j;

                if (distancia > puenteMasCaro)
                    puenteMasCaro = distancia;

                archipielago[verticeE + ciudadesDeimos.size()][verticeD + ciudadesDeimos.size() + ciudadesEuropa.size()] = archipielago[verticeD + ciudadesDeimos.size() + ciudadesEuropa.size()][verticeE + ciudadesDeimos.size()] = distancia;
            }
        }
    }

    // PUENTE ENTRE FOBOS Y Deimos
    for (int i = 0; i < costerasFobos.size(); i++)
    {
        for (int j = 0; j < costerasDeimos.size(); j++)
        {
            if (costerasFobos[i] && costerasDeimos[i])
            {
                int distancia = distanciaEuclidea(ciudadesFobos[i], ciudadesDeimos[j]);
                size_t verticeD = i;
                size_t verticeE = j;

                if (distancia > puenteMasCaro)
                    puenteMasCaro = distancia;

                archipielago[verticeD + ciudadesDeimos.size() + ciudadesEuropa.size()][verticeE] = archipielago[verticeE][verticeD + ciudadesDeimos.size() + ciudadesEuropa.size()] = distancia;
            }
        }
    }

    // CONECTO DEIMOS
    for (int i = 0; i < ciudadesDeimos.size(); i++)
    {
        for (int j = 0; j < ciudadesDeimos.size(); j++)
        {
            archipielago[i][j] = archipielago[j][i] = distanciaEuclidea(ciudadesDeimos[i], ciudadesDeimos[j]) + puenteMasCaro;
        }
    }

    // CONECTO EUROPA
    for (int i = 0; i < ciudadesEuropa.size(); i++)
    {
        for (int j = 0; j < ciudadesEuropa.size(); j++)
        {
            archipielago[i + ciudadesDeimos.size()][j + ciudadesDeimos.size()] = archipielago[i + ciudadesDeimos.size()][j + ciudadesDeimos.size()] = distanciaEuclidea(ciudadesEuropa[i], ciudadesEuropa[j]) + puenteMasCaro;
        }
    }

    // CONECTO FOBOS
    for (int i = 0; i < ciudadesFobos.size(); i++)
    {
        for (int j = 0; j < ciudadesFobos.size(); j++)
        {
            archipielago[i + ciudadesDeimos.size() + ciudadesEuropa.size()][j + ciudadesDeimos.size() + ciudadesEuropa.size()] = archipielago[i + ciudadesDeimos.size() + ciudadesEuropa.size()][j + ciudadesDeimos.size() + ciudadesEuropa.size()] = distanciaEuclidea(ciudadesFobos[i], ciudadesFobos[j]) + puenteMasCaro;
        }
    }

    // RECONSTRUYO GRECOLAND
    GrafoP<int> grecoland = Kruskall(archipielago);

    int vectI, vectD;

    bool encontradoD = false;
    bool encontradoI = false;

    for (int i = 0; i < ciudadesDeimos.size() && (!encontradoD || !encontradoI); i++)
    {
        if (ciudadesDeimos[i].x == origen.x && ciudadesDeimos[i].y == origen.y)
        {
            encontradoI = true;
            vectI = i;
        }
        if (ciudadesDeimos[i].x == destino.x && ciudadesDeimos[i].y == destino.y)
        {
            encontradoD = true;
            vectD = i;
        }
    }

    for (int i = 0; i < ciudadesEuropa.size() && (!encontradoD || !encontradoI); i++)
    {
        if (ciudadesEuropa[i].x == origen.x && ciudadesEuropa[i].y == origen.y)
        {
            encontradoI = true;
            vectI = i + ciudadesDeimos.size();
        }
        if (ciudadesEuropa[i].x == destino.x && ciudadesEuropa[i].y == destino.y)
        {
            encontradoD = true;
            vectD = i + ciudadesDeimos.size();
        }
    }

    for (int i = 0; i < ciudadesFobos.size() && (!encontradoD || !encontradoI); i++)
    {
        if (ciudadesFobos[i].x == origen.x && ciudadesFobos[i].y == origen.y)
        {
            encontradoI = true;
            vectI = i + ciudadesDeimos.size() + ciudadesEuropa.size();
        }
        if (ciudadesFobos[i].x == destino.x && ciudadesFobos[i].y == destino.y)
        {
            encontradoD = true;
            vectD = i + ciudadesDeimos.size() + ciudadesEuropa.size();
        }
    }

    vector<size_t> P;
    vector<int> coste = Dijkstra(grecoland, vectI, P);

    return coste[vectD];
}