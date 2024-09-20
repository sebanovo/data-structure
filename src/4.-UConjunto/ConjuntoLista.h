//---------------------------------------------------------------------------

#ifndef ConjuntoListaH
#define ConjuntoListaH
//---------------------------------------------------------------------------
#include <iostream>
#include <string>

#include "2.-ULista/ListaSM.h"
#include "2.-ULista/ListaVector.h"

// Conjunto LISTA
// SOLO FUNCIONA PARA UNA (LISTA SM) Y (LISTA VECTOR)

namespace UConjuntoLista {
    class ConjuntoLista {
       private:
        // UListaVector::ListaVector* elem;
        UListaSM::ListaSM* elem;
        UCSMemoria::CSMemoria* mem;

       public:
        ConjuntoLista();
        ConjuntoLista(UCSMemoria::CSMemoria* m);
        int cardinal();
        bool vacio();
        int ordinal(int e);
        void inserta(int e);
        void suprime(int e);
        bool pertenece(int e);
        int muestrea();
        ~ConjuntoLista();
        std::string mostrar();
    };

    void _union();
    void _interseccion();
    void _equivalentes();

    void _union(ConjuntoLista* a, ConjuntoLista* b, ConjuntoLista* c);
    void _interseccion(ConjuntoLista* a, ConjuntoLista* b, ConjuntoLista* c);
    bool _equivalentes(ConjuntoLista* a, ConjuntoLista* b);
}  // namespace UConjuntoLista
#endif