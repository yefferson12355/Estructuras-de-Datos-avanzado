#include <iostream>
#include <cstdlib> // Para system("cls") o system("clear")

using namespace std;

// --- CLASE NODO ---
class Nodo {
public:
    int dato;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(int valor) {
        dato = valor;
        siguiente = nullptr;
        anterior = nullptr;
    }
};

// --- CLASE LISTA (Base para la Pila) ---
class Lista {
private:
    Nodo* inicio;
    Nodo* fin;

public:
    Lista() { inicio = nullptr; fin = nullptr; }

    ~Lista() {
        while (inicio != nullptr) pop_front();
    }

    bool isEmpty() { return inicio == nullptr; }

    // Insertar al final
    void push_back(int valor) {
        Nodo* nuevo = new Nodo(valor);
        if (inicio == nullptr) {
            inicio = nuevo;
            fin = nuevo;
        } else {
            fin->siguiente = nuevo;
            nuevo->anterior = fin;
            fin = nuevo;
        }
    }

    // Sacar del final
    int pop_back() {
        if (inicio == nullptr) return -1;
        int valor = fin->dato;
        Nodo* temp = fin;
        if (inicio == fin) {
            inicio = nullptr;
            fin = nullptr;
        } else {
            fin = fin->anterior;
            fin->siguiente = nullptr;
        }
        delete temp;
        return valor;
    }

    // Sacar del inicio (Necesario para limpiar memoria en el destructor)
    int pop_front() { 
        if (inicio == nullptr) return -1;
        int valor = inicio->dato;
        Nodo* temp = inicio;
        if (inicio == fin) {
            inicio = nullptr;
            fin = nullptr;
        } else {
            inicio = inicio->siguiente;
            inicio->anterior = nullptr;
        }
        delete temp;
        return valor;
    }

    void mostrar() {
        if (inicio == nullptr) {
            cout << "   [ Vacia ]" << endl;
            return;
        }
        Nodo* actual = inicio;
        cout << "   Estado: ";
        while (actual != nullptr) {
            cout << "[" << actual->dato << "]";
            if (actual->siguiente != nullptr) cout << " <-> ";
            actual = actual->siguiente;
        }
        cout << endl;
    }
};

// --- CLASE PILA (LIFO: Last In, First Out) ---
class Pila {
private:
    Lista lista; 

public:
    // En una Pila, insertamos al final (push_back)
    void push(int valor) {
        lista.push_back(valor); 
    }

    // En una Pila, sacamos del final (pop_back) -> El último que entró
    int pop() {
        return lista.pop_back(); 
    }

    bool isEmpty() {
        return lista.isEmpty();
    }

    void mostrar() {
        cout << "\n   --- PILA ACTUAL ---" << endl;
        lista.mostrar();
        cout << "   -------------------" << endl;
    }
};

// --- MAIN INTERACTIVO ---
int main() {
    Pila miPila;
    int opcion, valor;

    do {
        // Mostramos la pila antes del menú para ver los cambios en tiempo real
        miPila.mostrar();

        cout << "\n   MENU DE LA PILA" << endl;
        cout << "   1. APILAR (Push)" << endl;
        cout << "   2. DESAPILAR (Pop)" << endl;
        cout << "   3. Salir" << endl;
        cout << "   Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: // APILAR
                cout << "   Ingrese numero a apilar: ";
                cin >> valor;
                miPila.push(valor);
                cout << "   -> Ok, apilado el " << valor << "." << endl;
                break;

            case 2: // DESAPILAR
                if (miPila.isEmpty()) {
                    cout << "   -> Error: La pila esta vacia." << endl;
                } else {
                    int sacado = miPila.pop();
                    cout << "   -> Ok, desapilado el numero: " << sacado << endl;
                }
                break;

            case 3: // SALIR
                cout << "   Saliendo..." << endl;
                break;

            default:
                cout << "   -> Opcion no valida." << endl;
                break;
        }
        
        cout << endl; // Espacio visual entre turnos

    } while (opcion != 3);

    return 0;
}