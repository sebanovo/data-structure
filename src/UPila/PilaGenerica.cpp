//---------------------------------------------------------------------------

#pragma hdrstop

#include "PilaGenerica.h"
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <type_traits>

//---------------------------------------------------------------------------
#pragma package(smart_init)

// Añadir mas instancias si se lo desea
template class UPilaGenerica::PilaGenerica<int>;
template class UPilaGenerica::PilaGenerica<char>;
template class UPilaGenerica::PilaGenerica<std::string>;
template class UPilaGenerica::PilaGenerica<bool>;

namespace UPilaGenerica
{
    // Implementación de las funciones plantilla
    template <typename T>
    PilaGenerica<T>::PilaGenerica()
    {
        tope = 0;
        elementos = new T[MAX];
    }

    template <typename T>
    bool PilaGenerica<T>::vacia()
    {
        return tope == 0;
    }

    template <typename T>
    void PilaGenerica<T>::meter(T e)
    {
        if (tope >= MAX) return;
        tope++;
        elementos[tope] = e;
    }

    template <typename T>
    void PilaGenerica<T>::sacar(T& e)
    {
        if (vacia()) throw std::runtime_error("No hay elementos que sacar");
        e = elementos[tope];
        tope--;
    }

    template <typename T>
    T PilaGenerica<T>::cima()
    {
        if (vacia()) throw std::runtime_error("No hay elementos en la cima");
        return elementos[tope];
    }

    template <typename T>
    std::string PilaGenerica<T>::mostrar()
    {
        std::string s = "";
        PilaGenerica<T>aux;
        while (!vacia())
        {
            T e;
            sacar(e);
            // Usamos `if constexpr` para verificar el tipo en tiempo de compilación
            if constexpr (std::is_same<T, int>::value)
            {
                s += "| " + std::to_string(e) + " |\n";
            }
            else if constexpr (std::is_same<T, char>::value)
            {
                s += "| ";
                s += e;
                s += " |\n";
            }
            else if constexpr (std::is_same<T, std::string>::value)
            {
                s += "| " + e + " |\n";
            }
            else if constexpr (std::is_same<T, bool>::value)
            {
                s += "| ";
                s += e ? "true" : "false";
                s += " |\n";
            }
            else
            {
                // tipo no especificado
                s += "| Tipo no soportado |\n";
            }
            aux.meter(e);
        }
        while (!aux.vacia())
        {
            T e;
            aux.sacar(e);
            meter(e);
        }
        return s;
    }

    template <typename T>
    PilaGenerica<T>::~PilaGenerica()
    {
        delete[] elementos;
    }

    bool son_parentesis_validos(std::string expresionInfija)
    {
        int balance = 0;
        for (char c : expresionInfija)
        {
            if (c == '(')
                ++balance;
            else if (c == ')')
                --balance;
            if (balance < 0)
                return false;
        }
        if (balance != 0)
            return false;
        return true;
    }

    bool son_caracteres_validos(std::string expresionInfija) {
        std::string numeros =  "0123456789";
        std::string operadores =  "+-*/^";
        std::string parentesis =  "()";
        std::string punto = ".";
        std::string caracteresValidos = numeros + operadores + parentesis + punto;

        for(size_t i = 0; i < expresionInfija.length() ; i++) {
            if(caracteresValidos.find(expresionInfija[i]) == std::string::npos) return false;
        }
        return true;
    }

    double evaluar(double op1, double op2, char operacion)
    {
        switch (operacion)
        {
            case '+':
                return op2 + op1;
            case '-':
                return op2 - op1;
            case '*':
                return op2 * op1;
            case '/':
                return op2 / op1;
            case '^':
                return std::pow(op2, op1);
            default:
                throw std::invalid_argument("Operador inválido");
        }
    }

    int jerarquia(char operador)
    {
        switch (operador)
        {
            case '^':
                return 3;
            case '*':
            case '/':
                return 2;
            case '+':
            case '-':
                return 1;
            default:
                return 0;
        }
    }

    std::string infija_a_postfija(std::string expresionInfija)
    {
        if (expresionInfija.empty()) throw std::runtime_error("La expresión infija no puede ser vacía");
        if(!son_caracteres_validos(expresionInfija)) throw std::runtime_error("Caracteres de la expresion infija invalidos");
        if (!son_parentesis_validos(expresionInfija)) throw std::runtime_error("Paréntesis inválidos");

        PilaGenerica<char> pilaOp;
        std::string postfija;
        for (size_t i = 0; i < expresionInfija.length(); ++i)
        {
            char car = expresionInfija[i];
            // if (std::isdigit(car))
            // {
            //     postfija += car;
            //     while (i + 1 < expresionInfija.length() && std::isdigit(expresionInfija[i + 1]))
            //     {
            //         postfija += expresionInfija[++i];
            //     }
            //     postfija += ' ';
            // }
            if (std::isdigit(car) || car == '.')
            {
                postfija += car;

                bool decimalAdded = (car == '.');
                while (i + 1 < expresionInfija.length() && (std::isdigit(expresionInfija[i + 1]) || (!decimalAdded && expresionInfija[i + 1] == '.')))
                {
                    char nextChar = expresionInfija[++i];
                    if (nextChar == '.') decimalAdded = true;
                    postfija += nextChar;
                }
                postfija += ' ';
            }
            else if (jerarquia(car) > 0)
            {
                while (!pilaOp.vacia() && jerarquia(pilaOp.cima()) >= jerarquia(car))
                {
                    char operacion;
                    pilaOp.sacar(operacion);
                    postfija += operacion;
                    postfija += ' ';
                }
                pilaOp.meter(car);
            }
            else if (car == '(')
            {
                pilaOp.meter(car);
            }
            else if (car == ')')
            {
                while (!pilaOp.vacia() && pilaOp.cima() != '(')
                {
                    char op;
                    pilaOp.sacar(op);
                    postfija += op;
                    postfija += ' ';
                }
                char any;
                pilaOp.sacar(any);
            }
        }
        while (!pilaOp.vacia())
        {
            char op;
            pilaOp.sacar(op);
            postfija += op;
            postfija += ' ';
        }
        return postfija;
    }

    double evaluar_postfija(std::string postfija)
    {
        PilaGenerica<double> pila;
        std::istringstream tokens(postfija);
        std::string token;
        while (tokens >> token)
        {
            if (token.size() == 1 && jerarquia(token[0]) > 0)
            {
                double op1, op2;
                pila.sacar(op1);
                pila.sacar(op2);
                pila.meter(evaluar(op1, op2, token[0]));
            }
            else
            {
                pila.meter(std::stod(token));
            }
        }

        double resultado;
        pila.sacar(resultado);
        return resultado;
    }
}  // namespace UPilaGenerica
