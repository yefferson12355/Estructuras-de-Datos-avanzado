#include <iostream>
using namespace std;

class Fraccion
{
private:
    int numerador;
    int denominador;

public:
   
    Fraccion(int numerador, int denominador);
    
    double valor(); 
};

// Constructor
Fraccion::Fraccion(int numerador, int denominador)
{
    this->numerador = numerador;
    this->denominador = denominador;
}


double Fraccion::valor()
{
    return numerador / denominador;
}

int main ()
{
    Fraccion fraccion1(3, 4);
    cout << "Valor de la fraccion: " << fraccion1.valor() << endl;
    return 0;
}