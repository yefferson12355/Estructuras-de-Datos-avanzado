#include <iostream>
#include <cstdlib> 

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

// --- CLASE LISTA ---
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

    // Sacar del final (No se usa en la Cola, pero queda en la lista base)
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

    // Sacar del inicio (ESTE LO USAREMOS PARA EL POP DE LA COLA)
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

// --- CLASE COLA (FIFO) ---
class Cola {
private:
    Lista lista; 

public:
    // INSERTAR: Entra al final de la fila
    void insertar(int valor) {
        lista.push_back(valor); 
    }

    // POP: Sale el primero de la fila (el de adelante)
    int pop() {
        return lista.pop_front(); 
    }

    bool isEmpty() {
        return lista.isEmpty();
    }

    void mostrar() {
        cout << "\n   --- COLA ACTUAL ---" << endl;
        lista.mostrar();
        cout << "   -------------------" << endl;
    }
};

// --- MAIN INTERACTIVO ---
int main() {
    Cola miCola;
    int opcion, valor;

    do {
        // Mostrar estado
        miCola.mostrar();

        cout << "\n   MENU DE LA COLA" << endl;
        cout << "   1. INSERTAR" << endl;
        cout << "   2. POP (Sacar)" << endl;
        cout << "   3. Salir" << endl;
        cout << "   Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: // INSERTAR
                cout << "   Ingrese numero a insertar: ";
                cin >> valor;
                miCola.insertar(valor);
                cout << "   -> Insertado el " << valor << "." << endl;
                break;

            case 2: // POP
                if (miCola.isEmpty()) {
                    cout << "   -> Error: La cola esta vacia." << endl;
                } else {
                    int sacado = miCola.pop();
                    cout << "   -> Pop (sacado): " << sacado << endl;
                }
                break;

            case 3: // SALIR
                cout << "   Saliendo..." << endl;
                break;

            default:
                cout << "   -> Opcion no valida." << endl;
                break;
        }
        
        cout << endl; 

    } while (opcion != 3);

    return 0;
}