// Enunciado: ´Arboles generales similares. Dos ´arboles generales son similares si tienen
// la misma estructura y el contenido de sus nodos hojas deben de ser el mismo.

#include "Arboles/aGenCelEnLa.hpp"

template <typename T>
bool similar(const Agen<T> &A, const Agen<T> &B)
{
}
template <typename T>
bool similarRec(const Agen<T> &A, const Agen<T> &B,
                typename Agen<T>::nodo nA, typename Agen<T>::nodo nB)
{

    bool iguales = true;

    // SI UNO ES NULO Y EL OTRO NO TIENEN DISTINTA FORMA
    if ((nA == A.NODO_NULO && nB != B.NODO_NULO) ||
        (nA != A.NODO_NULO && nB == B.NODO_NULO))
    {
        return false;
    }

    if ((nA == A.NODO_NULO && nB == B.NODO_NULO))
        return true;

    typename Agen<T>::nodo auxA = A.hijoIzqdo(nA);
    typename Agen<T>::nodo auxB = B.hijoIzqdo(nB);

    // MIRO QUE SEAN HOJA Y TENGAN MISMO ELEMENTO PARA SEGUIR MIRANDO ESTRUCTURA
    if (auxA == A.NODO_NULO && auxB == B.NODO_NULO)
    {
        if (A.elemento(nA) != B.elemento(nB))
            return false;
        else
            return true;
    }

    while ((auxA != A.NODO_NULO || auxB != B.NODO_NULO) && iguales)
    {

        iguales &= similarRec(A, B, auxA, auxB);
        if (iguales)
        {
            auxA = A.hermDrcho(auxA);
            auxB = B.hermDrcho(auxB);
        }
    }

    return iguales;
}