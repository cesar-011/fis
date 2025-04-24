#include "usuario.h"
#include "gestor_de_proyectos.h"
#include <iostream>

int main() {
  std::string opcion;
  std::cout << "=== GESTOR DE PROYECTOS ===" << std::endl;
  std::cout << "1. Crear nuevo proyecto" << std::endl;
  std::cout << "2. Abrir proyecto existente" << std::endl;
  std::cout << "Opción: ";
  std::getline(std::cin, opcion);

  if (opcion == "1") {
    std::string uid;
    std::cout << "Tu UID: ";
    std::getline(std::cin, uid);
    Usuario usuario(uid);
    Proyecto proyecto = GestorDeProyectos::crearProyecto(usuario);
    proyecto.abrirMenuInteractivo(uid);
  } else if (opcion == "2") {
    GestorDeProyectos::abrirProyectoExistente();
  } else {
    std::cout << "Opción no válida" << std::endl;
  }
  return 0;
}
