#include "../Grafos/alg_grafoPMC.h"

struct Cliente
{
    int ctd;
    int pedido() { return ctd; };
    int entregar(int a) { ctd -= a; };
};

double kmRecorridos(const GrafoP<double> &G, int capacidadMax, vector<Cliente> &clientes,
                    typename GrafoP<double>::vertice fabrica)
{

    vector<bool> repartidos(G.numVert(), false);
    int cantidadRepartir = G.numVert() - 1;
    repartidos[fabrica] = true;

    matriz<double> caminos = Floyd(G, matriz<typename GrafoP<double>::vertice>(G.numVert()));

    // PARTE DE LA FABRICA
    int cantidadActual = capacidadMax;
    typename GrafoP<double>::vertice actual = fabrica;
    typename GrafoP<double>::vertice destino = ubicacionMasCercana(caminos, actual, repartidos);
    double kmRealizados = 0;

    while (cantidadRepartir > 0)
    {
        kmRealizados += caminos[actual][destino];

        // EN EL DESTINO ENTREGA LO QUE LE TOCA
        int ctdadEntregar = clientes[destino].pedido();
        if (ctdadEntregar > cantidadActual)
        {
            clientes[destino].entregar(cantidadActual);
            cantidadActual = 0;
            // VUELVO A LA FABRICA A REPOSTAR Y TNGO Q VOLVER AL CAMINO
            kmRealizados += caminos[destino][fabrica];
            actual = fabrica;
            cantidadActual = capacidadMax;
        }
        else if (ctdadEntregar < cantidadActual)
        {
            clientes[destino].entregar(ctdadEntregar);
            repartidos[destino] = true;
            cantidadRepartir--;
            cantidadActual -= ctdadEntregar;

            // EN CASO DE QUE YA NO QUEDE MAS POR REPARTIR HAY Q VOVLER A LA FABRICA
            if (cantidadRepartir == 0)
            {
                kmRealizados += caminos[actual][fabrica];
            }
            else
            {
                // SI NO SE BUSCA EL SIGUIENTE SITIO
                actual = destino;
                destino = ubicacionMasCercana(caminos, actual, repartidos);
            }
        }
        else
        {
            clientes[destino].entregar(cantidadActual);
            repartidos[destino] = true;
            cantidadRepartir--;
            cantidadActual = 0;
            // VUELVO A LA FABRICA A REPOSTAR Y TNGO Q VOLVER AL CAMINO
            kmRealizados += caminos[destino][fabrica];
            actual = fabrica;
            cantidadActual = capacidadMax;
        }
    }
};

typename GrafoP<double>::vertice ubicacionMasCercana(matriz<double> &caminos, typename GrafoP<double>::vertice actual,
                                                     vector<bool> &repartido)
{

    double costeIr = GrafoP<double>::INFINITO;
    typename GrafoP<double>::vertice cercano = actual;

    for (size_t i = 0; i < repartido.size(); i++)
    {
        if (!repartido[i])
        {
            if (caminos[actual][i] < costeIr)
            {
                costeIr = caminos[actual][i];
                cercano = i;
            }
        }
    }

    return cercano;
}