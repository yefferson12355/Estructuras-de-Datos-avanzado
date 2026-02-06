#include "lista.h"
#include <algorithm> 

lista::lista() : inicio(nullptr), fin(nullptr) {}

lista::~lista() {
    while (inicio != nullptr) {
        pop_front();
    }
}

void lista::push_end(Contacto valor) {
    Nodo* nuevo = new Nodo(valor);
    if (!inicio) {
        inicio = fin = nuevo;
    } else {
        fin->siguiente = nuevo;
        nuevo->anterior = fin;
        fin = nuevo;
    }
}

void lista::push_front(Contacto valor) {
    Nodo* nuevo = new Nodo(valor);
    if (!inicio) {
        inicio = fin = nuevo;
    } else {
        nuevo->siguiente = inicio;
        inicio->anterior = nuevo;
        inicio = nuevo;
    }
}

void lista::pop_end() {
    if (!fin) return;
    Nodo* temp = fin;
    if (inicio == fin) {
        inicio = fin = nullptr;
    } else {
        fin = fin->anterior;
        fin->siguiente = nullptr;
    }
    delete temp;
}

void lista::pop_front() {
    if (!inicio) return;
    Nodo* temp = inicio;
    if (inicio == fin) {
        inicio = fin = nullptr;
    } else {
        inicio = inicio->siguiente;
        inicio->anterior = nullptr;
    }
    delete temp;
}

void lista::push_ordered(Contacto valor) {
    Nodo* nuevo = new Nodo(valor);
    if (!inicio) {
        inicio = fin = nuevo;
        return;
    }
    
    if (valor.paterno < inicio->dato.paterno) {
        nuevo->siguiente = inicio;
        inicio->anterior = nuevo;
        inicio = nuevo;
        return;
    }

    Nodo* actual = inicio;
    // Buscamos la posición
    while (actual->siguiente != nullptr && actual->siguiente->dato.paterno < valor.paterno) {
        actual = actual->siguiente;
    }

    nuevo->siguiente = actual->siguiente;
    nuevo->anterior = actual;

    if (actual->siguiente != nullptr) 
        actual->siguiente->anterior = nuevo;
    else 
        fin = nuevo;

    actual->siguiente = nuevo;
}

// --- NUEVO: Implementación de buscar ---
Contacto* lista::buscarPorId(int idBusqueda) {
    Nodo* actual = inicio;
    while (actual != nullptr) {
        if (actual->dato.id == idBusqueda) {
            return &actual->dato; // Retorna la dirección del contacto encontrado
        }
        actual = actual->siguiente;
    }
    return nullptr; // Retorna nulo si no lo encuentra
}

int lista::obtenerMayorId() {
    int maxId = 0;
    Nodo* actual = inicio;
    
    while (actual != nullptr) {
        if (actual->dato.id > maxId) {
            maxId = actual->dato.id;
        }
        actual = actual->siguiente;
    }
    return maxId; // Si la lista está vacía retorna 0
}

void lista::mostrar() {
    Nodo* actual = inicio;
    cout << "--- Lista de Contactos ---" << endl;
    while (actual) {
        cout << "ID: " << actual->dato.id 
             << " | " << actual->dato.nombres 
             << " " << actual->dato.paterno 
             << " " << actual->dato.materno
             << " | Tel: " << actual->dato.telefono 
             << " | Nac: " << actual->dato.FechaNacimiento << endl;
        actual = actual->siguiente;
    }
    cout << "--------------------------" << endl;
}