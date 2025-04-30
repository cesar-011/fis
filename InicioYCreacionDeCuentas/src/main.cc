#include "../include/Login/IniciarSesion.h"
#include "../include/HashTable/DispersionFunction/SumBased.h"
#include "../include/User/Usuario.h"
#include "../include/Proyects/gestor_de_proyectos.h"
#include "../include/Proyects/proyecto.h"
#include "../include/Proyects/tarea.h"
#include "../include/HashTable/HashTable.h"
#include "../include/Login/CrearCuenta.h"

#include <iostream>
#include <fstream>
#include <limits>


int main() {

/*
  SumBased<Uid> df(6);
  HashTable<Uid> ht(6, df);
  std::ifstream file ("../data/usuarios_registrados");
  ht.CreateDataBase(file);
  Uid uid(1234);
  Usuario usuario1("Laura", "ey", uid);
  IniciarSesion iniciar(usuario1);
  if (iniciar.ValidarCuenta(ht)) {
    std::cout<<"Encontrado"<<'\n';
  }
*/

  SumBased<Uid> df(6);
  HashTable<Uid> ht(6, df);
  
  std::ifstream file("../data/usuarios_registrados");
  if (!file) {
    std::cerr << "Error al abrir el archivo de usuarios.\n";
    return 1;
  }
  ht.CreateDataBase(file);
  file.close();

  std::cout << "Bienvenido al Gestor de Proyectos\n";
  std::cout << "1. Iniciar sesión\n";
  std::cout << "2. Registrarse\n";
  std::cout << "3. Salir\n";
  std::cout << "Seleccione una opción (1 o 2 o 3): ";

  int opcion;
  std::cin >> opcion;
  std::cin.ignore();

  if (opcion == 3) {
    std::cout << "Saliendo del programa...\n";
    return 0;
  }

  Usuario usuario;
  if (opcion == 1) {
    std::string nombre, password;
    int uid;

    std::cout << "Nombre de usuario: ";
    std::getline(std::cin, nombre);

    std::cout << "Contraseña: ";
    std::getline(std::cin, password);

    std::cout << "UID: ";
    std::cin >> uid;
    std::cin.ignore();

    usuario = Usuario(nombre, password, Uid(uid));
    IniciarSesion inicio(usuario);

    if (inicio.ValidarCuenta(ht)) {
      std::cout << "Usuario autenticado correctamente.\n";
    } else {
      std::cout << "Usuario o contraseña incorrectos.\n";
      return 1;
    }
  } else if (opcion == 2) {
    std::string nombre, password;
    int uid;

    std::cout << "Nombre de usuario: ";
   // std::cin.ignore();
    std::getline(std::cin, nombre);

    std::cout << "Contraseña: ";
    std::getline(std::cin, password);

    std::cout << "UID (número entero): ";
    std::cin >> uid;
    std::cin.ignore();

    usuario = Usuario(nombre, password, Uid(uid));
    std::fstream db_file("../data/usuarios_registrados", std::ios::app);
    CrearCuenta nueva(usuario, db_file);
    nueva.AñadirCuenta(ht);
    db_file.close();

    std::cout << "Cuenta creada exitosamente.\n";
  } else {
    std::cout << "Opción no válida.\n";
    return 1;
  }


  std::string opcion2;
  std::cout << "=== GESTOR DE PROYECTOS ===" << std::endl;
  std::cout << "1. Crear nuevo proyecto" << std::endl;
  std::cout << "2. Abrir proyecto existente" << std::endl;
  std::cout << "3. Salir" << std::endl;
  std::cout << "Opción: ";
  std::getline(std::cin, opcion2);


  if (opcion2 == "3") {
    std::cout << "Saliendo del programa...\n";
    return 0;
  }

  if (opcion2 == "1") {
    std::string uid;
    std::cout << "Tu UID: ";
    std::getline(std::cin, uid);
    Usuario usuario2(uid);
    //Corregir la clase usuario para solo trabajar con una
    Proyecto proyecto = GestorDeProyectos::crearProyecto(usuario2);
    proyecto.abrirMenuInteractivo(uid);
  } else if (opcion2 == "2") {
    GestorDeProyectos::abrirProyectoExistente();
  } else {
    std::cout << "Opción no válida" << std::endl;
  }

  return 0;
}

