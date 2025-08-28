//RECAMBIARLO POR GRAFODEMATRIZDECOSTE
#include "../Grafos/grafoMA.h"
#include "../Grafos/alg_grafoMA.h"
#include "../Grafos/alg_grafo_E-S.h"
#include <iostream>

struct Casilla{
    int x;
    int y;
};

typedef Grafo::vertice vertice;
typedef std::pair<Casilla,Casilla> Pared;
typedef std::vector<Pared> Paredes;

Casilla verticeToCasilla(vertice v, int N){
    Casilla c;
    c.x = v/N;
    c.y = v%N;
    return c;
};

vertice casillaToVertice(Casilla c, int N){
    vertice v = c.x * N + c.y;

    return v;
};

bool esAdyacente(Casilla c1, Casilla c2){
    return (std::abs(c1.x-c2.x)+std::abs(c1.y-c2.y))==1;
};

Grafo crearAdyacentes(size_t N){
    Grafo G(N*N);
    for(vertice i=0;i<G.numVert();i++){
        for(vertice j=0;G.numVert()<N;j++){
            if(esAdyacente(verticeToCasilla(i,N),verticeToCasilla(j,N)))
                G[i][j]=1;
            else
                G[i][j]=0;
        }
    }

    return G;
};

void colocarParedes(Grafo &G,const Paredes &p,int N){
    for(auto &pared:p){
        vertice x = casillaToVertice(pared.first,N);
        vertice y = casillaToVertice(pared.second,N);
        G[x][y] = G[y][x] = 0;
    }
};

std::pair<vector<vertice>,size_t> construirJuego(int N,const Paredes& p,Casilla entrada, Casilla final){

    Grafo G = crearAdyacentes(N);
    colocarParedes(G,p,N);
    vertice ini = casillaToVertice(entrada,N);
    vertice fini = casillaToVertice(final,N);

    vector<vertice> P;
    //vector<size_t> costeMin = Dijkstra


}

int main(){

    Grafo p = crearAdyacentes(5);

};
