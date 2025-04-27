#ifndef GESTOR_DE_PROYECTOS_H
#define GESTOR_DE_PROYECTOS_H

#include "usuario.h"
#include "proyecto.h"
#include <vector>
#include <string>

class GestorDeProyectos {
public:
  static Proyecto crearProyecto(const Usuario2& usuario);
  static void abrirProyectoExistente();
};

#endif
