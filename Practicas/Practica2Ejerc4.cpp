#include "ABinConVec.hpp"

int main(){

    Abin<char> A(31);
    A.insertarRaiz('h');
    A.insertarHijoIzqdo('a','h');
    A.insertarHijoDrcho('m','h');

    A.insertarHijoIzqdo('n','a');
    //A.insertarHijoDrcho('b','a');
    // A.insertarHijoIzqdo('l','b');
    // A.insertarHijoIzqdo('f','l');
    // A.insertarHijoDrcho('d','b');
    // A.insertarHijoDrcho('j','m');
    // A.insertarHijoIzqdo('c','j');
    A.verVector();
}