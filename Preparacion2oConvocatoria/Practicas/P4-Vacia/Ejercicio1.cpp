#include "Abb.h"

template <typename T>
void eliminarRamaAbb(Abb<T> &A, T& e){

    Abb<T> obj = A.buscar(e);
    
    while (!A.buscar(e).vacio())
    {
        T elemnto;
        //VACIO PRIMERO EL HIJO IZQ
        if(!obj.izqdo().vacio())
            elemnto=obj.izqdo().elemento();
        else if(!obj.drcho().vacio())
            elemnto = obj.drcho().elemento();
        else 
            elemnto = obj.elemento();

        A.eliminar(elemnto);
    }
    

}

