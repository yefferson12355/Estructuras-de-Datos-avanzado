#include <iostream>
using namespace std;

// --- CLASE NODO ---
class Nodo {
private:
    int dato;           
    Nodo* siguiente;    

public:
    // Constructor
    Nodo(int valor) {
        dato = valor;
        siguiente = nullptr;
    }

    // getters y setters
    int getDato() { 
        return dato; 
    }

    Nodo* getSiguiente() { 
        return siguiente; 
    }
    //set para modificar 
    void setSiguiente(Nodo* nuevoSiguiente) { 
        siguiente = nuevoSiguiente; 
    }
};

// --- CLASE LISTA ---
class Lista {
private:
    Nodo* inicio;

public:
    // Constructor
    Lista() {
        inicio = nullptr; 
    }

    // Destructor
    ~Lista() {
        Nodo* actual = inicio;
        while (actual != nullptr) {
        
            Nodo* siguienteTemp = actual->getSiguiente(); 
            
            delete actual;
            actual = siguienteTemp;
        }
    }

    // Insertar al Inicio
    void InsertarInicio(int valor) {
        Nodo* nuevo = new Nodo(valor);
        nuevo->setSiguiente(inicio); 
        
        inicio = nuevo; 
    }

    // Insertar al Final
    void InsertarFinal(int valor) {
        Nodo* nuevo = new Nodo(valor);
        // Si la lista está vacía, el nuevo nodo es el inicio
        if (inicio == nullptr) {
            inicio = nuevo;
            return;
        }
        // Si no está vacía, recorremos hasta el final
        Nodo* temporal = inicio;
        while (temporal->getSiguiente() != nullptr) { 
            temporal = temporal->getSiguiente(); 
        }

        // Enlazamos el último nodo con el nuevo nodo
        temporal->setSiguiente(nuevo); 
    }

    
    void InsertarPosicion(int valor, int posicion) {
        if (posicion <= 0 || inicio == nullptr) {
            InsertarInicio(valor);
            return;
        }

        Nodo* actual = inicio;
        int indice = 0;

        // Avanzamos hasta el nodo previo a la posicion deseada o hasta el ultimo
        while (actual->getSiguiente() != nullptr && indice < posicion - 1) {
            actual = actual->getSiguiente();
            indice++;
        }

        Nodo* nuevo = new Nodo(valor);
        nuevo->setSiguiente(actual->getSiguiente());
        actual->setSiguiente(nuevo);
    }
    void eliminarPosicion(int posicion) {
        if (inicio == nullptr || posicion < 0) {
            return; 
        }

        // Eliminar el primer nodo
        if (posicion == 0) {
            Nodo* a_eliminar = inicio;
            inicio = inicio->getSiguiente();
            delete a_eliminar;
            return;
        }

        Nodo* actual = inicio;
        int indice = 0;

        // Avanzamos hasta el nodo previo al que queremos eliminar
        while (actual->getSiguiente() != nullptr && indice < posicion - 1) {
            actual = actual->getSiguiente();
            indice++;
        }

        // Si la siguiente es nula, la posición es inválida
        if (actual->getSiguiente() == nullptr) {
            return; 
        }

        Nodo* a_eliminar = actual->getSiguiente();
        actual->setSiguiente(a_eliminar->getSiguiente());
        delete a_eliminar;
    }

    // Pop al inicio: elimina el primer nodo y devuelve su valor. Retorna false si la lista esta vacia.
    bool PopInicio(int& valor) {
        if (inicio == nullptr) {
            return false;
        }

        Nodo* eliminado = inicio;
        valor = eliminado->getDato();
        inicio = eliminado->getSiguiente();
        delete eliminado;
        return true;
    }

    // Mostrar 
    void Mostrar() {
        Nodo* actual = inicio;
        cout << "Lista: ";
        while (actual != nullptr) {
            // Usamos getDato() para leer el valor
            cout << "[" << actual->getDato() << "] -> ";
            actual = actual->getSiguiente();
        }
        cout << "null" << endl;
    }
};

int main() {
    Lista miLista;

    miLista.InsertarInicio(10);
    miLista.InsertarInicio(5);
    miLista.InsertarFinal(20);
    miLista.InsertarPosicion(15, 2); // posicion 2: despues de 10

    miLista.Mostrar(); // [5] -> [10] -> [15] -> [20] -> null

    int valor;
    if (miLista.PopInicio(valor)) {
        cout << "Pop al inicio: " << valor << endl;
    }

    miLista.Mostrar();

    return 0;
}