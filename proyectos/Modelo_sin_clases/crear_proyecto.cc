#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <filesystem>


// Estructura del proyecto
struct Proyecto {
  std::string id;
  std::string nombre;
  std::string descripcion;
  std::string creadorUID;
  std::vector<std::string> miembros;
};

// Funciones auxiliares 
std::string generarID() {
  srand(time(nullptr));
  return "PRJ" + std::to_string(rand() % 1000000);
}

std::string obtenerFechaHora() {
  time_t ahora = time(nullptr);
  char buffer[100];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&ahora));
  return std::string(buffer);
}

void registrarHistorial(const std::string& rutaProyecto, const std::string& mensaje) {
  std::string rutaHistorial = rutaProyecto + "/historial.txt";
  std::ofstream archivo(rutaHistorial, std::ios::app);
  if (archivo.is_open()) {
    archivo << "[" << obtenerFechaHora() << "] " << mensaje << std::endl;
    archivo.close();
  } else {
    std::cerr << " No se pudo escribir en el historial" << std::endl;
  }
}

// Acciones del menu
void crearArchivo(const std::string& rutaProyecto, const std::string& usuarioUID) {
  std::string nombreArchivo;
  std::cout << "Nombre del nuevo archivo: ";
  std::getline(std::cin, nombreArchivo);

  std::string rutaCompleta = rutaProyecto + "/" + nombreArchivo;
  std::ofstream archivo(rutaCompleta);
  if (archivo.is_open()) {
    archivo << "Archivo creado por " << usuarioUID << std::endl;
    archivo.close();
    std::cout << " Archivo creado" << std::endl;
    registrarHistorial(rutaProyecto, "Creado archivo '" + nombreArchivo + "' por " + usuarioUID);
  } else {
    std::cerr << " No se pudo crear el archivo" << std::endl;
  }
}

void modificarArchivo(const std::string& rutaProyecto, const std::string& usuarioUID) {
  std::string nombreArchivo;
  std::cout << "Archivo a modificar: ";
  std::getline(std::cin, nombreArchivo);

  std::string rutaCompleta = rutaProyecto + "/" + nombreArchivo;
  std::ofstream archivo(rutaCompleta, std::ios::app);
  if (archivo.is_open()) {
    std::string linea;
    std::cout << "Texto a añadir: ";
    std::getline(std::cin, linea);
    archivo << linea << std::endl;
    archivo.close();
    std::cout << " Archivo modificado" << std::endl;
    registrarHistorial(rutaProyecto, "Modificado archivo '" + nombreArchivo + "' por " + usuarioUID);
  } else {
    std::cerr << " No se pudo modificar" << std::endl;
  }
}

void borrarArchivo(const std::string& rutaProyecto, const std::string& usuarioUID) {
  std::string nombreArchivo;
  std::cout << "Archivo a eliminar: ";
  std::getline(std::cin, nombreArchivo);

  std::string rutaCompleta = rutaProyecto + "/" + nombreArchivo;
  if (std::filesystem::remove(rutaCompleta)) {
    std::cout << " Archivo eliminado" << std::endl;
    registrarHistorial(rutaProyecto, "Eliminado archivo '" + nombreArchivo + "' por " + usuarioUID);
  } else {
    std::cerr << " No se pudo borrar el archivo" << std::endl;
  }
}

void renombrarArchivo(const std::string& rutaProyecto, const std::string& usuarioUID) {
  std::string original, nuevo;
  std::cout << "Nombre actual del archivo: ";
  std::getline(std::cin, original);
  std::cout << "Nuevo nombre: ";
  std::getline(std::cin, nuevo);

  std::string rutaOriginal = rutaProyecto + "/" + original;
  std::string rutaNueva = rutaProyecto + "/" + nuevo;

  if (std::filesystem::exists(rutaOriginal)) {
    std::filesystem::rename(rutaOriginal, rutaNueva);
    std::cout << " Archivo renombrado" << std::endl;
    registrarHistorial(rutaProyecto, "Renombrado archivo '" + original + "' -> '" + nuevo + "' por " + usuarioUID);
  } else {
    std::cerr << " Archivo original no encontrado" << std::endl;
  }
}

void mostrarHistorial(const std::string& rutaProyecto) {
  std::string rutaHistorial = rutaProyecto + "/historial.txt";
  std::ifstream archivo(rutaHistorial);
  if (archivo.is_open()) {
    std::string linea;
    std::cout << "=== Historial de cambios ===" << std::endl;
    while (std::getline(archivo, linea)) {
      std::cout << linea << std::endl;
    }
    archivo.close();
  } else {
    std::cerr << " No se pudo abrir el historial" << std::endl;
  }
}

// Menu de proyecto
void menuProyecto(const std::string& rutaProyecto, const std::string& usuarioUID) {
  std::string opcion;
  do {
    std::cout << "\n--- Menú de Proyecto (" << rutaProyecto << ") ---" << std::endl;
    std::cout << "1. Crear archivo" << std::endl;
    std::cout << "2. Modificar archivo" << std::endl;
    std::cout << "3. Borrar archivo" << std::endl;
    std::cout << "4. Renombrar archivo" << std::endl;
    std::cout << "5. Ver historial" << std::endl;
    std::cout << "6. Salir" << std::endl;
    std::cout << "Elige una opción: ";
    std::getline(std::cin, opcion);

    if (opcion == "1") {
      crearArchivo(rutaProyecto, usuarioUID);
    } else if (opcion == "2") {
      modificarArchivo(rutaProyecto, usuarioUID);
    } else if (opcion == "3") {
      borrarArchivo(rutaProyecto, usuarioUID);
    } else if (opcion == "4") { 
      renombrarArchivo(rutaProyecto, usuarioUID);
    } else if (opcion == "5") { 
      mostrarHistorial(rutaProyecto);
    } else if (opcion != "6") {
      std::cout << "Opción no válida" << std::endl;
    }
  } while (opcion != "6");
}

// Crear proyecto
void crearProyecto(const std::string& usuarioUID) {
  Proyecto project;
  project.creadorUID = usuarioUID;

  std::cout << "=== Crear nuevo proyecto (directorio) ===" << std::endl;
  std::cout << "Nombre del proyecto: ";
  std::getline(std::cin, project.nombre);
  std::cout << "Descripción: ";
  std::getline(std::cin, project.descripcion);
  project.id = generarID();

  // Añadir miembros
  std::string respuesta;
  std::cout << "¿Quieres añadir miembros al proyecto? (s/n): ";
  std::getline(std::cin, respuesta);
  while (respuesta == "s" || respuesta == "S") {
    std::string uidMiembro;
    std::cout << "Escribe el UID del usuario a añadir: ";
    std::getline(std::cin, uidMiembro);
    project.miembros.push_back(uidMiembro);
    std::cout << "¿Añadir otro miembro? (s/n): ";
    std::getline(std::cin, respuesta);
  }

  // Crear directorio
  if (std::filesystem::create_directory(project.nombre)) {
    std::ofstream info(project.nombre + "/info.txt");
    if (info.is_open()) {
      info << "ID: " << project.id << std::endl;
      info << "Nombre: " << project.nombre << std::endl;
      info << "Descripción: " << project.descripcion << std::endl;
      info << "Creador: " << project.creadorUID << std::endl;
      info << "Miembros: ";
      for (size_t i = 0; i < project.miembros.size(); ++i) {
        info << project.miembros[i];
        if (i != project.miembros.size() - 1)
          info << ", ";
      }
      info << std::endl;
      info.close();
      registrarHistorial(project.nombre, "Proyecto creado por " + usuarioUID);
      std::cout << " Proyecto creado y guardado como directorio: " << project.nombre << std::endl;
      menuProyecto(project.nombre, usuarioUID); // Lanzar menu
    } else {
      std::cerr << " No se pudo crear info.txt." << std::endl;
    }
  } else {
    std::cerr << " No se pudo crear el directorio del proyecto." << std::endl;
  }
}

// === Abrir proyecto existente ===
void abrirProyectoExistente() {
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

  std::cout << "\n--- Proyectos Disponibles ---" << std::endl;
  for (size_t i = 0; i < proyectos.size(); ++i) {
    std::cout << i + 1 << ". " << proyectos[i] << std::endl;
  }

  int eleccion;
  std::cout << "Selecciona un proyecto (número): ";
  std::cin >> eleccion;
  std::cin.ignore();

  if (eleccion < 1 || eleccion > (int)proyectos.size()) {
    std::cout << "Opción inválida" << std::endl;
    return;
  }

  std::string uid;
  std::cout << "Tu UID (para registrar cambios): ";
  std::getline(std::cin, uid);

  std::string rutaProyecto = proyectos[eleccion - 1];
  menuProyecto(rutaProyecto, uid);
}


// === main ===
int main() {
  std::string opcion;
  std::cout << "=== Gestor de Proyectos ===" << std::endl;
  std::cout << "1. Crear nuevo proyecto" << std::endl;
  std::cout << "2. Abrir proyecto existente" << std::endl;
  std::cout << "Elige opción: ";
  std::getline(std::cin, opcion);

  if (opcion == "1") {
    std::string uid;
    std::cout << "Tu UID: ";
    std::getline(std::cin, uid);
    crearProyecto(uid);
  } else if (opcion == "2") {
    abrirProyectoExistente();
  } else {
    std::cout << "Opción inválida" << std::endl;
  }
  return 0;
}
