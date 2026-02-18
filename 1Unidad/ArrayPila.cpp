#include <iostream>
using namespace std;

class Pila {
    private :
       int elementos[10]; // Arreglo de enteros
       int indice ;

    public :
         // Constructor
         Pila () {
             indice = -1;
         }

         // AGREGAR (Push) - Ahora recibe int
         void push(int valor) {
            if (indice < 9) { 
                indice++; 
                elementos[indice] = valor; 
            } 
         }

         // SACAR (Pop)
         void pop() {
            if (indice >= 0) { 
                indice--; 
            }
         }

         // VER EL DE ARRIBA (Top) - Devuelve int
         int top() {
            if (indice >= 0) {
                return elementos[indice]; 
            }
            return -1; // Retorno por defecto si esta vacia
         }
};

int main() {
    Pila miPila;

    // 1. Agregamos numeros
    miPila.push(10);
    miPila.push(20);
    miPila.push(30);

    // 2. Imprimimos el de arriba (30)
    cout << "Arriba esta: " << miPila.top() << endl; 

    miPila.pop(); // Sacamos el 30

    // 3. Imprimimos el nuevo de arriba (20)
    cout << "Ahora arriba esta: " << miPila.top() << endl; 

    return 0;
}