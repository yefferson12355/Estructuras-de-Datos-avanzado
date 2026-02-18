#include <iostream>

using namespace std;

// Nodo
class Nodo {
public:
    int dato;
    Nodo* siguiente; //mano del puntero 
    //Inicializacion del contructor
    Nodo(int valor) : dato(valor), siguiente(nullptr) {}
};

// 2. Definición de la Clase Pila
class Pila {
private:
    Nodo* cima; // Puntero ala cima

public:
    //constructor de Inicializacion de pila
    Pila() : cima(nullptr) {}

    // Insertar elemento 
    void push(int valor) {
        Nodo* nuevoNodo = new Nodo(valor); //Creamos nodo y apuntamos a el puntero temportal
        nuevoNodo->siguiente = cima; //siguiente nodo apunta ala cima 
        cima = nuevoNodo;// el nuevo nodo ahora es la cima, 
        cout << "Insertado: " << valor << endl;
    }

    // Eliminar elemento (Pop)
    void pop() {
        if (estaVacia()) {
            std::cout << "Error: La pila está vacía." << std::endl;
            return;
        }
        Nodo* temporal = cima;
        cima = cima->siguiente;
        delete temporal; // Liberar memoria
    }

    // Obtener el valor superior (Top)
    int obtenerCima() {
        if (estaVacia()) return -1; // O manejar excepción
        return cima->dato;
    }

    
    bool estaVacia() {
        return cima == nullptr;
    }
};

// 3. Uso en el Main
int main() {
    Pila miPila;

    miPila.push(10);
    miPila.push(25);
    miPila.push(50);

    cout << "La cima es  " << miPila.obtenerCima() << endl;

    miPila.pop();
    cout << "la cima es: " << miPila.obtenerCima() << endl;

    return 0;
}
