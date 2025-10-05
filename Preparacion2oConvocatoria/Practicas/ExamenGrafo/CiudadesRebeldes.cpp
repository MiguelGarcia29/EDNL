#include "../Grafos/alg_grafoPMC.h"

typedef std::pair<size_t,size_t> Carretera;

template <typename tCoste>
matriz<tCoste> CiudadRebeldes(GrafoP<tCoste> G,vector<bool>& ciudadTomada,vector<Carretera>& carreterasTomadas, 
    typename GrafoP<tCoste>::vertice Capital){

        //BLOQUEAR LAS CIUDADES TOMADAS
        for(int i=0;i<ciudadTomada.size();i++){
            if(ciudadTomada[i]){
                for(int j=0;j<G.numVert();j++){
                    G[j][i]=G[i][j]=G.INFINITO;
                }
            }
        }

        //QUITAR LAS CARRETERAS
        for(Carretera c : carreterasTomadas){

            G[c.first()][c.second()]=G.INFINITO;
        }

        vector<typename GrafoP<tCoste>::vertice> P;
        vector<tCoste> desdeCapital = Dijkstra(G,Capital,P);
        vector<tCoste> haciaCapital = DijkstraInv(G,Capital,P);

        matriz<tCoste> viajes(G.numVert(),G.INFINITO);

        for(int i=0;i<G.numVert();i++){
            for(int j=0;j<G.numVert();j++){
                if(i==j)
                    G[i][j]=0;
                
                viajes[i][j]=suma(haciaCapital[i],desdeCapital[j]);

            }
        }

        return viajes;

    }