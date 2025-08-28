#ifndef ABB_H
#define ABB_H
#include <cassert>
#include <utility> // swap
template <typename T>
class Abb
{
public:
    Abb();
    const Abb &buscar(const T &e) const;
    void insertar(const T &e);
    void eliminar(const T &e);
    bool vacio() const;
    const T &elemento() const;
    const Abb &izqdo() const;
    const Abb &drcho() const;
    Abb(const Abb &A);            // Ctor. de copia
    Abb &operator=(const Abb &A); // Asig. árboles
    ~Abb();

private:
    struct arbol
    {
        T elto;
        Abb izq, der;
        arbol(const arbol &a) = default;
        ~arbol() = default;
    };
    arbol *r; // Raíz del árbol
};
template <typename T>
inline Abb<T>::Abb() : r{nullptr} {}
template <typename T>
inline bool Abb<T>::vacio() const
{
    return r == nullptr;
}
template <typename T>
const Abb<T> &Abb<T>::buscar(const T &e) const
{
    if (vacio()) // No encontrado.
        return *this;
    else if (e < r->elto) // Buscar en subárbol izqdo.
        return r->izq.buscar(e);
    else if (r->elto < e) // Buscar en subárbol drcho.
        return r->der.buscar(e);
    else
        return *this; // Encontrado en la raíz.
}
template <typename T>
void Abb<T>::insertar(const T &e)
{
    if (vacio()) // Insertar en la raíz.
        r = new árbol{e};
    else if (e < r->elto) // Insertar en subárbol izqdo.
        r->izq.insertar(e);
    else if (r->elto < e) // Insertar en subárbol drcho.
        r->der.insertar(e);
}
template <typename T>
void Abb<T>::eliminar(const T &e)
{
    if (!vacio())
    {
        if (e < r->elto) // Eliminar del subárbol izqdo.
            r->izq.eliminar(e);
        else if (r->elto < e) // Eliminar del subárbol drcho.
            r->der.eliminar(e);
        else
        {                               // Eliminar la raíz.
            árbol *a;                   // Sustituto de la raíz.
            if (!r->izq.r && !r->der.r) // 1. La raíz es hoja.
                a = nullptr;
            else if (!r->der.r)
            { // 2. Raíz sólo tiene hijo izqdo.
                a = r->izq.r;
                r->izq.r = nullptr; // Descolgar el subárbol izqdo.
            }
            else if (!r->izq.r)
            { // 3. Raíz sólo tiene hijo drcho.
                a = r->der.r;
                r->der.r = nullptr; // Descolgar el subárbol drcho.
            }
            else
            { // 4. Raíz tiene dos hijos.
                // Buscar el mínimo del subárbol drcho. de la raíz.
                Abb *pMin = &r->der;
                while (pMin->r->izq.r != nullptr)
                    pMin = &pMin->r->izq;
                // Extraer el mínimo y sustituirlo por su hijo drcho.
                a = pMin->r;
                pMin->r = a->der.r;
                // Transferir al mínimo los subárboles de la raíz.
                a->izq.r = r->izq.r; // Colgar de *a los
                a->der.r = r->der.r; // subárboles de la raíz.
                r->izq.r = nullptr;  // Descolgarlos
                r->der.r = nullptr;  // de la raíz.
            }
            delete r; // Destruir la raíz.
            r = a;    // Sustituir la raíz eliminada.
        } // Eliminar la raíz.
    } // if (!vacio())
}
template <typename T>
inline const T &Abb<T>::elemento() const
{
    assert(!vacio());
    return r->elto;
}
template <typename T>
inline const Abb<T> &Abb<T>::izqdo() const
{
    assert(!vacio());
    return r->izq;
}
template <typename T>
inline const Abb<T> &Abb<T>::drcho() const
{
    assert(!vacio());
    return r->der;
}
template <typename T>
inline Abb<T>::Abb(const Abb<T> &A) : Abb{}
{
    if (!A.vacio())
        r = new árbol{*A.r}; // Copiar raíz y subárboles.
}
template <typename T>
inline Abb<T> &Abb<T>::operator=(const Abb<T> &A)
{
    Abb B{A};
    std::swap(r, B.r);
    return *this;
}
template <typename T>
Abb<T>::~Abb()
{
    delete r;    // Destruir raíz y subárboles con r->~arbol()
    r = nullptr; // El árbol queda vacío.
}
#endif // ABB_H