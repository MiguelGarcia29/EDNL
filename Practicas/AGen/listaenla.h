#ifndef LISTA_DOBLE_H
#define LISTA_DOBLE_H

#include <cstddef> // size_t
#include <utility> // swap
#include <cassert> // assert

template <typename T>
class Lista {
    struct nodo; // Declaración adelantada privada

public:
    typedef nodo* posicion; // Posición de un elemento

    Lista(); // Constructor por defecto
    bool vacia() const;
    size_t tama() const;
    void insertar(const T& x, posicion p); // Inserta un elemento
    void eliminar(posicion p); // Elimina un elemento
    const T& elemento(posicion p) const; // Lectura en lista constante
    T& elemento(posicion p); // Lectura/Escritura en lista no constante
    posicion siguiente(posicion p) const;
    posicion anterior(posicion p) const;
    posicion primera() const;
    posicion fin() const; // Posición después del último
    Lista(const Lista& Lis); // Constructor de copia
    Lista& operator=(const Lista& Lis); // Operador de asignación
    ~Lista(); // Destructor

private:
    struct nodo {
        T elto;
        nodo* ant;
        nodo* sig;
        nodo(const T& e = T(), nodo* a = nullptr, nodo* s = nullptr)
            : elto(e), ant(a), sig(s) {}
    };

    nodo* L; // Lista doblemente enlazada circular con cabecera
    size_t n; // Longitud de la lista
};

// Implementaciones

template <typename T>
inline Lista<T>::Lista()
    : L(new nodo), n(0) {
    L->ant = L->sig = L; // Estructura circular
}

template <typename T>
inline bool Lista<T>::vacia() const {
    return n == 0;
}

template <typename T>
inline size_t Lista<T>::tama() const {
    return n;
}

template <typename T>
inline void Lista<T>::insertar(const T& x, posicion p) {
    p->sig = p->sig->ant = new nodo(x, p, p->sig);
    ++n;
}

template <typename T>
inline void Lista<T>::eliminar(posicion p) {
    assert(p != fin());
    nodo* q = p->sig;
    p->sig = q->sig;
    p->sig->ant = p;
    delete q;
    --n;
}

template <typename T>
inline const T& Lista<T>::elemento(posicion p) const {
    assert(p != fin());
    return p->sig->elto;
}

template <typename T>
inline T& Lista<T>::elemento(posicion p) {
    assert(p != fin());
    return p->sig->elto;
}

template <typename T>
inline typename Lista<T>::posicion Lista<T>::siguiente(posicion p) const {
    assert(p != fin());
    return p->sig;
}

template <typename T>
inline typename Lista<T>::posicion Lista<T>::anterior(posicion p) const {
    assert(p != primera());
    return p->ant;
}

template <typename T>
inline typename Lista<T>::posicion Lista<T>::primera() const {
    return L;
}

template <typename T>
inline typename Lista<T>::posicion Lista<T>::fin() const {
    return L->ant;
}

// Constructor de copia
template <typename T>
Lista<T>::Lista(const Lista& Lis) : Lista() {
    if (!Lis.vacia()) {
        for (nodo* p = Lis.L->sig; p != Lis.L; p = p->sig)
            L->ant = L->ant->sig = new nodo(p->elto, L->ant, L);
        n = Lis.n;
    }
}

// Operador de asignación
template <typename T>
inline Lista<T>& Lista<T>::operator=(const Lista& Lis) {
    Lista L1(Lis);
    std::swap(L, L1.L);
    std::swap(n, L1.n);
    return *this;
}

// Destructor
template <typename T>
Lista<T>::~Lista() {
    nodo* p;
    while (L != L->sig) {
        p = L->sig;
        L->sig = p->sig;
        delete p;
    }
    delete L;
}

#endif // LISTA_DOBLE_H
