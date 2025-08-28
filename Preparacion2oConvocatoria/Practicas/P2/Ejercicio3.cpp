
#include <iostream>
#include <fstream>
#include "../Abin/aBinCelEnla.hpp"
#include "../Abin/abin_E-S.h"

struct aritmetica
{

    bool isOp;
    double num;
    char op;

    aritmetica(double n)
    {
        isOp = false;
        num = n;
        op = '\0';
    }

    aritmetica(char c)
    {
        isOp = true;
        num = 0;
        op = c;
    }
};

double realizarOp(const Abin<aritmetica> &A)
{
    return realizarOpRec(A, A.raiz());
}

double realizarOpRec(const Abin<aritmetica> &A, typename Abin<aritmetica>::nodo nA)
{

    if (!A.elemento(nA).isOp)
        return A.elemento(nA).num;

    switch (A.elemento(nA).op)
    {
    case '+':
        return realizarOpRec(A, A.hijoIzqdo(nA)) + realizarOpRec(A, A.hijoDrcho(nA));

    case '-':
        return realizarOpRec(A, A.hijoIzqdo(nA)) - realizarOpRec(A, A.hijoDrcho(nA));

    case '/':
        return realizarOpRec(A, A.hijoIzqdo(nA)) / realizarOpRec(A, A.hijoDrcho(nA));

    case '*':
        return realizarOpRec(A, A.hijoIzqdo(nA)) * realizarOpRec(A, A.hijoDrcho(nA));
    }
}