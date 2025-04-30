#include "../include/Proyects/proyecto.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <filesystem>

Proyecto::Proyecto(const std::string& nombre, const std::string& descripcion, const std::string& creador_uid)
  : nombre_(nombre), descripcion_(descripcion), creador_uid_(creador_uid) {
  id_ = generarID();
  ruta_ = nombre_;
}

Proyecto::Proyecto(const std::string& rutaProyecto) {
  ruta_ = rutaProyecto;
  std::ifstream info(ruta_ + "/info.txt");
  std::string linea;
  while (std::getline(info, linea)) {
    if (linea.rfind("ID:", 0) == 0) {
      id_ = linea.substr(4);
    } else if (linea.rfind("Nombre:", 0) == 0) {
      nombre_ = linea.substr(8);
    } else if (linea.rfind("Descripción:", 0) == 0) {
      descripcion_ = linea.substr(13);
    } else if (linea.rfind("Creador:", 0) == 0) {
        creador_uid_ = linea.substr(9);
    } else if (linea.rfind("Miembros:", 0) == 0) {
      std::string miembrosStr = linea.substr(10);
      size_t comienzo = 0, final;
      while ((final = miembrosStr.find(',', comienzo)) != std::string::npos) {
        miembros_.push_back(miembrosStr.substr(comienzo, final - comienzo));
        comienzo = final + 2;
      }
      if (comienzo < miembrosStr.length()) {
        miembros_.push_back(miembrosStr.substr(comienzo));
      }
    }
  }
}

std::string Proyecto::generarID() {
  std::srand(std::time(nullptr));
  return "PRJ" + std::to_string(std::rand() % 1000000);
}

std::string Proyecto::obtenerFechaHora() const {
  std::time_t ahora = std::time(nullptr);
  char buffer[100];
  std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&ahora));
  return std::string(buffer);
}

void Proyecto::registrarHistorial(const std::string& mensaje) const {
  std::ofstream historial(ruta_ + "/historial.txt", std::ios::app);
  if (historial.is_open()) {
    historial << "[" << obtenerFechaHora() << "] " << mensaje << std::endl;
  }
}

void Proyecto::anadirMiembro(const std::string& uid) {
  miembros_.push_back(uid);
}

bool Proyecto::crearDirectorio() {
  return std::filesystem::create_directory(ruta_);
}

void Proyecto::guardarInfo() {
  std::ofstream info(ruta_ + "/info.txt");
  info << "ID: " << id_ << std::endl;
  info << "Nombre: " << nombre_ << std::endl;
  info << "Descripción: " << descripcion_ << std::endl;
  info << "Creador: " << creador_uid_ << std::endl;
  info << "Miembros: ";
  for (size_t i = 0; i < miembros_.size(); ++i) {
    info << miembros_[i];
    if (i != miembros_.size() - 1) {
      info << ", ";
    }
  }
  info << std::endl;
  registrarHistorial("Proyecto creado por " + creador_uid_);
}


void Proyecto::crearArchivo(const std::string& usuarioUID) {
  std::string archivo;
  std::cout << "Nombre del archivo: ";
  std::getline(std::cin, archivo);
  std::ofstream out(ruta_ + "/" + archivo);
  if (out.is_open()) {
    out << "Creado por " << usuarioUID << std::endl;
    registrarHistorial("Creado archivo '" + archivo + "' por " + usuarioUID);
  }
}

void Proyecto::modificarArchivo(const std::string& usuarioUID) {
  std::string archivo, texto;
  std::cout << "Archivo a modificar: ";
  std::getline(std::cin, archivo);
  std::ofstream out(ruta_ + "/" + archivo, std::ios::app);
  if (out.is_open()) {
    std::cout << "Texto a añadir: ";
    std::getline(std::cin, texto);
    out << texto << std::endl;
    registrarHistorial("Modificado archivo '" + archivo + "' por " + usuarioUID);
  }
}

void Proyecto::borrarArchivo(const std::string& usuarioUID) {
  std::string archivo;
  std::cout << "Archivo a borrar: ";
  std::getline(std::cin, archivo);
  if (std::filesystem::remove(ruta_ + "/" + archivo)) {
    registrarHistorial("Eliminado archivo '" + archivo + "' por " + usuarioUID);
  } else {
    std::cout << "No se pudo borrar el archivo" << std::endl;
  }
}


void Proyecto::renombrarArchivo(const std::string& usuarioUID) {
  std::string original, nuevo;
  std::cout << "Archivo a renombrar: ";
  std::getline(std::cin, original);
  std::cout << "Nuevo nombre: ";
  std::getline(std::cin, nuevo);

  std::string rutaOriginal = ruta_ + "/" + original;
  std::string rutaNuevo = ruta_ + "/" + nuevo;

  if (!std::filesystem::exists(rutaOriginal)) {
    std::cout << "El archivo '" << original << "' no existe. No se puede renombrar" << std::endl;
    return;
  }
 
  try {
    std::filesystem::rename(rutaOriginal, rutaNuevo);
    registrarHistorial("Renombrado archivo '" + original + "' -> '" + nuevo + "' por " + usuarioUID);
    std::cout << "Archivo renombrado correctamente" << std::endl;
  } catch (const std::filesystem::filesystem_error& e) {
    std::cerr << "Error al renombrar: " << e.what() << std::endl;
  }
}


void Proyecto::verHistorial() const {
  std::ifstream hist(ruta_ + "/historial.txt");
  std::string linea;
  std::cout << "\n--- Historial del Proyecto ---" << std::endl;
  while (std::getline(hist, linea)) {
    std::cout << linea << std::endl;
  }
}

void Proyecto::abrirMenuInteractivo(const std::string& usuarioUID) {
  std::string opcion;
  do {
    std::cout << "\n--- Menú de Proyecto (" << nombre_ << ") ---" << std::endl;
    std::cout << "1. Crear archivo" << std::endl;
    std::cout << "2. Modificar archivo" << std::endl;
    std::cout << "3. Borrar archivo" << std::endl;
    std::cout << "4. Renombrar archivo" << std::endl;
    std::cout << "5. Ver historial" << std::endl;
    std::cout << "6. Añadir tarea" << std::endl;
    std::cout << "7. Completar tarea" << std::endl;
    std::cout << "8. Mostrar tareas" << std::endl;
    std::cout << "9. Salir" << std::endl;
    std::cout << "Elige una opción: ";
    std::getline(std::cin, opcion);

    if (opcion == "1") {
      crearArchivo(usuarioUID);
    } else if (opcion == "2") {
      modificarArchivo(usuarioUID);
    } else if (opcion == "3") {
      borrarArchivo(usuarioUID);
    } else if (opcion == "4") {
      renombrarArchivo(usuarioUID);
    } else if (opcion == "5") {
      verHistorial();
    } else if (opcion == "6") {
      anadirTarea();
    } else if (opcion == "7") {
      completarTarea();
    } else if (opcion == "8") {
      mostrarTareas();
    }
  } while (opcion != "9");
}

std::string Proyecto::getRuta() const {
  return ruta_;
}

std::string Proyecto::getNombre() const {
  return nombre_;
}

void Proyecto::anadirTarea() {
  std::string descripcion, uid;
  std::cout << "Descripción de la tarea: ";
  std::getline(std::cin, descripcion);
  std::cout << "Asignar a UID: ";
  std::getline(std::cin, uid);

  Tarea tarea(descripcion, uid);
  std::ofstream out(ruta_ + "/tareas.txt", std::ios::app);
  if (out.is_open()) {
    out << tarea.formatear() << std::endl;
    std::cout << "Tarea añadida" << std::endl;
  } else {
    std::cout << "No se pudo guardar la tarea" << std::endl;
  }
}

void Proyecto::completarTarea() {
  std::ifstream in(ruta_ + "/tareas.txt");
  if (!in.is_open()) {
    std::cout << "No hay tareas registradas" << std::endl;
    return;
  }

  std::vector<Tarea> tareas;
  std::string linea;
  while (std::getline(in, linea)) {
    if (!linea.empty()) {
      tareas.push_back(Tarea::desdeLinea(linea));
    }
  }
  in.close();

  if (tareas.empty()) {
    std::cout << "No hay tareas pendientes" << std::endl;
    return;
  }

  std::cout << "\n--- Tareas ---" << std::endl;
  for (size_t i = 0; i < tareas.size(); ++i) {
    std::cout << i + 1 << ". " << tareas[i].formatear() << std::endl;
  }

  int opcion;
  std::cout << "Selecciona una tarea a marcar como completada (número): ";
  std::cin >> opcion;
  std::cin.ignore();

  if (opcion < 1 || opcion > (int)tareas.size()) {
    std::cout << "Opción inválida" << std::endl;
    return;
  }

  tareas[opcion - 1].marcarComoCompletada();

  std::ofstream out(ruta_ + "/tareas.txt");
  for (const auto& tarea : tareas) {
    out << tarea.formatear() << std::endl;
  }

  std::cout << "Tarea actualizada" << std::endl;
}


void Proyecto::mostrarTareas() const {
  std::ifstream archivo(ruta_ + "/tareas.txt");
  if (!archivo.is_open()) {
    std::cout << "No hay tareas registradas" << std::endl;
    return;
  }

  std::string linea;
  int numero = 1;
  std::cout << "\n--- Tareas del proyecto ---" << std::endl;
  while (std::getline(archivo, linea)) {
    if (!linea.empty()) {
      std::cout << numero << ". " << linea << std::endl;
      numero++;
    }
  }

  if (numero == 1) {
    std::cout << "No hay tareas en el archivo" << std::endl;
  }
}


bool Proyecto::tieneAcceso(const std::string& usuarioUID) const {
  // El creador tiene acceso
  if (usuarioUID == creador_uid_) {
    return true;
  }
  
  // Los miembros tambien tienen acceso
  for (const auto& miembro : miembros_) {
    if (miembro == usuarioUID) {
      return true;
    }
  }

  // Si no es el creador ni un miembro, no tiene acceso
  return false;
}