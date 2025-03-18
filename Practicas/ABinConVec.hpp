#ifndef ABIN_CONVEC_H
#define ABIN_CONVEC_H
#include <cassert>
#include <math.h>
#include <iostream>
using namespace std;

template <typename T>
class Abin
{
public:
    Abin(int t); // constructor
    void insertarRaiz(const T &n);
    const T &padre(const T &n) const;
    void insertarHijoIzqdo(const T &n, const T &pad);
    void insertarHijoDrcho(const T &n, const T &pad);
    void verVector() const;
    int obtenerP(const T &n);


private:
    T *vec;
    int tam_;
    int alturaArbol() const;
    int obtenerP_Rec(const T &n, int ini, int fin);
    int posN(const T &x);
};

template <typename T>
inline Abin<T>::Abin(int t) : tam_(t)
{
    vec = new T[tam_];
    for (int i = 0; i < tam_; ++i)
    {
        vec[i]='-';
    }
};

template <typename T>
inline void Abin<T>::insertarRaiz(const T &n)
{
    vec[tam_ / 2] = n;
};

template <typename T>
inline int Abin<T>::alturaArbol() const
{
    return log2(tam_ + 1) - 1;
};

template <typename T>
int Abin<T>::obtenerP(const T &c)
{

    return obtenerP_Rec(c, 0, tam_);
};

template <typename T>
inline int Abin<T>::obtenerP_Rec(const T &c, int ini, int fin)
{

    if (ini >= fin)
        return 0;
    int mid = ini + (fin - ini) / 2;
    if (c == vec[mid])
        return 0;

    return 1 + obtenerP_Rec(c, ini, mid - 1) + obtenerP_Rec(c, mid + 1, fin);
};

template <typename T>
inline void Abin<T>::insertarHijoIzqdo(const T &ins, const T &pad)
{
    int alt = alturaArbol();
    int prof = obtenerP(pad);
    int h = alt - prof;
    int pos = posN(pad) - pow(2, h - 1);
    vec[pos] = ins;
};

template <typename T>
inline void Abin<T>::insertarHijoDrcho(const T &ins, const T &pad)
{
    int h = alturaArbol() - obtenerP(pad);
    int pos = posN(pad) + pow(2, h - 1);
    vec[pos] = ins;
};

template <typename T>
inline const T &Abin<T>::padre(const T &n) const
{
    // compruebo si es hijo izq o derecho
    int h = alturaArbol() - obtenerP(n);
    if (posN(n) % pow(2, h + 2) == pow(2, h) - 1)
    {
        return vec[posN(n) + pow(2, h)];
    }
    else
    {
        return vec[posN(n) - pow(2, h)];
    }
};

template <typename T>
inline int Abin<T>::posN(const T &x)
{
    int pos = 0;
    bool encontrado = false;
    for (int i = 0; i < tam_ && !encontrado; ++i)
    {
        if (vec[i] == x)
        {
            pos = i;
            encontrado = true;
        }
    }

    return pos;
};

template <typename T>
inline void Abin<T>::verVector() const
{

    for (int i = 0; i < tam_; ++i)
    {
        cout << " " << vec[i];
    }
};

#endif // ABIN_H