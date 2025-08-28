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
    int obtenerP(int pos);

private:
    T *vec;
    int tam_;
    int alturaArbol() const;
    int posN(const T &c);
};

template <typename T>
inline Abin<T>::Abin(int t) : tam_(t)
{
    vec = new T[tam_];
    for (int i = 0; i < tam_; ++i)
    {
        vec[i] = '-';
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

//PROMT DE CHATGPT: dado un numero i tienes que hacer un programa que cree un vector de 0 a un tamaño dado y cuente cuantas iteraciones necesitaria de manera bicotomica para encontrar ese numeros
template <typename T>
int Abin<T>::obtenerP(int i)
{
    int size = tam_;
    int left = 0, right = size - 1;
    int iterations = -1; //PARA QUE EL RAIZ SEA PROF 0

    while (left <= right)
    {
        iterations++;
        int mid = left + (right - left) / 2;

        if (mid == i)
        {
            return iterations;
        }
        else if (mid > i)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    return iterations; // No debería ocurrir en este caso
};

template <typename T>
inline void Abin<T>::insertarHijoIzqdo(const T &ins, const T &pad)
{
    int alt = alturaArbol();
    int posPad = posN(pad);
    int prof = obtenerP(posPad);
    int h = alt - prof;
    int pos = posPad - pow(2, h - 1);
    vec[pos] = ins;
};

template <typename T>
inline void Abin<T>::insertarHijoDrcho(const T &ins, const T &pad)
{
    int posPad = posN(pad);
    int h = alturaArbol() - obtenerP(posPad);
    int pos = posPad + pow(2, h - 1);
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