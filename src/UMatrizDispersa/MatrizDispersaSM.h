//---------------------------------------------------------------------------

#ifndef MatrizDispersaSMH
#define MatrizDispersaSMH
//---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "UCSMemoria/CSMemoria.h"

namespace UMatrizDispersaSM
{

    using std::string;
    const string _fil_col_dato_sig = "fil,col,dato,sig";
    const string _fil = "->fil";
    const string _col = "->col";
    const string _dato = "->dato";
    const string _sig = "->sig";

    class MatrizDispersaSM
    {
        private:
        UCSMemoria::CSMemoria* mem;
        int PtrMatD, repe, df, dc, nt;
        int buscar(int f, int c);
        bool hay(int elemento);

        public:
        MatrizDispersaSM();
        MatrizDispersaSM(UCSMemoria::CSMemoria* m);
        void dimensionar(int f, int c);
        int dimension_fila();
        int dimension_columna();
        void poner(int f, int c, int elemento);
        int elemento(int f, int c);
        void definir_valor_repetido(int elemento);
        std::string mostrar();
        ~MatrizDispersaSM();

        // ejercicios
        static int suma(MatrizDispersaSM* m);
        static void transpuesta(MatrizDispersaSM* m, MatrizDispersaSM* m1);
        static bool es_simetrica(MatrizDispersaSM* m);
    };

    void resolverSudoku(MatrizDispersaSM* m);
    bool esSudoku(MatrizDispersaSM* m);
} // namespace UMatrizDispersaSM

#endif