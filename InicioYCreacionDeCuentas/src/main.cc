#include "../include/Login/IniciarSesion.h"
#include "../include/HashTable/DispersionFunction/SumBased.h"
#include "../../proyectos/Modelo_sin_clases/Modelo_clases/usuario.h"
#include "../../proyectos/Modelo_sin_clases/Modelo_clases/gestor_de_proyectos.h"

int main() {
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
    Usuario2 usuario2(uid);
    //Corregir la clase usuario para solo trabajar con una
    Proyecto proyecto = GestorDeProyectos::crearProyecto(usuario2);
    proyecto.abrirMenuInteractivo(uid);
  } else if (opcion == "2") {
    GestorDeProyectos::abrirProyectoExistente();
  } else {
    std::cout << "Opción no válida" << std::endl;
  }

  return 0;
}