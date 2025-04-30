#ifndef PROYECTO_H
#define PROYECTO_H

#include <string>
#include <vector>
#include <sstream>
#include "tarea.h"

class Proyecto {
 public:
  Proyecto(const std::string& nombre, const std::string& descripcion, const std::string& creador_uid);
  Proyecto(const std::string& rutaProyecto);
  
  std::string generarID();
  std::string obtenerFechaHora() const;
  void registrarHistorial(const std::string& mensaje) const;
  
  void anadirMiembro(const std::string& uid);
  bool crearDirectorio();
  void guardarInfo();
  
  void abrirMenuInteractivo(const std::string& usuarioUID);
  void crearArchivo(const std::string& usuarioUID);
  void modificarArchivo(const std::string& usuarioUID);
  void borrarArchivo(const std::string& usuarioUID);
  void renombrarArchivo(const std::string& usuarioUID);
  void verHistorial() const;
  void anadirTarea();
  void completarTarea();
  void mostrarTareas() const;
  bool tieneAcceso(const std::string& usuarioUID) const;
  
  std::string getRuta() const;
  std::string getNombre() const;

 private:
  std::string id_;
  std::string nombre_;
  std::string descripcion_;
  std::string creador_uid_;
  std::vector<std::string> miembros_;
  std::string ruta_;
};
  
#endif