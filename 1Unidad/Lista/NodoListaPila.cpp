#include <iostream>
#include <cstdlib>
using namespace std;

// Nodo simple para la pila
class Nodo
{
public:
    int dato;
    Nodo* siguiente;

    // Constructor
    Nodo(int valor) {
        dato = valor;
        siguiente = nullptr;
    }
};

// Lista que funciona como PILA
class ListaPila
{
private:
    Nodo* tope; // Puntero al tope de la pila

public:
    // Constructor - Pila vacía
    ListaPila() {
        tope = nullptr;
    }

    // Destructor - Libera toda la memoria
    ~ListaPila() {
        while (tope != nullptr) {
            Nodo* temp = tope;
            tope = tope->siguiente;
            delete temp;
        }
    }

    // Verificar si la pila está vacía
    bool isEmpty() {
        return tope == nullptr;
    }

    // PUSH - Insertar elemento al TOPE de la pila
    void push(int valor) {
        Nodo* nuevo = new Nodo(valor);
        
        // El nuevo nodo apunta al antiguo tope
        nuevo->siguiente = tope;
        
        // El nuevo nodo ahora es el tope
        tope = nuevo;
        
        cout << "Elemento [" << valor << "] agregado al tope" << endl;
    }

    // POP - Eliminar y retornar el elemento del TOPE
    int pop() {
        // Verificar si la pila está vacía
        if (isEmpty()) {
            cout << "Error: Pila vacia, no se puede hacer POP" << endl;
            return -1; // Valor de error
        }

        // Guardamos el nodo a eliminar
        Nodo* a_eliminar = tope;
        int valor = tope->dato;

        // Movemos el tope al siguiente
        tope = tope->siguiente;

        // Liberamos memoria
        delete a_eliminar;

        cout << "Elemento [" << valor << "] eliminado del tope" << endl;
        return valor;
    }

    // PEEK/TOP - Ver el elemento del TOPE sin eliminarlo
    int peek() {
        if (isEmpty()) {
            cout << "Error: Pila vacia" << endl;
            return -1;
        }
        return tope->dato;
    }

    // MOSTRAR - Visualizar toda la pila (de arriba hacia abajo)
    void mostrar() {
        if (isEmpty()) {
            cout << "Pila: [vacia]" << endl;
            return;
        }

        Nodo* actual = tope;
        cout << "Pila (Tope -> Base): ";
        
        while (actual != nullptr) {
            cout << "[" << actual->dato << "] -> ";
            actual = actual->siguiente;
        }
        
        cout << "null" << endl;
    }

    // SIZE - Contar elementos
    int size() {
        int contador = 0;
        Nodo* actual = tope;
        
        while (actual != nullptr) {
            contador++;
            actual = actual->siguiente;
        }
        
        return contador;
    }
};

int main()
{
    ListaPila pila; // Crear pila vacía

    cout << "=== DEMOSTRACIÓN DE PILA (LIFO) ===" << endl << endl;

    // Verificar si está vacía
    cout << "¿Pila vacia? " << (pila.isEmpty() ? "Si" : "No") << endl << endl;

    // PUSH - Agregar elementos
    cout << "--- AGREGANDO ELEMENTOS (PUSH) ---" << endl;
    pila.push(10);
    pila.push(20);
    pila.push(30);
    pila.push(40);
    pila.mostrar();
    cout << endl;

    // PEEK - Ver el tope sin eliminar
    cout << "--- VER TOPE (PEEK) ---" << endl;
    cout << "Elemento en el tope: " << pila.peek() << endl;
    pila.mostrar();
    cout << endl;

    // SIZE - Tamaño de la pila
    cout << "--- TAMAÑO DE LA PILA ---" << endl;
    cout << "Cantidad de elementos: " << pila.size() << endl << endl;

    // POP - Eliminar elementos
    cout << "--- ELIMINANDO ELEMENTOS (POP) ---" << endl;
    pila.pop(); // Elimina 40
    pila.mostrar();
    cout << endl;

    pila.pop(); // Elimina 30
    pila.mostrar();
    cout << endl;

    // Agregar más elementos
    cout << "--- AGREGANDO MÁS ELEMENTOS ---" << endl;
    pila.push(50);
    pila.push(60);
    pila.mostrar();
    cout << endl;

    // Vaciar toda la pila
    cout << "--- VACIANDO LA PILA COMPLETAMENTE ---" << endl;
    while (!pila.isEmpty()) {
        pila.pop();
    }
    pila.mostrar();
    cout << endl;

    // Intentar POP en pila vacía
    cout << "--- INTENTAR POP EN PILA VACIA ---" << endl;
    pila.pop();

    return 0;
}
