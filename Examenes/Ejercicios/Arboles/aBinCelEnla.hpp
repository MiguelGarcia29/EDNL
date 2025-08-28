#ifndef ABIN_CELENLA_H
#define ABIN_CELENLA_H
#include <cassert>
template <typename T>
class Abin
{
    struct celda; // declaraciÛn adelantada privada
public:
    typedef celda *nodo;
    static const nodo NODO_NULO;
    Abin(); // constructor
    void insertarRaiz(const T &e);
    void insertarHijoIzqdo(nodo n, const T &e);
    void insertarHijoDrcho(nodo n, const T &e);
    void eliminarHijoIzqdo(nodo n);
    void eliminarHijoDrcho(nodo n);
    void eliminarRaiz();
    bool vacio() const;
    const T &elemento(nodo n) const; // acceso a elto, lectura
    T &elemento(nodo n);             // acceso a elto, lectura/escritura
    nodo raiz() const;
    nodo padre(nodo n) const;
    nodo hijoIzqdo(nodo n) const;
    nodo hijoDrcho(nodo n) const;
    int profNodo(nodo n) const;
    int altArbolNodo(nodo n) const;
    Abin(const Abin<T> &a);               // ctor. de copia
    Abin<T> &operator=(const Abin<T> &A); // asig.de ·rboles
    ~Abin();                              // destructor
    
private:
    struct celda
    {
        T elto;
        nodo padre, hizq, hder;
        celda(const T &e, nodo p = NODO_NULO) : elto(e), padre(p),
                                                hizq(NODO_NULO), hder(NODO_NULO) {}
    };
    nodo r; // nodo raÌz del ·rbol
    void destruirNodos(nodo &n);
    nodo copiar(nodo n);
};


/* DefiniciÛn del nodo nulo */
template <typename T>
const typename Abin<T>::nodo Abin<T>::NODO_NULO(0);
/*--------------------------------------------------------*/
/* MÈtodos p˙blicos */
/*--------------------------------------------------------*/
template <typename T>
inline Abin<T>::Abin() : r(NODO_NULO) {}
template <typename T>
inline void Abin<T>::insertarRaiz(const T &e)
{
    assert(r == NODO_NULO); // £rbol vacÌo
    r = new celda(e);
}
template <typename T>
inline void Abin<T>::insertarHijoIzqdo(Abin<T>::nodo n, const T &e)
{
    assert(n != NODO_NULO);
    assert(n->hizq == NODO_NULO); // No existe hijo izqdo.
    n->hizq = new celda(e, n);
}
template <typename T>
inline void Abin<T>::insertarHijoDrcho(Abin<T>::nodo n, const T &e)
{
    assert(n != NODO_NULO);
    assert(n->hder == NODO_NULO); // No existe hijo drcho.
    n->hder = new celda(e, n);
}
template <typename T>
inline void Abin<T>::eliminarHijoIzqdo(Abin<T>::nodo n)
{
    assert(n != NODO_NULO);
    assert(n->hizq != NODO_NULO);        // Existe hijo izqdo.
    assert(n->hizq->hizq == NODO_NULO && // Hijo izqdo.
           n->hizq->hder == NODO_NULO);  // es hoja.
    delete n->hizq;
    n->hizq = NODO_NULO;
}

template <typename T>
inline void Abin<T>::eliminarHijoDrcho(Abin<T>::nodo n)
{
    assert(n != NODO_NULO);
    assert(n->hder != NODO_NULO);        // Existe hijo drcho.
    assert(n->hder->hizq == NODO_NULO && // Hijo drcho.
           n->hder->hder == NODO_NULO);  // es hoja
    delete n->hder;
    n->hder = NODO_NULO;
}
template <typename T>
inline void Abin<T>::eliminarRaiz()
{
    assert(r != NODO_NULO); // £rbol no vacÌo.
    assert(r->hizq == NODO_NULO &&
           r->hder == NODO_NULO); // La raÌz es hoja.
    delete r;
    r = NODO_NULO;
}
template <typename T>
inline bool Abin<T>::vacio() const
{
    return (r == NODO_NULO);
}
template <typename T>
inline const T &Abin<T>::elemento(Abin<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->elto;
}
template <typename T>
inline T &Abin<T>::elemento(Abin<T>::nodo n)
{
    assert(n != NODO_NULO);
    return n->elto;
}
template <typename T>
inline typename Abin<T>::nodo Abin<T>::raiz() const
{
    return r;
}
template <typename T>
inline
    typename Abin<T>::nodo
    Abin<T>::padre(Abin<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->padre;
}
template <typename T>
inline
    typename Abin<T>::nodo
    Abin<T>::hijoIzqdo(Abin<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->hizq;
}
template <typename T>
inline
    typename Abin<T>::nodo
    Abin<T>::hijoDrcho(Abin<T>::nodo n) const
{
    assert(n != NODO_NULO);
    return n->hder;
}
template <typename T>
inline Abin<T>::Abin(const Abin<T> &A)
{
    r = copiar(A.r); // Copiar raÌz y descendientes.
}
template <typename T>
Abin<T> &Abin<T>::operator=(const Abin<T> &A)
{
    if (this != &A) // Evitar autoasignaciÛn.
    {
        this->~Abin();   // Vaciar el ·rbol.
        r = copiar(A.r); // Copiar raÌz y descendientes.
    }
    return *this;
}
template <typename T>
inline Abin<T>::~Abin()
{
    destruirNodos(r); // Vaciar el ·rbol.
}
/*--------------------------------------------------------*/
/* MÈtodos privados */
/*--------------------------------------------------------*/
// Destruye un nodo y todos sus descendientes
template <typename T>
void Abin<T>::destruirNodos(Abin<T>::nodo &n)

{
    if (n != NODO_NULO)
    {
        destruirNodos(n->hizq);
        destruirNodos(n->hder);
        delete n;
        n = NODO_NULO;
    }
}
// Devuelve una copia de un nodo y todos sus descendientes
template <typename T>
typename Abin<T>::nodo Abin<T>::copiar(Abin<T>::nodo n)
{
    nodo m = NODO_NULO;
    if (n != NODO_NULO)
    {
        m = new celda(n->elto);    // Copiar n.
        m->hizq = copiar(n->hizq); // Copiar sub·rbol izqdo.
        if (m->hizq != NODO_NULO)
            m->hizq->padre = m;
        m->hder = copiar(n->hder); // Copiar sub·rbol drcho.
        if (m->hder != NODO_NULO)
            m->hder->padre = m;
    }
    return m;
}

template <typename T>
inline int Abin<T>::profNodo(nodo n) const
{
    int prof=0;
    while(n!=r){
        prof += 1;
        n = n->padre;
    }
    return prof;
}

template <typename T>
inline int Abin<T>::altArbolNodo(nodo n) const
{
    if(n==r){
        return 0;
    }
    else if(n==NODO_NULO){
        return -1;
    }else{
        return 1 + max(altArbolNodo(n->hizq),altArbolNodo(n->hder));
    }
}

#endif // ABIN_H