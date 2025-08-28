#include "../Arboles/aGenCelEnLa.hpp"

struct informacion
{
    bool estado;
    int cantidad;
};

bool tieneDescendenciaViva(Agen<informacion> &A, typename Agen<informacion>::nodo n)
{

    bool descendencia = false;

    if (n == A.NODO_NULO)
        return false;

    typename Agen<informacion>::nodo hijo = A.hijoIzqdo(n);

    while (hijo != A.NODO_NULO && !descendencia)
    {

        if (A.elemento(hijo).estado)
            return true;

        else if (A.hijoIzqdo(hijo) != A.NODO_NULO)
            descendencia |= tieneDescendenciaViva(A, A.hijoIzqdo(hijo));

        hijo = A.hermDrcho(hijo);
    }

    return descendencia;
}

void reparto(Agen<informacion> &A, typename Agen<informacion>::nodo n)
{

    if (n != A.NODO_NULO)
    {
        if (A.elemento(n).cantidad > 0)
        {

            // CUENTO LA DESCENCENDIA VIVA

            int vivos = 0;

            typename Agen<informacion>::nodo hijo = A.hijoIzqdo(n);

            while (hijo != A.NODO_NULO)
            {
                if (A.elemento(hijo).estado)
                    vivos++;
                else
                {
                    if (tieneDescendenciaViva(A, hijo))
                        vivos++;
                }

                hijo = A.hermDrcho(hijo);
            }

            int recibe;

            if (vivos > 0)
            {
                recibe = A.elemento(n).cantidad / vivos;
                A.elemento(n).cantidad = 0;
            }

            hijo = A.hijoIzqdo(n);
            while (hijo != A.NODO_NULO)
            {
                if (A.elemento(hijo).estado)
                {
                    A.elemento(hijo).cantidad = recibe;
                    reparto(A, hijo);
                }
                else
                {
                    if (tieneDescendenciaViva(A, hijo))
                    {
                        A.elemento(hijo).cantidad = recibe;
                        reparto(A, hijo);
                    }
                }

                hijo = A.hermDrcho(hijo);
            }
        }
    }
}