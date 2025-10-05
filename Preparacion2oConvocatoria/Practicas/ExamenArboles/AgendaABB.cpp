#include "../Abb/Abb.h"
#include "string"

struct Persona
{
    std::string nombre, tlfono;

    Persona(std::string n, std::string t) : nombre(n), tlfono(t) {};

    bool operator<(Persona p) { return nombre < p.nombre; };
};

class Agenda
{

    Abb<Persona> personas;

    void insertarPersona(Persona &p)
    {
        personas.insertar(p);
    }

    void eliminarPersona(Persona &p)
    {
        personas.eliminar(p);
    }

    const std::string getTlefono(std::string nombre)
    {
        return personas.buscar(Persona(nombre, "")).elemento().nombre;
    }

    void getPersona(std::string tlefono, const Abb<Persona> &A, Persona &p)
    {

        if (!A.vacio())
        {

            if (A.elemento().tlfono == tlefono)
                p = A.elemento();
            else{
                getPersona(tlefono,A.izqdo(),p);
                getPersona(tlefono,A.drcho(),p);
            }
        }
    }


};