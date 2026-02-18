#include <iostream>
#include <vector>
#include <cmath>    // Para hypot (distancia euclidiana) y abs
#include <iomanip>  // Para setw (alineación) y setprecision
#include <cstdlib>  // Para system("cls")
#include <string>

using namespace std;



struct Punto {
    double x;
    double y;
    char nombre; // A....
};


class PlanoCartesiano {
private:
    vector<Punto> puntos;

public:
    // Agrega un punto, le asigna nombre y activa el radar de proximidad
    void agregarPunto(double x, double y) {
        char letra = 'A' + (char)puntos.size();
        puntos.push_back({x, y, letra});
        
        cout << "\n>> Punto " << letra << " guardado en: (" << x << ", " << y << ")" << endl;

        // Analiza automáticamente la distancia con los puntos que ya existían
        analizarProximidad();
    }

    // Permite ingresar varios puntos llamando internamente a agregarPunto
    void agregarMultiples(int cantidad) {
        for (int i = 0; i < cantidad; ++i) {
            double x, y;
            cout << "   Punto " << (char)('A' + puntos.size()) << " [X Y]: ";
            cin >> x >> y;
            agregarPunto(x, y);
        }
    }

    // Calcula la distancia entre dos puntos seleccionados por el usuario
    double calcularDistancia(int iA, int iB) {
        if (!indicesValidos(iA, iB)) return 0.0;
        return hypot(puntos[iB].x - puntos[iA].x, puntos[iB].y - puntos[iA].y);
    }

    // Muestra el análisis de distancias del último punto contra los anteriores
    void analizarProximidad() {
        if (puntos.size() < 2) return; //mas de dos elementos para analizar

        Punto actual = puntos.back();
        double minDistancia = 999999.0;  // inicialmente para que sea menor 
        char nombreCercano = '?'; //guardar el nombre del punto mas cercano

        cout << "\n--- ANALISIS DE PROXIMIDAD (Punto " << actual.nombre << ") ---" << endl;

        for (size_t i = 0; i < puntos.size() - 1; i++) {
            double d = hypot(actual.x - puntos[i].x, actual.y - puntos[i].y);
            
            cout << " -> Distancia a " << puntos[i].nombre << ": " << fixed << setprecision(2) << d << endl;

            if (d < minDistancia) {
                minDistancia = d;
                nombreCercano = puntos[i].nombre;
            }
        }

        cout << "\n[*] RESULTADO: El vecino mas cercano a " << actual.nombre 
             << " es " << nombreCercano << " (d=" << minDistancia << ")" << endl;
    }

    void listarPuntos() {
        if (puntos.empty()) return;
        cout << "\n--- COORDENADAS REGISTRADAS ---" << endl;
        for (size_t i = 0; i < puntos.size(); ++i) {
            cout << " [" << i << "] Punto " << puntos[i].nombre << " -> (" << puntos[i].x << ", " << puntos[i].y << ")" << endl;
        }
    }

    void dibujarGrafico() {
        if (puntos.empty()) return;

        int maxX = 1, maxY = 1;
        for (const auto& p : puntos) {
            if (p.x > maxX) maxX = (int)p.x;
            if (p.y > maxY) maxY = (int)p.y;
        }

        cout << "\n--- VISTA DEL PLANO (Letras) ---" << endl << endl;

        for (int y = maxY; y >= 1; --y) {
            cout << setw(3) << y << " | "; 
            for (int x = 1; x <= maxX; ++x) {
                char marca = '.';
                for (const auto& p : puntos) {
                    if (abs(p.x - x) < 0.1 && abs(p.y - y) < 0.1) {
                        marca = p.nombre; // Dibujamos la letra del punto
                        break;
                    }
                }
                cout << " " << marca << " ";
            }
            cout << endl;
        }

        cout << "    | " << endl << "      "; 
        for (int x = 1; x <= maxX; ++x) {
            cout << setw(2) << x << " "; 
        }
        cout << "\n\n      (Eje X)\n" << endl;
    }

    bool indicesValidos(int i1, int i2) {
        return (i1 >= 0 && (size_t)i1 < puntos.size() && 
                i2 >= 0 && (size_t)i2 < puntos.size());
    }
    
    int cantidad() { return (int)puntos.size(); }
};

void limpiar() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausa() {
    cout << "\n[Presiona Enter para continuar...]";
    cin.ignore();
    cin.get();
}

int main() {
    PlanoCartesiano plano;
    int opcion = -1;

    while (opcion != 0) {
        limpiar();
        cout << "=== SISTEMA GEOMETRICO CON RADAR ===" << endl;
        cout << "1. Agregar punto " << endl;
        cout << "2. Agregar varios puntos" << endl;
        cout << "3. Ver lista y grafico de letras" << endl;
        cout << "4. Calcular distancia especifica" << endl;
        cout << "0. Salir" << endl;
        cout << "Selecciona: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                double x, y;
                cout << "Ingrese X: "; cin >> x;
                cout << "Ingrese Y: "; cin >> y;
                plano.agregarPunto(x, y);
                pausa();
                break;
            }
            case 2: {
                int n;
                cout << "¿Cuantos puntos?: "; cin >> n;
                plano.agregarMultiples(n);
                pausa();
                break;
            }
            case 3:
                limpiar();
                plano.listarPuntos();
                plano.dibujarGrafico();
                pausa();
                break;
            case 4:
                if (plano.cantidad() < 2) {
                    cout << "!! Se necesitan al menos 2 puntos." << endl;
                } else {
                    plano.listarPuntos();
                    int a, b;
                    cout << "Indice del Punto A: "; cin >> a;
                    cout << "Indice del Punto B: "; cin >> b;
                    double d = plano.calcularDistancia(a, b);
                    cout << "\n>> La distancia es: " << fixed << setprecision(2) << d << endl;
                }
                pausa();
                break;
        }
    }
    return 0;
}