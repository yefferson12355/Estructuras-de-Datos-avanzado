#include<iostream>
#include<windows.h>
#include<string> 

using namespace std;

// --- 1. HERRAMIENTAS GLOBALES ---
void gotoxy(int x, int y) {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

// --- 2. ESTRUCTURA Y CLASE ---
struct Nodo {
    char dato; 
    Nodo* Hizquierdo;
    Nodo* Hderecho;
};

class ArbolBinario {
private:
    Nodo* raiz;
    void dibujarArbol(Nodo* n, int x, int y, int separacion);
    void Inorden(Nodo* n);
    void Postorden(Nodo* n);
    void Preorden(Nodo* n); 

public:
    ArbolBinario();
    ~ArbolBinario();
    
    void insertar(char valor);
    void eliminar(char valor);
    Nodo* buscar(char valor);

    void insertarFrase(string texto) {
        for(size_t i = 0; i < texto.length(); i++) {
            insertar(texto[i]); 
        }
    }

    void ver() {
        system("cls"); 
        cout << "=== VISTA GRAFICA ===" << endl;
        if(raiz == NULL) {
            cout << "\n(El arbol esta vacio)\n";
        } else {
            dibujarArbol(raiz, 50, 4, 24); 
        }
        gotoxy(0, 22); 
    }

    void mostrarInorden()   { if(raiz){ Inorden(raiz); } else { cout << "(Vacio)"; } cout << endl; }
    void mostrarPreorden()  { if(raiz){ Preorden(raiz); } else { cout << "(Vacio)"; } cout << endl; }
    void mostrarPostorden() { if(raiz){ Postorden(raiz); } else { cout << "(Vacio)"; } cout << endl; }

    // --- CORRECCIÓN AQUÍ: Quitamos 'ArbolBinario::' ---
    void buscarConDetalles(char valor) {
        Nodo* tmp = raiz;
        int nivel = 1; 
        bool encontrado = false;

        cout << "\n--- RASTREANDO LA LETRA '" << valor << "' ---" << endl;

        if (raiz == NULL) {
            cout << "[!] El arbol esta vacio. No hay nada que buscar." << endl;
            return;
        }

        while (tmp != NULL) {
            cout << "  > Visitando Nivel " << nivel << ": [" << tmp->dato << "]" << endl;

            if (tmp->dato == valor) {
                cout << "\n[OK] ENCONTRADO!" << endl;
                cout << "     - Ubicacion: Nivel " << nivel << endl;
                cout << "     - Direccion Memoria: " << tmp << endl; 
                encontrado = true;
                return; 
            }
            else if (valor < tmp->dato) {
                cout << "     ... '" << valor << "' es MENOR que '" << tmp->dato << "'. Bajando a la IZQUIERDA." << endl;
                tmp = tmp->Hizquierdo;
            }
            else {
                cout << "     ... '" << valor << "' es MAYOR que '" << tmp->dato << "'. Bajando a la DERECHA." << endl;
                tmp = tmp->Hderecho;
            }
            nivel++; 
        }

        if (!encontrado) {
            cout << "\n[X] NO ENCONTRADO." << endl;
            cout << "    Llegamos hasta el nivel " << nivel - 1 << " y se acabo el camino." << endl;
        }
    }
};

// --- 3. IMPLEMENTACIÓN ---

ArbolBinario::ArbolBinario() { raiz = NULL; }
ArbolBinario::~ArbolBinario() { }

void ArbolBinario::insertar(char valor) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;
    nuevo->Hizquierdo = NULL; nuevo->Hderecho = NULL;
     
    if (raiz == NULL) raiz = nuevo;
    else {
        Nodo* tmp = raiz; 
        Nodo* padre; 
        while (true) {
            padre = tmp; 
            if (valor < tmp->dato) {
                tmp = tmp->Hizquierdo; 
                if (tmp == NULL) { padre->Hizquierdo = nuevo; break; }
            } else {
                tmp = tmp->Hderecho; 
                if(tmp == NULL) { padre->Hderecho = nuevo; break; }
            }
        }
    }
}

void ArbolBinario::dibujarArbol(Nodo* n, int x, int y, int separacion) {
    if (n == NULL) return;
    gotoxy(x, y); cout << n->dato;

    int mitad = separacion / 2;
    if (mitad < 4) mitad = 4; 

    if(n->Hizquierdo) {
        gotoxy(x - mitad, y + 1); cout << "/"; 
        dibujarArbol(n->Hizquierdo, x - separacion, y + 3, mitad);
    }
    if(n->Hderecho) {
        gotoxy(x + mitad, y + 1); cout << "\\"; 
        dibujarArbol(n->Hderecho, x + separacion, y + 3, mitad);
    }
}

void ArbolBinario::Inorden(Nodo* n) { 
    if(n){ Inorden(n->Hizquierdo); cout << n->dato << " "; Inorden(n->Hderecho); }
}
void ArbolBinario::Preorden(Nodo* n) { 
    if(n){ cout << n->dato << " "; Preorden(n->Hizquierdo); Preorden(n->Hderecho); }
}
void ArbolBinario::Postorden(Nodo* n) { 
    if(n){ Postorden(n->Hizquierdo); Postorden(n->Hderecho); cout << n->dato << " "; }
}

Nodo* ArbolBinario::buscar(char valor) {
    Nodo* tmp = raiz;
    while (tmp != NULL) {
        if (tmp->dato == valor) return tmp;
        else if (valor < tmp->dato) tmp = tmp->Hizquierdo;
        else tmp = tmp->Hderecho;
    }
    return NULL;
}

void ArbolBinario::eliminar(char valor) {
    if (raiz == NULL) return;
    Nodo* padre = NULL;
    Nodo* actual = raiz;
    while (actual != NULL && actual->dato != valor) {
        padre = actual;
        if (valor < actual->dato) actual = actual->Hizquierdo;
        else actual = actual->Hderecho;
    }
    if (actual == NULL) return;

    if (actual->Hizquierdo != NULL && actual->Hderecho != NULL) {
        Nodo* sucesorPadre = actual;
        Nodo* sucesor = actual->Hderecho;
        while (sucesor->Hizquierdo != NULL) {
            sucesorPadre = sucesor;
            sucesor = sucesor->Hizquierdo;
        }
        actual->dato = sucesor->dato;
        actual = sucesor;
        padre = sucesorPadre;
    }
    Nodo* hijo;
    if (actual->Hizquierdo != NULL) hijo = actual->Hizquierdo;
    else hijo = actual->Hderecho;

    if (padre == NULL) raiz = hijo;
    else if (padre->Hizquierdo == actual) padre->Hizquierdo = hijo;
    else padre->Hderecho = hijo;
    delete actual;
}

// --- 4. MENU PRINCIPAL ---

int main() {
    ArbolBinario arbol;
    int opcion;
    char letra;
    string palabra; 

    do {
        system("cls"); 
        cout << "==================================" << endl;
        cout << "    ENCRIPTADOR ARBOL BINARIO     " << endl;
        cout << "==================================" << endl;
        cout << "1. Insertar PALABRA completa" << endl;
        cout << "2. Insertar letra unica" << endl;
        cout << "3. Ver Arbol (Grafico)" << endl;
        cout << "4. Buscar letra (Rastreo)" << endl;
        cout << "5. Eliminar letra" << endl;
        cout << "6. Ver mensaje oculto (Recorridos)" << endl;
        cout << "7. Salir" << endl;
        cout << "==================================" << endl;
        cout << "Opcion: ";
        
        cin >> opcion;

        if(cin.fail()) {
            cin.clear(); cin.ignore(10000, '\n'); opcion = -1;
        }

        switch(opcion) {
            case 1:
                cout << "\nEscribe la palabra (HOLA): ";
                cin >> palabra; 
                arbol.insertarFrase(palabra); 
                cout << ">> Palabra insertada." << endl;
                break;

            case 2:
                cout << "\nIngrese la letra: ";
                cin >> letra;
                arbol.insertar(letra);
                break;

            case 3:
                arbol.ver();
                cout << "\n(Enter para volver)";
                cin.ignore(); cin.get();
                break;

            case 4:
                cout << "\nIngrese la letra a rastrear: "; 
                cin >> letra;
                arbol.buscarConDetalles(letra);
                break;

            case 5:
                cout << "\nEliminar letra: "; cin >> letra;
                arbol.eliminar(letra);
                cout << ">> Eliminada." << endl;
                break;

            case 6:
                cout << "\n--- MENSAJES OCULTOS ---" << endl;
                cout << "Inorden (Alfabetico): "; arbol.mostrarInorden();
                cout << "Preorden (Raiz 1ro):  "; arbol.mostrarPreorden();
                cout << "Postorden (Original): "; arbol.mostrarPostorden();
                break;
            
            case 7: cout << "Saliendo..." << endl; break;
            default: cout << "Opcion no valida." << endl;
        }

        if(opcion != 3 && opcion != 7) {
            cout << "\nPause..."; cin.ignore(); cin.get();
        }

    } while (opcion != 7);

    return 0;
}