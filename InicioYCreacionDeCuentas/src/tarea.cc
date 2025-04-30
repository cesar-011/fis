#include "../include/Proyects/tarea.h"
#include <sstream>

Tarea::Tarea(const std::string& descripcion, const std::string& asignado_uid, bool completada)
  : descripcion_(descripcion), asignado_uid_(asignado_uid), completada_(completada) {}

std::string Tarea::formatear() const {
  return descripcion_ + " | " + asignado_uid_ + " | " + (completada_ ? "completada" : "pendiente");
}

Tarea Tarea::desdeLinea(const std::string& linea) {
  std::istringstream ss(linea);
  std::string desc, uid, estado;
  std::getline(ss, desc, '|');
  std::getline(ss, uid, '|');
  std::getline(ss, estado);

  // quitar espacios
  desc.erase(desc.find_last_not_of(" \t\n\r\f\v") + 1);
  uid.erase(0, uid.find_first_not_of(" \t"));
  estado.erase(0, estado.find_first_not_of(" \t"));

  return Tarea(desc, uid, estado == "completada");
}

bool Tarea::estaCompletada() const {
  return completada_;
}

void Tarea::marcarComoCompletada() {
  completada_ = true;
}

std::string Tarea::getDescripcion() const {
  return descripcion_;
}

std::string Tarea::getAsignadoUID() const {
  return asignado_uid_;
}
