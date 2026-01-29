#include<iostream>
#include<windows.h>

using namespace std;

//Funcion global para mover el cursor en la consola

void gotoxy(int x, int y) {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

struct Nodo
{
    /* data */
    int dato;
    Nodo* Hizquierdo;
    Nodo* Hderecho;
};

class ArbolBinario
{
private:
    /* data */
    Nodo* raiz;
    void dibujarArbol(Nodo* n, int x, int y, int separacion);
public:
    ArbolBinario(/* args */);
    ~ArbolBinario();
    //Metodos para insertar, recorrer, eliminar, buscar, Preorden ,  Inorden, Postorden,imprimir
    void insertar(int valor);
    void eliminar(int valor);
    Nodo* buscar(int valor);
    //Busquedas
    void Inorden(Nodo* raiz);
    void Postorden(Nodo* raiz);
    void Preorden(Nodo* raiz);  
    void ver() 
    {
        system("cls"); 
        cout << "--- TU ARBOL JERARQUICO ---\n\n";

        // X=50 (Centro), Y=3 (Arriba), Separación Inicial=24 (Muy ancha)
        dibujarArbol(raiz, 50, 3, 24); 
        
        // Bajar mucho el cursor al final
        gotoxy(0, 20); 
    }
    // Funciones para mostrar los recorridos
    void mostrarInorden()   { Inorden(raiz); cout << endl; }
    void mostrarPreorden()  { Preorden(raiz); cout << endl; }
    void mostrarPostorden() { Postorden(raiz); cout << endl; }
    };

ArbolBinario::ArbolBinario(/* args */)
{
    raiz = NULL;
}

ArbolBinario::~ArbolBinario()
{
    //Borrar consola completo con delete

}
void ArbolBinario::insertar(int valor)
{
    // Creamos la structura Nodo para el nuevo valor
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;
    nuevo->Hizquierdo = NULL;
    nuevo->Hderecho = NULL;
     
    //si el arbol esta vacio
    if (raiz == NULL){
        raiz = nuevo;
    }
    else
    {
        Nodo* tmp = raiz; // Nodo temporal para recorrer el arbol
        Nodo* padre; // Nodo padre para enlazar el nuevo nodo

        while (true) // Bucle infinito hasta encontrar el lugar
        {
            padre = tmp; // Guardamos el nodo actual como padre
            //2. Comparamos el valor a insertar con el nodo actual
            //3. Decidimos si ir a la izquierda o a la derecha

            //menor o igual va a la izquierda 
            if (valor < tmp->dato) // es menor?
            {
                tmp = tmp->Hizquierdo; 
                //si es NULL, encontramos el lugar
                if (tmp == NULL) 
                {
                    padre->Hizquierdo = nuevo;//enlazamos el nuevo nodo 
                    break; 
                }
            }
            //Es mayor va a la derecha
            else
            {
                tmp = tmp->Hderecho; // temporal se mueve a la derecha
                //si es NULL, encontramos el lugar
                if(tmp == NULL) 
                {
                    padre->Hderecho = nuevo; //enlazamos el nuevo nodo 
                    break; 
                }
            }


        }
    }
}
// ESTA ES LA FUNCION NUEVA PARA COPIAR ABAJO
void ArbolBinario::dibujarArbol(Nodo* n, int x, int y, int separacion)
{
    if (n == NULL) return;

    // 1. Imprimir el dato
    gotoxy(x, y);
    cout << n->dato;

    // --- TRUCO: Calcular la separación para el SIGUIENTE nivel ---
    // Dividimos entre 2, pero si baja de 6, lo dejamos en 6 para que no se peguen
    int nuevaSeparacion = separacion / 2;
    if (nuevaSeparacion < 6) nuevaSeparacion = 6;

    // 2. Dibujar ramitas e hijos
    
    // IZQUIERDA
    if(n->Hizquierdo != NULL) {
        // Dibujar la rayita un poco antes
        gotoxy(x - separacion/2, y + 1); 
        cout << "/";
        // Ir al hijo izquierdo
        dibujarArbol(n->Hizquierdo, x - separacion/2 - 2, y + 2, nuevaSeparacion);
    }

    // DERECHA
    if(n->Hderecho != NULL) {
        // Dibujar la rayita un poco después
        gotoxy(x + separacion/2, y + 1); 
        cout << "\\";
        // Ir al hijo derecho
        dibujarArbol(n->Hderecho, x + separacion/2 + 2, y + 2, nuevaSeparacion);
    }
}
Nodo* ArbolBinario::buscar(int valor)
{
    Nodo* tmp = raiz;

    while (tmp != NULL)
    {
        if (tmp->dato == valor)
        {
            return tmp; // ¡Lo encontramos!
        }
        else if (valor < tmp->dato)
        {
            tmp = tmp->Hizquierdo; // Buscamos a la izquierda
        }
        else
        {
            tmp = tmp->Hderecho; // Buscamos a la derecha
        }
    }
    return NULL; // No se encontró
}
// Preorden: Raíz -> Izquierda -> Derecha
void ArbolBinario::Preorden(Nodo* n)
{
    if (n == NULL) return;

    cout << n->dato << " ";     // 1. Imprimir
    Preorden(n->Hizquierdo);    // 2. Izquierda
    Preorden(n->Hderecho);      // 3. Derecha
}

// Inorden: Izquierda -> Raíz -> Derecha (Ordenado)
void ArbolBinario::Inorden(Nodo* n)
{
    if (n == NULL) return;

    Inorden(n->Hizquierdo);     // 1. Izquierda
    cout << n->dato << " ";     // 2. Imprimir
    Inorden(n->Hderecho);       // 3. Derecha
}

// Postorden: Izquierda -> Derecha -> Raíz
void ArbolBinario::Postorden(Nodo* n)
{
    if (n == NULL) return;

    Postorden(n->Hizquierdo);   // 1. Izquierda
    Postorden(n->Hderecho);     // 2. Derecha
    cout << n->dato << " ";     // 3. Imprimir
}
void ArbolBinario::eliminar(int valor)
{
    if (raiz == NULL) return;

    Nodo* padre = NULL;
    Nodo* actual = raiz;

    // 1. Buscar el nodo a eliminar y su padre
    while (actual != NULL && actual->dato != valor)
    {
        padre = actual;
        if (valor < actual->dato)
            actual = actual->Hizquierdo;
        else
            actual = actual->Hderecho;
    }

    // Si no lo encontramos, salimos
    if (actual == NULL) return;

    // 2.-El nodo tiene DOS hijos
    //  Reemplazarlo por el más pequeño del lado derecho
    if (actual->Hizquierdo != NULL && actual->Hderecho != NULL)
    {
        Nodo* sucesorPadre = actual;
        Nodo* sucesor = actual->Hderecho;

        // Buscamos el menor a la izquierda del subárbol derecho
        while (sucesor->Hizquierdo != NULL)
        {
            sucesorPadre = sucesor;
            sucesor = sucesor->Hizquierdo;
        }

        // Copiamos el valor del sucesor al nodo actual
        actual->dato = sucesor->dato;

        // Ahora eliminamos el sucesor
        actual = sucesor;
        padre = sucesorPadre;
    }

    // 3.- El nodo tiene 0 o 1 hijo
    // Vemos cuál es el hijo único (o NULL si no tiene)
    Nodo* hijo;
    if (actual->Hizquierdo != NULL)
        hijo = actual->Hizquierdo;
    else
        hijo = actual->Hderecho;

    // Conectamos el padre con el hijo (saltándonos el actual)
    if (padre == NULL)
    {
        raiz = hijo; // Si borramos la raíz
    }
    else if (padre->Hizquierdo == actual)
    {
        padre->Hizquierdo = hijo;
    }
    else
    {
        padre->Hderecho = hijo;
    }

    delete actual; // Borramos la memoria
}


//EJEMPLO MAIN 
int main() {
    ArbolBinario arbol;

    // Prueba tu insertar
    arbol.insertar(10); 
    arbol.insertar(5);
    arbol.insertar(15);
    arbol.insertar(3);
    arbol.insertar(7);
    arbol.insertar(12);
    arbol.insertar(18);
    arbol.insertar(1);
    arbol.insertar(4);
    arbol.insertar(6);
    arbol.insertar(8);

    // Prueba tu imprimir
    arbol.ver();

    // Prueba tus recorridos (usando los interruptores nuevos)
    cout << "Inorden: ";
    arbol.mostrarInorden(); 
    cout << "Preorden: ";
    arbol.mostrarPreorden();  
    cout << "Postorden: ";
    arbol.mostrarPostorden();  
    return 0;
}