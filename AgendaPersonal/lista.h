#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include <string>

using namespace std;

// Estructura pura en C++
struct Contacto {
    int id;
    string paterno;
    string materno;
    string nombres;
    string telefono;
    string correo;
    string direccion;
    int edad;
    string FechaNacimiento; 
    int id_padre;
    int id_madre;
};

class lista {
public: // <--- CAMBIO IMPORTANTE: Nodo debe ser público para que el Backend lo pueda leer
    struct Nodo {
        Contacto dato;
        Nodo* siguiente;
        Nodo* anterior;
        Nodo(Contacto valor) : dato(valor), siguiente(nullptr), anterior(nullptr) {}
    };

private:
    Nodo* inicio;
    Nodo* fin;

public:
    lista();
    ~lista();

    void push_end(Contacto valor);
    void push_front(Contacto valor);
    void pop_end();
    void pop_front();
    void mostrar();
    void push_ordered(Contacto valor);
    
    int obtenerMayorId();
    // Ahora sí funcionará porque Nodo es público
    Nodo* getInicio() { return inicio; }
    Contacto* buscarPorId(int idBusqueda);
};

#endif // LISTA_H