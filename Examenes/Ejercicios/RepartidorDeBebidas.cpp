#include "Grafos/alg_grafoPMC.h"

int *Pedido(typename GrafoP<int>::vertice);

bool porRepartir(vector<bool> &c)
{

    for (bool a : c)
    {
        if (a)
            return a;
    }

    return false;
}

typename GrafoP<int>::vertice clienteMasCerca(matriz<int> &m, vector<bool> &clientesRepartido, typename GrafoP<int>::vertice origen)
{

    int costeMin = GrafoP<int>::INFINITO;
    typename GrafoP<int>::vertice destino;

    for (int i = 0; i < clientesRepartido.size(); i++)
    {
        if (!clientesRepartido[i])
        {
            if (m[origen][i] < costeMin)
            {
                costeMin = m[origen][i];
                destino = i;
            }
        }
    }
}

int repartir(GrafoP<int> &c, int max, typename GrafoP<int>::vertice central)
{

    // FLOYD PARA OBTENER A DONDE TENGO QUE IR Y EN CASO DE QUE REPARTA PARTIR HACIA EL SIGUIETNE DESTINO
    matriz<typename GrafoP<int>::vertice> P;
    matriz<int> caminos = Floyd(c, P);

    int distanciaTotal = 0;

    typename GrafoP<int>::vertice actual = central;
    int cantidadActual = max;

    vector<bool> clientesRepartido(c.numVert(), false);
    typename GrafoP<int>::vertice destino;

    while (porRepartir(clientesRepartido))
    {
        destino = clienteMasCerca(caminos, clientesRepartido, actual);
        distanciaTotal += caminos[actual][destino];
        int *cajasClt = Pedido(destino);
        if (*cajasClt > cantidadActual)
        {
            cajasClt -= cantidadActual;
            distanciaTotal += caminos[actual][central];
            cantidadActual = max;
            actual = central;
        }

        else
        {
            cajasClt = 0;
            cantidadActual -= *cajasClt;
            clientesRepartido[destino] = true;
            actual=destino;
        }
    }

    distanciaTotal += caminos[actual][central];

    return distanciaTotal;
}