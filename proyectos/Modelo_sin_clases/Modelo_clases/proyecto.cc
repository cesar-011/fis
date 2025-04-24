#include "proyecto.h"
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
  std::filesystem::rename(ruta_ + "/" + original, ruta_ + "/" + nuevo);
  registrarHistorial("Renombrado archivo '" + original + "' -> '" + nuevo + "' por " + usuarioUID);
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
    std::cout << "6. Salir" << std::endl;
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
    }
  } while (opcion != "6");
}

std::string Proyecto::getRuta() const {
  return ruta_;
}

std::string Proyecto::getNombre() const {
  return nombre_;
}
