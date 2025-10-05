#include "../Abb/Abb.h"
#include <iostream>

template <typename T>
T minimo(const Abb<T> &A)
{
        std::cout<<A.elemento()<<" \n";

    if (A.izqdo().vacio())
        return A.elemento();

    return minimo(A.izqdo());
}

template <typename T>
T InfimoRec(const Abb<T> &A, T num)
{

    if (A.vacio())
        return -1;

    T raiz = A.elemento();

    if (raiz == num)
    {
        return raiz;
    }

    else if (raiz > num)
    {
        InfimoRec(A.izqdo(), num);
    }
    else
    {
        T infimoAbajo = InfimoRec(A.drcho(), num);
        if (raiz > infimoAbajo)
            return raiz;
        else
            return infimoAbajo;
    }
}

template <typename T>
T maximo(const Abb<T> &A)
{
    if (A.drcho().vacio())
        return A.elemento();

    return maximo(A.drcho());
}

template <typename T>
T SupremoRec(const Abb<T> &A, T num)
{
    if (A.vacio())
        return maximo(A);

    T raiz = A.elemento();

    if (raiz == num)
    {
        return raiz;
    }

    else if (raiz < num)
    {
        SupremoRec(A.drcho(), num);
    }
    else
    {
        T supremoAbajo = SupremoRec(A.izqdo(), num);
        if (raiz < supremoAbajo)
            return raiz;
        else
            return supremoAbajo;
    }
}

int main(){

Abb<int> A;
int numeros[16] = {15,7,20,4,12,18,30,3,5,10,14,16,19,25,40,1};

for(int i=0;i<16;i++){
    A.insertar(numeros[i]);
}


std::cout<<"Infimo de 9: "<<InfimoRec(A,9)<<std::endl;
std::cout<<"Infimo de 27: "<<InfimoRec(A,27)<<std::endl;

//std::cout<<"Supremo de 27: "<<SupremoRec(A,27)<<std::endl;
//std::cout<<"Supremo de 17: "<<SupremoRec(A,17)<<std::endl;

}