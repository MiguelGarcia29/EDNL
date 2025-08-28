#include "Arboles/Abb.h"

template <typename T>
T maximo(const Abb<T> &a)
{

    if (a.drcho().vacio)
    {
        return a.elemento();
    }

    return maximo(a.drcho());
}

template <typename T>
T minimo(const Abb<T> &a)
{

    if (a.izqdo().vacio)
    {
        return a.elemento();
    }

    return minimo(a.izqdo());
}

template <typename T>
T Supremo(const Abb<T> &A, const T &x)
{

    if (A.vacio())
        return maximo(A);

    const T &raiz = A.elemento();

    if (x < raiz)
    {
        T supremo = Supremo(A.izqdo(), x);
        return (supremo >= x) ? supremo : raiz;
    }
    else if (x > raiz)
    {
        return Supremo(A.drcho(), x);
    }
    else
    {
        return raiz;
    }
}

template <typename T>
T Infimo(const Abb<T> &A, const T &x)
{
    if (A.vacio())
    {
        return minimo(A);
    }

    const T &raiz = A.elemento();

    if(x>raiz){
        T infimo = Infimo(A.drcho(),x);

        return (infimo<=x) ? infimo:raiz;
    }
    else if(x<raiz){
        return Infimo(A.izqdo(),x);
    }
    else{
        return raiz;
    }
}