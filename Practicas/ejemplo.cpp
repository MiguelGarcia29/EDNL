#include <iostream>
#include <fstream>
#include "aBinCelEnla.hpp"
#include "abin_E-S.h"
using namespace std;
typedef char tElto;
const tElto fin = '#';

int main()
{
    Abin<tElto> C;
    cout << "*** Lectura del árbol binario***\n";
    rellenarAbin(C, fin);
    ofstream fs("E.dat");
    imprimirAbin(fs, C, fin);
    fs.close();
    cout << "\n*** Árbol guardado en fichero .dat ***\n";
}
    

