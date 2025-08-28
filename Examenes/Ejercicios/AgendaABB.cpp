#include "Arboles/Abb.h"
#include <string>

class Persona
{
public:
    Persona(std::string n_, std::string telf) : nombre(n_), telefono(telf) {};

    bool operator<(const Persona &p)
    {
        return nombre < p.nombre;
    };

    std::string nombre, telefono;
};

class Agenda
{
public:
    void insertarPersona(const Persona &p)
    {
        agenda.insertar(p);
    }

    void eliminarPersona(const Persona &p)
    {
        agenda.eliminar(p);
    }

    const std::string &getTlf(std::string nomb) const
    {
        Abb<Persona> t = agenda.buscar(Persona(nomb, ""));
        return t.elemento().telefono;
    }

    const std::string &getNombre(std::string tlf) const
    {
        return getNombre_rec(tlf, agenda);
    }

    const std::string &getNombre_rec(std::string tlf, const Abb<Persona> &A) const
    {
        if (!agenda.vacio())
        {

            return getNombre_rec(tlf, A.izqdo()) + getNombre_rec(tlf, A.drcho());
        }

        return "";
    }

private:
    Abb<Persona> agenda;
};