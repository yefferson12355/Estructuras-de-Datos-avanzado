#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>  // Para poner los numeros bonitos (setw, setprecision)
#include <cstdlib>  // Para system("cls")
#include <string>

// ==========================================
// ESTRUCTURA Y CLASE
// ==========================================

struct Punto {
    double x;
    double y;
};

class PlanoCartesiano {
private:
    std::vector<Punto> puntos;

public:
    void agregarPunto(double x, double y) {
        puntos.push_back({x, y});
        std::cout << "\n>> Punto guardado: (" << x << ", " << y << ")\n";
    }

    void agregarMultiples(int cantidad) {
        for(int i=0; i<cantidad; ++i) {
            double x, y;
            std::cout << "   Punto " << (i+1) << " [X Y]: ";
            std::cin >> x >> y;
            puntos.push_back({x, y});
        }
        std::cout << "\n>> Se agregaron " << cantidad << " puntos.\n";
    }

    double calcularDistancia(int iA, int iB) const {
        if (!indicesValidos(iA, iB)) return 0.0;
        return std::hypot(puntos[iB].x - puntos[iA].x, puntos[iB].y - puntos[iA].y);
    }

    void listarPuntos() const {
        if (puntos.empty()) {
            std::cout << ">> (Lista vacia)\n";
            return;
        }
        std::cout << "\n--- LISTA DE COORDENADAS ---\n";
        for (size_t i = 0; i < puntos.size(); ++i) {
            std::cout << " [" << i << "] -> (" << puntos[i].x << ", " << puntos[i].y << ")\n";
        }
    }

    // =========================================================
    // NUEVO GRAFICO CON EJES NUMÉRICOS (Tipo Papel Milimetrado)
    // =========================================================
    void dibujarGrafico() const {
        if (puntos.empty()) return;

        std::cout << "\n--- PLANO CARTESIANO VISUAL ---\n\n";
        
        // 1. Encontrar limites para escalar
        // Inicializamos con 0,0 para que el origen siempre salga
        double minX = 0, maxX = 0;
        double minY = 0, maxY = 0;

        for (const auto& p : puntos) {
            if (p.x < minX) minX = p.x;
            if (p.x > maxX) maxX = p.x;
            if (p.y < minY) minY = p.y;
            if (p.y > maxY) maxY = p.y;
        }

        // Damos un poco de aire (margen) a los bordes
        maxX += 1; maxY += 1; 

        // 2. Configuración del lienzo
        const int alto = 12; // Cantidad de filas
        const int ancho = 30; // Cantidad de columnas
        char lienzo[alto][ancho];

        // Rellenar fondo con una grilla suave ':'
        for(int i=0; i<alto; i++) 
            for(int j=0; j<ancho; j++) 
                lienzo[i][j] = ':'; // ':' se ve como puntitos de guia

        // 3. Pintar los puntos sobre el lienzo
        for (const auto& p : puntos) {
            int xPos = (int)((p.x - minX) / (maxX - minX + 0.001) * (ancho - 1));
            // Invertimos Y para dibujar de arriba a abajo
            int yPos = (alto - 1) - (int)((p.y - minY) / (maxY - minY + 0.001) * (alto - 1));
            
            if(xPos >= 0 && xPos < ancho && yPos >= 0 && yPos < alto) {
                lienzo[yPos][xPos] = 'O'; // El punto es una 'O' mayúscula
            }
        }

        // 4. IMPRIMIR CON ETIQUETAS NUMÉRICAS (LO QUE PEDISTE)
        
        for(int i=0; i<alto; i++) {
            // Calculamos qué valor Y representa esta fila específica
            // logica: valor = max - (rango * porcentaje_avance)
            double valY = maxY - ((maxY - minY) * (double)i / (double)(alto - 1));

            // Imprimimos el numero del EJE Y a la izquierda (con 1 decimal)
            // setw(5) reserva espacio para que queden alineados
            std::cout << std::setw(5) << std::fixed << std::setprecision(1) << valY << " | ";

            // Imprimimos la fila del gráfico
            for(int j=0; j<ancho; j++) {
                std::cout << lienzo[i][j];
            }
            std::cout << "\n";
        }

        // 5. Imprimir EJE X abajo
        std::cout << "        +" << std::string(ancho, '-') << "\n"; // Linea base
        
        // Imprimir valores X (Minimo ... Medio ... Maximo)
        std::cout << "      " 
                  << std::setw(6) << std::left << minX  // Valor inicial
                  << std::string(ancho - 12, ' ')       // Espacio en medio
                  << std::setw(6) << std::right << maxX // Valor final
                  << "\n";
        std::cout << "      (Eje X) \n";
    }

    bool indicesValidos(int i1, int i2) const {
        return (i1 >= 0 && i1 < puntos.size() && i2 >= 0 && i2 < puntos.size());
    }
    
    int cantidad() const { return puntos.size(); }
};

// ==========================================
// FUNCIONES DE UTILIDAD (MENU)
// ==========================================

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar() {
    std::cout << "\n[Presiona Enter para continuar...]";
    std::cin.ignore();
    std::cin.get();
}

int main() {
    PlanoCartesiano plano;
    int opcion = -1;

    while (opcion != 0) {
        limpiarPantalla(); 
        
        std::cout << "=== MENU GEOMETRICO ===\n";
        std::cout << "1. Agregar coordenada (x, y)\n";
        std::cout << "2. Agregar multiples coordenadas\n";
        std::cout << "3. Ver grafico con ejes\n";
        std::cout << "4. Calcular distancia\n";
        std::cout << "0. Salir\n";
        std::cout << "Selecciona: ";
        std::cin >> opcion;

        if (opcion == 1) {
            double x, y;
            std::cout << "Ingresa X: "; std::cin >> x;
            std::cout << "Ingresa Y: "; std::cin >> y;
            plano.agregarPunto(x, y);
            pausar();

        } else if (opcion == 2) {
            int cant;
            std::cout << "¿Cuantos puntos?: "; std::cin >> cant;
            plano.agregarMultiples(cant);
            pausar();

        } else if (opcion == 3) {
            limpiarPantalla();
            plano.listarPuntos();
            plano.dibujarGrafico(); // <--- AQUI SE VE LA MAGIA
            pausar();

        } else if (opcion == 4) {
            if (plano.cantidad() < 2) {
                std::cout << "!! Faltan puntos (minimo 2).\n";
            } else {
                plano.listarPuntos();
                int a, b;
                std::cout << "Punto A (indice): "; std::cin >> a;
                std::cout << "Punto B (indice): "; std::cin >> b;
                double dist = plano.calcularDistancia(a, b);
                std::cout << "\n>>> DISTANCIA: " << std::fixed << std::setprecision(2) << dist << "\n";
            }
            pausar();
        }
    }
    return 0;
}