#ifndef AGENDABACKEND_H
#define AGENDABACKEND_H

#include "lista.h"
#include <string>

using namespace std;

class AgendaBackend {
private:
    lista misContactos;
    string nombreArchivo = "agenda_contactos.txt"; 

public:
    AgendaBackend();
    ~AgendaBackend();

    void registrarContacto(Contacto c);
    void verAgenda();
    void borrarPrimero();
    void borrarUltimo();

    // Persistencia
    void guardarEnTexto();
    void cargarDesdeTexto();

    // 
    void buscarContacto(int id);

    int generarNuevoId();
};

#endif // AGENDABACKEND_H