#ifndef TAREA_H
#define TAREA_H

#include <string>

class Tarea {
 public:
  Tarea(const std::string& descripcion, const std::string& asignado_uid, bool completada = false);
  
  std::string formatear() const;
  static Tarea desdeLinea(const std::string& linea);
  bool estaCompletada() const;
  void marcarComoCompletada();
  std::string getDescripcion() const;
  std::string getAsignadoUID() const;

 private:
  std::string descripcion_;
  std::string asignado_uid_;
  bool completada_;
};

#endif
