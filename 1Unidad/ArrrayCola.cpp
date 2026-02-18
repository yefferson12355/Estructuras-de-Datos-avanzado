#include <iostream>
using namespace std;

class Cola {
    private :
       int elementos[10]; 
       int indice; 

    public :
         Cola () {
             indice = -1;
         }

         void push(int valor) {
            if (indice < 9) { 
                indice++; 
                elementos[indice] = valor; 
            } 
         }

        
         int pop() {
            if (indice >= 0) { 
                // 1. Guardamos al que está en el frente (el que se va a ir)
                int valorAtendido = elementos[0];

                // 2. Movemos a todos los demás un paso hacia adelante
                for (int i = 0; i < indice; i++) {
                    elementos[i] = elementos[i+1];
                }
                
                // 3. Reducimos el indice
                indice--; 

                // 4. Devolvemos el valor que sacamos
                return valorAtendido;
            }
            return -1; // Si estaba vacía
         }
};

int main() {
    Cola miCola;

    
    miCola.push(10); 
    miCola.push(20);
    miCola.push(30);

    
    cout << "Atendiendo a: " << miCola.pop() << endl; // Debe salir el 10
    cout << "Atendiendo a: " << miCola.pop() << endl; // Debe salir el 20
    cout << "Atendiendo a: " << miCola.pop() << endl; // Debe salir el 30

    return 0;
}