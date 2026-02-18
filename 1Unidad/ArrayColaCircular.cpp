#include <iostream>
using namespace std;

class ColaCircular {
    private:
        int cola[5]; 
        int Frente;  
        int Final;   
        int MAX;     

    public:
        ColaCircular() {
            MAX = 5;
            Frente = -1;
            Final = -1;
        }

        bool estaVacia() {
            return (Frente == -1);
        }

        bool estaLlena() {
            return ((Final + 1 == Frente) || (Frente == 0 && Final == MAX - 1));
        }

        void push(int valor) {
            if (estaLlena()) return; 

            if (Final == MAX - 1) {
                Final = 0;      
            } else {
                Final++;        
            }

            cola[Final] = valor;

            if (Frente == -1) Frente = 0;
        }

        int pop() {
            if (estaVacia()) return -1;

            int valor = cola[Frente];

            if (Frente == Final) {
                Frente = -1;
                Final = -1;
            } else {
                if (Frente == MAX - 1) {
                    Frente = 0; 
                } else {
                    Frente++;   
                }
            }
            return valor;
        }
};

int main() {
    ColaCircular miCola;

    miCola.push(10);
    miCola.push(20);
    miCola.push(30);

    cout << "Salio: " << miCola.pop() << endl; 
    cout << "Salio: " << miCola.pop() << endl; 

    miCola.push(40); 
    cout << "Salio: " << miCola.pop() << endl; 
    cout << "Salio: " << miCola.pop() << endl; 

    return 0;
}