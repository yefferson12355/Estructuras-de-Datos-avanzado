
#include <iostream>
#include <cstdlib>
using namespace std;


class Nodo
{
public:
    int dato ;
    Nodo* siguiente;
    Nodo* anterior;

    // Constructor comenzando en nullptr
    Nodo( int valor ){
        dato = valor;
        siguiente = nullptr;
        anterior = nullptr;
    }
};
class Lista
{
private:
    Nodo* inicio; //puntero  donde comienza la lista
    Nodo* fin; 
public:
    Lista(){  // Constructor de lista vacia 
        inicio = nullptr;
        fin = nullptr;
    }

    ~Lista(){}  // Destructor de la lista

    //Metodo push al final
    void push( int valor ){
        Nodo* nuevo = new Nodo( valor ); // creamos nodo limpio 
        //si esta vacio 
        if ( inicio == nullptr){
            inicio = nuevo; // Empieza a recorrer desde el inicio
            fin = nuevo; // si es nuevo tambien es el fin
        }
        // si hay nodos 
        else{
            fin->siguiente = nuevo; // el siguiente del fin apunta al nuevo
            nuevo->anterior = fin; // el anterior del nuevo apunta al fin   
            fin = nuevo ; // el nuevo ahora es el fin
        }
    }
    // Insertar al INICIO
    void pushI(int valor) {
        Nodo* nuevo = new Nodo(valor);

        // CASO 1: Lista vacía
        if (inicio == nullptr) {
            inicio = nuevo;
            fin = nuevo; // Si es el primero, también es el último
        } 
        // CASO 2: Ya hay gente en la lista
        else {
            nuevo->siguiente = inicio; //  El nuevo agarra al viejo inicio
            inicio->anterior = nuevo;  //  El viejo inicio agarra al nuevo (hacia atrás)
            inicio = nuevo;            //  Movemos la etiqueta INICIO al nuevo
        }
    }
    void mostrar (){
        Nodo* actual = inicio; // puntero temporal para recorrer
        cout << "Lista: ";
        while (actual != nullptr) // mientras no sea nulo
        {   
           cout << "[" << actual->dato << "] <-> ";
              actual = actual->siguiente; // 
        }
        cout << "null" << endl;
    }
    //Eliminra el finl de la lista
    void pop_back(){
        if (inicio == nullptr ) return ; // lista vacia
        // 1. Guardamos el nodo a eliminar
        Nodo *temporal = fin;
        // 2. ¿Es el único nodo? 
        if (inicio == fin) {
            inicio = nullptr; //borramos referencias
            fin = nullptr;
        }
        // 3. ¿Hay más nodos? (Hacemos el paso atrás)
        else {
            fin = fin->anterior;       // Movemos la etiqueta FIN un paso atrás
            fin->siguiente = nullptr;  // Cortamos el enlace con el nodo viejo
        }
        delete temporal; // Liberamos la memoria del nodo eliminado
    }
    // Eliminar al INICIO (pop_front)
    void pop_front() {
        
        if (inicio == nullptr) return;
        Nodo* a_eliminar = inicio;

        // 3. Caso especial: ¿Es el único nodo?
        if (inicio == fin) {
            inicio = nullptr;
            fin = nullptr;
        } 
       
        else {
            // A) Movemos la etiqueta INICIO un paso adelante
            inicio = inicio->siguiente;

            // B) Al nuevo inicio le cortamos el brazo izquierdo (anterior)
            // Ya no debe apuntar al nodo viejo que vamos a matar.
            inicio->anterior = nullptr; 
        }

        // 5. Borramos de la memoria
        delete a_eliminar;
    }
};


int main()
{
    Lista Telefono; // Instancia de la lista
    
    // Insertamos al final (Cola)
    Telefono.push(10);
    Telefono.push(20);
    Telefono.mostrar(); // [10] <-> [20] <-> null

    // Insertamos al INICIO (Cabeza)
    Telefono.pushI(5);
    Telefono.mostrar(); // [5] <-> [10] <-> [20] <-> null

    // Borramos del FINAL
    Telefono.pop_back();
    Telefono.mostrar(); // [5] <-> [10] <-> null

    // Borramos del INICIO
    Telefono.pop_front();
    Telefono.mostrar(); // [10] <-> null

    Telefono.pop_front(); // Borramos el último que queda (10)
    Telefono.mostrar();   // null

    //detele
    return 0;
}