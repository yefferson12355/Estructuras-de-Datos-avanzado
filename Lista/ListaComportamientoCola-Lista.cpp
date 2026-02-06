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
            cout << "   [ Lista Vacia ]" << endl;
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

// --- MAIN INTERACTIVO ---
int main() {
    Lista miLista;
    int opcionPrincipal;
    int subOpcion;
    int valor;

    do {
        cout << "\n=======================================" << endl;
        cout << " MENU PRINCIPAL (Estructura Dinamica)" << endl;
        cout << "=======================================" << endl;
        cout << "1. Usar como PILA (LIFO)" << endl;
        cout << "2. Usar como COLA (FIFO)" << endl;
        cout << "3. Salir" << endl;
        cout << "Elige una opcion: ";
        cin >> opcionPrincipal;

        switch (opcionPrincipal) {
        
        // ================= CASO 1: SUB-MENU PILA =================
        case 1: 
            do {
                cout << "\n   --- MODO PILA (Tope es el final) ---" << endl;
                miLista.mostrar(); 
                cout << "   1. APILAR " << endl;
                cout << "   2. DESAPILAR " << endl;
                cout << "   3. Volver al menu principal" << endl;
                cout << "   Opcion: ";
                cin >> subOpcion;

                if (subOpcion == 1) {
                    cout << "   Ingrese numero a apilar: ";
                    cin >> valor;
                    miLista.push_back(valor); // Pila: entra al final
                    cout << "   -> Apilado " << valor << endl;
                } 
                else if (subOpcion == 2) {
                    if (miLista.isEmpty()) {
                        cout << "   -> Error: Pila vacia." << endl;
                    } else {
                        // Pila: sale del final (LIFO)
                        cout << "   -> Desapilado: " << miLista.pop_back() << endl;
                    }
                }

            } while (subOpcion != 3);
            break;

        // ================= CASO 2: SUB-MENU COLA =================
        case 2:
            do {
                cout << "\n   --- MODO COLA (Frente es el inicio) ---" << endl;
                miLista.mostrar();
                cout << "   1. ENCOLAR " << endl;
                cout << "   2. DESENCOLAR " << endl;
                cout << "   3. Volver al menu principal" << endl;
                cout << "   Opcion: ";
                cin >> subOpcion;

                if (subOpcion == 1) {
                    cout << "   Ingrese numero a formar: ";
                    cin >> valor;
                    miLista.push_back(valor); // Cola: entra al final
                    cout << "   -> Encolado " << valor << endl;
                } 
                else if (subOpcion == 2) {
                    if (miLista.isEmpty()) {
                        cout << "   -> Error: Cola vacia." << endl;
                    } else {
                        // Cola: sale del inicio (FIFO)
                        cout << "   -> Atendido: " << miLista.pop_front() << endl;
                    }
                }

            } while (subOpcion != 3);
            break;

        case 3:
            cout << "Saliendo del programa..." << endl;
            break;

        default:
            cout << "Opcion no valida." << endl;
        }

    } while (opcionPrincipal != 3);

    return 0;
}