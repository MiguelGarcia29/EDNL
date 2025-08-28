#include "../Grafos/alg_grafoPMC.h"
template <typename tCoste>
void distribuciones(GrafoP<tCoste> ciudades, typename GrafoP<tCoste>::vertice origen, int cantidad, vector<int> capacidad, vector<double> descuento)
{

    vector<typename GrafoP<tCoste>::vertice> P;
    vector<tCoste> coste = Dijkstra(ciudades, origen, P);

    for (int i = 0; i < ciudades.numVert(); i++)
    {
        coste[i] *= (1.0 - descuento[i] / 100.0);

    }

    // CIUDADES DONDE HE DEJADO PRODUCTOS
    vector<bool> rellenados(ciudades.numVert(), false);
    vector<bool> dejadoCiudades (ciudades.numVert(),0);
    int min = ciudades.INFINITO;
    int pos = 0;
    while (cantidad > 0)
    {
        for (int i = 0; i < ciudades.numVert(); i++)
        {
            if(coste[i]<min&&!rellenados[i]){
                min = coste[i];
                pos = i;
            };
        };

        dejadoCiudades[pos] = std::min(cantidad, capacidad[pos]);
        rellenados[pos] = true;
        cantidad -= capacidad[pos];
        min = ciudades.INFINITO;
        pos = 0;
    };
}