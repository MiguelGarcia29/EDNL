#include "../Grafos/alg_grafoPMC.h"
#include "../Grafos/alg_grafo_E-S.h"

struct Casilla{
    int x;
    int y;
    Casilla(int x1,int y1):x(x1),y(y1){};
};

struct Pared{
    Casilla a,b;
};


typename GrafoP<int>::vertice CasillaToVertice(Casilla c, int N){
    return c.x * N + c.y;
};

Casilla VerticeToCasilla(typename GrafoP<int>::vertice v, int N){
    Casilla c(v/N,v%N);

    return c;
};


int salida(int N, vector<Pared> paredes,typename GrafoP<int>::vertice o,typename GrafoP<int>::vertice s){

    GrafoP<int> G(N*N);

    //CONSTRUIR LABERINTO
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){

            //PONGO LAS CUATRO
            if(i==j)
                G[i][j]=0;

            typename GrafoP<int>::vertice v = CasillaToVertice(Casilla(i,j),N); 
            typename GrafoP<int>::vertice x;
                //ARRIBA
            if(i+1<N){
                x = CasillaToVertice(Casilla(i+1,j),N);
                G[v][x] = 1;
            }
                //ABAJO
            if(i-1>=0){
                x = CasillaToVertice(Casilla(i-1,j),N);
                G[v][x] = 1;
            }
                //DRCHA
            if(j+1<N){
                x = CasillaToVertice(Casilla(i,j+1),N);
                G[v][x] = 1;
            }
                //IZQ
            if(j-1>=0){
                x = CasillaToVertice(Casilla(i,j-1),N);
                G[v][x] = 1;
            }
        }
    }

    for(Pared p : paredes){
        typename GrafoP<int>::vertice a = CasillaToVertice(p.a,N); 
        typename GrafoP<int>::vertice b = CasillaToVertice(p.b,N); 

        G[a][b]=G[b][a]=G.INFINITO;
    }


    vector<typename GrafoP<int>::vertice> P;
    vector<int> D=Dijkstra(G,o,P);

    return D[s];

}