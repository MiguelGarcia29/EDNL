#include "../Abin/aBinCelEnla.hpp"

template <typename T>
int nietosNodo(const Abin<T> &A, typename Abin<T>::nodo nA)
{

    if (nA == A.NODO_NULO)
        return 0;
    else
    {
        int nietos = 0;
        // TIENE HIJO IZQDO
        if (A.hijoIzqdo(nA) != A.NODO_NULO)
        {
            if (A.hijoIzqdo(A.hijoIzqdo(nA) != A.NODO_NULO))
                nietos++;
            if (A.hijoDrcho(A.hijoIzqdo(nA) != A.NODO_NULO))
                nietos++;
        }

        if (A.hijoDrcho(nA) != A.NODO_NULO)
        {
            if (A.hijoIzqdo(A.hijoDrcho(nA) != A.NODO_NULO))
                nietos++;
            if (A.hijoDrcho(A.hijoDrcho(nA) != A.NODO_NULO))
                nietos++;
        }
        return nietos;
    }
}

template <typename T>
int TresNietosRec(const Abin<T> &A, typename Abin<T>::nodo nA)
{

    if (nA == A.NODO_NULO)
        return 0;

    if (nietosNodo(A, nA) == 3)
        return 1 + TresNietosRec(A, A.hijoIzqdo(nA)) + TresNietosRec(A, A.hijoDrcho(nA));

    else
        return TresNietosRec(A, A.hijoIzqdo(nA)) + TresNietosRec(A, A.hijoDrcho(nA));
}
