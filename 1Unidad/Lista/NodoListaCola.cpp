#include <iostream>
#include <cstdlib>
using namespace std;

// Nodo simple para la cola
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

// Lista que funciona como COLA (FIFO - First In First Out)
class ListaCola
{
private:
    Nodo* frente;  // Puntero al frente de la cola (donde se elimina)
    Nodo* final;   // Puntero al final de la cola (donde se agrega)

public:
    // Constructor - Cola vacía
    ListaCola() {
        frente = nullptr;
        final = nullptr;
    }

    // Destructor - Libera toda la memoria
    ~ListaCola() {
        while (frente != nullptr) {
            Nodo* temp = frente;
            frente = frente->siguiente;
            delete temp;
        }
    }

    // Verificar si la cola está vacía
    bool isEmpty() {
        return frente == nullptr;
    }

    // ENQUEUE/PUSH - Insertar elemento al FINAL de la cola
    void enqueue(int valor) {
        Nodo* nuevo = new Nodo(valor);

        // CASO 1: Cola vacía
        if (isEmpty()) {
            frente = nuevo;
            final = nuevo;
        }
        // CASO 2: Ya hay elementos
        else {
            final->siguiente = nuevo;  // El último actual apunta al nuevo
            final = nuevo;             // El nuevo ahora es el último
        }

        cout << "Elemento [" << valor << "] agregado al final de la cola" << endl;
    }

    // DEQUEUE/POP - Eliminar y retornar el elemento del FRENTE
    int dequeue() {
        // Verificar si la cola está vacía
        if (isEmpty()) {
            cout << "Error: Cola vacia, no se puede hacer DEQUEUE" << endl;
            return -1; // Valor de error
        }

        // Guardamos el nodo a eliminar
        Nodo* a_eliminar = frente;
        int valor = frente->dato;

        // Movemos el frente al siguiente
        frente = frente->siguiente;

        // Si la cola quedó vacía, actualizamos final también
        if (frente == nullptr) {
            final = nullptr;
        }

        // Liberamos memoria
        delete a_eliminar;

        cout << "Elemento [" << valor << "] eliminado del frente" << endl;
        return valor;
    }

    // FRONT/PEEK - Ver el elemento del FRENTE sin eliminarlo
    int front() {
        if (isEmpty()) {
            cout << "Error: Cola vacia" << endl;
            return -1;
        }
        return frente->dato;
    }

    // REAR - Ver el elemento del FINAL sin eliminarlo
    int rear() {
        if (isEmpty()) {
            cout << "Error: Cola vacia" << endl;
            return -1;
        }
        return final->dato;
    }

    // MOSTRAR - Visualizar toda la cola (de frente a final)
    void mostrar() {
        if (isEmpty()) {
            cout << "Cola: [vacia]" << endl;
            return;
        }

        Nodo* actual = frente;
        cout << "Cola (Frente -> Final): ";
        
        while (actual != nullptr) {
            cout << "[" << actual->dato << "]";
            if (actual->siguiente != nullptr) {
                cout << " -> ";
            }
            actual = actual->siguiente;
        }
        
        cout << endl;
    }

    // SIZE - Contar elementos
    int size() {
        int contador = 0;
        Nodo* actual = frente;
        
        while (actual != nullptr) {
            contador++;
            actual = actual->siguiente;
        }
        
        return contador;
    }
};

int main()
{
    ListaCola cola; // Crear cola vacía

    cout << "=== DEMOSTRACIÓN DE COLA (FIFO) ===" << endl << endl;

    // Verificar si está vacía
    cout << "¿Cola vacia? " << (cola.isEmpty() ? "Si" : "No") << endl << endl;

    // ENQUEUE - Agregar elementos
    cout << "--- AGREGANDO ELEMENTOS (ENQUEUE) ---" << endl;
    cola.enqueue(10);
    cola.enqueue(20);
    cola.enqueue(30);
    cola.enqueue(40);
    cola.mostrar();
    cout << endl;

    // FRONT y REAR - Ver frente y final sin eliminar
    cout << "--- VER FRENTE Y FINAL ---" << endl;
    cout << "Elemento al frente: " << cola.front() << endl;
    cout << "Elemento al final: " << cola.rear() << endl;
    cola.mostrar();
    cout << endl;

    // SIZE - Tamaño de la cola
    cout << "--- TAMAÑO DE LA COLA ---" << endl;
    cout << "Cantidad de elementos: " << cola.size() << endl << endl;

    // DEQUEUE - Eliminar elementos
    cout << "--- ELIMINANDO ELEMENTOS (DEQUEUE) ---" << endl;
    cola.dequeue(); // Elimina 10 (primero que entró)
    cola.mostrar();
    cout << endl;

    cola.dequeue(); // Elimina 20
    cola.mostrar();
    cout << endl;

    // Agregar más elementos
    cout << "--- AGREGANDO MÁS ELEMENTOS ---" << endl;
    cola.enqueue(50);
    cola.enqueue(60);
    cola.mostrar();
    cout << endl;

    // Ver frente y final actualizados
    cout << "--- ESTADO ACTUAL ---" << endl;
    cout << "Frente: " << cola.front() << endl;
    cout << "Final: " << cola.rear() << endl;
    cout << "Tamaño: " << cola.size() << endl;
    cola.mostrar();
    cout << endl;

    // Vaciar toda la cola
    cout << "--- VACIANDO LA COLA COMPLETAMENTE ---" << endl;
    while (!cola.isEmpty()) {
        cola.dequeue();
    }
    cola.mostrar();
    cout << endl;

    // Intentar DEQUEUE en cola vacía
    cout << "--- INTENTAR DEQUEUE EN COLA VACIA ---" << endl;
    cola.dequeue();

    return 0;
}
