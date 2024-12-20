//---------------------------------------------------------------------------

#pragma hdrstop

#include "ConjuntoSM.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace UConjuntoSM
{
    using UCSMemoria::NULO;
    ConjuntoSM::ConjuntoSM()
    {
        PtrConj = NULO;
        mem     = new UCSMemoria::CSMemoria();
        cant    = 0;
    }

    ConjuntoSM::ConjuntoSM(UCSMemoria::CSMemoria* m)
    {
        PtrConj = UCSMemoria::NULO;
        mem     = m;
        cant    = 0;
    }

    // cantidad de elementos del conjunto
    int ConjuntoSM::cardinal()
    {
        return cant;
    }

    // esta vacio?
    bool ConjuntoSM::vacio()
    {
        return cant == 0; //|| PtrConj == UCSMemoria::NULO
    }

    // busca el lugar que ocupa el elemento E en el conjunto
    int ConjuntoSM::ordinal(int e)
    {
        int resp = 0;
        int pc   = PtrConj;
        while(pc != NULO)
        {
            resp++;
            if(mem->obtener_dato(pc, _dato) == e)
            {
                return resp;
            }
            pc = mem->obtener_dato(pc, _sig);
        }
        return NULO;
    }

    // inserta elementos en el conjunto
    void ConjuntoSM::inserta(int e)
    {
        if(!pertenece(e))
        {
            int dir = mem->new_espacio(_dato_sig);
            mem->poner_dato(dir, _dato, e);
            mem->poner_dato(dir, _sig, PtrConj);
            PtrConj = dir;
            cant++;
        }
        else
        {
            // error pertenece
        }
    }

    // elimna un elemento del conjunto
    void ConjuntoSM::suprime(int e)
    {
        if(!pertenece(e))
            return;

        int dir;
        if(mem->obtener_dato(PtrConj, _dato) == e)
        { // caso si esta en la cabeza
            dir     = PtrConj;
            PtrConj = mem->obtener_dato(PtrConj, _sig);
        }
        else
        {
            int pc = PtrConj;
            int ant;
            while(pc != NULO)
            {
                if(mem->obtener_dato(pc, _dato) == e)
                {
                    dir = pc;
                    break;
                }
                ant = pc;
                pc  = mem->obtener_dato(pc, _sig);
            }
            mem->poner_dato(ant, _sig, mem->obtener_dato(pc, _sig));
            mem->poner_dato(pc, _sig, NULO);
        }
        cant--;
        mem->delete_espacio(dir);
    }

    bool ConjuntoSM::pertenece(int e)
    {
        int pc = PtrConj;
        while(pc != NULO)
        {
            if(mem->obtener_dato(pc, _dato) == e)
            {
                return true;
            }
            pc = mem->obtener_dato(pc, _sig);
        }
        return false;
    }

    // busca un elemento al azar que pertenezca al conjunto
    int ConjuntoSM::muestrea()
    {
        if(vacio())
            return NULO;
        int i     = 0;
        int lugar = rand() % cardinal() + 1; // >= 1 && <= cant
        int pc    = PtrConj;
        while(pc != NULO)
        {
            i++;
            if(i == lugar)
            {
                return mem->obtener_dato(pc, _dato);
            }
            pc = mem->obtener_dato(pc, _sig);
        }
    }

    ConjuntoSM::~ConjuntoSM()
    {
        delete mem;
    }

    std::string ConjuntoSM::mostrar()
    {
        std::string s = "{";
        int x         = PtrConj;
        int i         = 0;
        while(x != NULO)
        {
            i++;
            s += std::to_string(mem->obtener_dato(x, _dato));
            s += i < cardinal() ? "," : "";
            x = mem->obtener_dato(x, _sig);
        }
        return s + "}";
    }

    void ConjuntoSM::_union(ConjuntoSM* a, ConjuntoSM* b, ConjuntoSM* c)
    {
        ConjuntoSM* aux = new ConjuntoSM;
        while(!a->vacio())
        {
            int m = a->muestrea();
            a->suprime(m);
            aux->inserta(m);
            c->inserta(m);
        }
        // while (!aux->vacio()) {
        //     int m = aux->muestrea();
        //     aux->suprime(m);
        //     a->inserta(m);
        // }
        while(!b->vacio())
        {
            int m = b->muestrea();
            b->suprime(m);
            aux->inserta(m);
            if(!c->pertenece(m))
                c->inserta(m);
        }
        // while (!aux->vacio()) {
        //     int m = aux->muestrea();
        //     aux->suprime(m);
        //     b->inserta(m);
        // }

        delete aux;
    };

    void ConjuntoSM::_interseccion(ConjuntoSM* a, ConjuntoSM* b, ConjuntoSM* c)
    {
        auto* aux = new ConjuntoSM;
        while(!a->vacio())
        {
            int m = a->muestrea();
            if(a->pertenece(m) && b->pertenece(m))
            {
                c->inserta(m);
            }
            a->suprime(m);
            aux->inserta(m);
        }

        while(!aux->vacio())
        {
            int m = aux->muestrea();
            aux->suprime(m);
            a->inserta(m);
        }

        delete aux;
    }

    bool ConjuntoSM::_equivalentes(ConjuntoSM* a, ConjuntoSM* b)
    {
        return a->cardinal() == b->cardinal();
    }
} // namespace UConjuntoSM