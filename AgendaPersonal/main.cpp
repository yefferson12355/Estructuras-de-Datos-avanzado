#include <iostream>
#include <limits>
#include "agendabackend.h"

using namespace std;

string pedirTexto(string mensaje) {
    string entrada;
    cout << mensaje;
    getline(cin >> ws, entrada); 
    return entrada;
}

int main() {
    AgendaBackend agenda;
    agenda.cargarDesdeTexto();

    int opcion = -1;
    while (opcion != 0) {
        cout << "\n=== AGENDA MEJORADA ===" << endl;
        cout << "1. Registrar Contacto (Completo)" << endl;
        cout << "2. Ver Agenda" << endl;
        cout << "3. Eliminar el PRIMERO" << endl;
        cout << "4. Eliminar el ULTIMO" << endl;
        cout << "5. BUSCAR POR ID" << endl; // <--- OPCION NUEVA
        cout << "6. Guardar Cambios" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione: ";
        cin >> opcion;

        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcion = -1;
        }

        switch (opcion) {
        case 1: {
            Contacto c;
            cout << "\n--- REGISTRAR NUEVO CONTACTO ---" << endl;
            
            // --- CAMBIO: AUTO-INCREMENTO ---
            c.id = agenda.generarNuevoId(); 
            cout << "[SISTEMA] Asignando ID Automatico: " << c.id << endl;
            // -------------------------------

            c.nombres = pedirTexto("Nombres: ");
            c.paterno = pedirTexto("Apellido Paterno: ");
            c.materno = pedirTexto("Apellido Materno: ");
            c.telefono = pedirTexto("Telefono: ");
            c.correo = pedirTexto("Correo Electronico: ");
            c.direccion = pedirTexto("Direccion: ");
            
            cout << "Edad: "; 
            while(!(cin >> c.edad)) { // Validación simple para que no falle si meten letras
                cout << "Por favor ingrese un numero valido para la edad: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            c.FechaNacimiento = pedirTexto("Fecha Nacimiento (YYYY-MM-DD): ");
            
            agenda.registrarContacto(c);
            cout << ">> Contacto guardado con ID " << c.id << " exitosamente." << endl;
            break;
        }
        case 2:
            agenda.verAgenda();
            break;
        case 3:
            agenda.borrarPrimero();
            cout << ">> Eliminado." << endl;
            break;
        case 4:
            agenda.borrarUltimo();
            cout << ">> Eliminado." << endl;
            break;
        case 5: { // <--- LOGICA DE BUSQUEDA
            int idBus;
            cout << "Ingrese el ID a buscar: ";
            cin >> idBus;
            agenda.buscarContacto(idBus);
            break;
        }
        case 6:
            agenda.guardarEnTexto();
            break;
        case 0:
            cout << "Guardando y saliendo..." << endl;
            agenda.guardarEnTexto();
            break;
        default:
            cout << "Opcion no valida." << endl;
        }
    }
    return 0;
}