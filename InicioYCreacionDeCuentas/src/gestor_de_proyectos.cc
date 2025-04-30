#include "../include/Proyects/gestor_de_proyectos.h"
#include <iostream>
#include <filesystem>

Proyecto GestorDeProyectos::crearProyecto(const Usuario& usuario) {
  std::string nombre, descripcion;
  std::cout << "Nombre del proyecto: ";
  std::getline(std::cin, nombre);
  std::cout << "Descripción: ";
  std::getline(std::cin, descripcion);

  Proyecto proyecto(nombre, descripcion, usuario.getUID());

  std::string respuesta;
  std::cout << "¿Añadir miembros? (s/n): ";
  std::getline(std::cin, respuesta);
  while (respuesta == "s") {
    std::string uid;
    std::cout << "UID del miembro: ";
    std::getline(std::cin, uid);
    proyecto.anadirMiembro(uid);
    std::cout << "¿Otro miembro? (s/n): ";
    std::getline(std::cin, respuesta);
  }

  if (proyecto.crearDirectorio()) {
    proyecto.guardarInfo();
  } else {
    std::cerr << "No se pudo crear el directorio del proyecto" << std::endl;
  }

  return proyecto;
}


void GestorDeProyectos::abrirProyectoExistente() {
  std::vector<std::string> proyectos;

  for (const auto& entrada : std::filesystem::directory_iterator(".")) {
    if (entrada.is_directory() && std::filesystem::exists(entrada.path() / "info.txt")) {
      proyectos.push_back(entrada.path().filename().string());
    }
  }

  if (proyectos.empty()) {
    std::cout << "No hay proyectos disponibles" << std::endl;
    return;
  }

  std::cout << "\n--- Proyectos disponibles ---" << std::endl;
  for (size_t i = 0; i < proyectos.size(); ++i) {
    std::cout << i + 1 << ". " << proyectos[i] << std::endl;
  }

  int seleccion;
  std::cout << "Selecciona un proyecto (número): ";
  std::cin >> seleccion;
  std::cin.ignore();

  if (seleccion < 1 || seleccion > (int)proyectos.size()) {
    std::cout << "Opción no válida" << std::endl;
    return;
  }

  std::string uid;
  std::cout << "Tu UID: ";
  std::getline(std::cin, uid);

  Proyecto proyecto(proyectos[seleccion - 1]);

  // Verificamos si el usuario tiene acceso
  if (!proyecto.tieneAcceso(uid)) {
    std::cout << "No tienes acceso a este proyecto" << std::endl;
    return;
  }

  proyecto.abrirMenuInteractivo(uid);
}
