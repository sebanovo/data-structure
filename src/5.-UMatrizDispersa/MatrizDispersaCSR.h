//---------------------------------------------------------------------------

#ifndef MatrizDispersaCSRH
#define MatrizDispersaCSRH
//---------------------------------------------------------------------------
#include <iostream>
#include <string>
namespace UMatrizDispersaCSR {
    class MatrizDispersaCSR {
       private:
        const int MAX = 1000;
        int *vf, *vc, *vd;  // filas, columnas, datos
        int df, dc, nt, repe;
        int buscar_posicion_vd(int f, int c);
        int donde_insertar(int f, int c);
        bool hay(int elemento);

       public:
        MatrizDispersaCSR();
        void dimensionar(int df, int dc);
        int dimension_fila();
        int dimension_columna();
        void poner(int f, int c, int elemento);
        int elemento(int f, int c);
        void definir_valor_repetido(int elemento);
        std::string mostrar();
        ~MatrizDispersaCSR();

        // void  traspuesta();
    };

    int suma(MatrizDispersaCSR *m);
}  // namespace UMatrizDispersaCSR

#endif