#include "../Grafos/alg_grafoPMC.h"

struct Puente{
    size_t x,y;
    Puente(size_t x_, size_t y_) : x(x_),y(y_){};
};


template <typename tCoste>
GrafoP<tCoste> superGrafo (const GrafoP<tCoste> & G1,const GrafoP<tCoste> & G2,const GrafoP<tCoste> & G3, const vector<Puente> & puentes){

    GrafoP<tCoste> sGrafo (G1.numVert()+G2.numVert()+G3.numVert());

    for(int i=0;i<G1.numVert()){
        for(int j=0;j<G1.numVert();j++){
            sGrafo[i][j]=G1[i][j];
        }
    }

    for(int i=0;i<G2.numVert()){
        for(int j=0;j<G2.numVert();j++){
            sGrafo[i+G1.numVert()][j+G1.numVert()]=G2[i][j];
        }
    }

    for(int i=0;i<G3.numVert()){
        for(int j=0;j<G3.numVert();j++){
            sGrafo[i+G1.numVert()+G2.numVert()][j+G1.numVert()+G2.numVert()]=G3[i][j];
        }
    }

    for(Puente p : puentes){
        sGrafo[p.x][p.y]=sGrafo[p.y][p.x]=0;
    }

    return sGrafo;
}

template <typename tCoste>
matriz<tCoste> calcularRutas (const GrafoP<tCoste> & G1,const GrafoP<tCoste> & G2,const GrafoP<tCoste> & G3, const vector<Puente> & puentes){

    GrafoP<tCoste> sGrafo = superGrafo(G1,G2,G3,puentes);

    matriz<typename GrafoP<tCoste>::vertice> P;
    matriz <tCoste> costes = Floyd(sGrafo,P);

    return costes;
}