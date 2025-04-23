#include "../include/Login/IniciarSesion.h"
#include "../include/HashTable/DispersionFunction/SumBased.h"


int main() {
  SumBased<Uid> df(6);
  HashTable<Uid> ht(6, df);
  std::ifstream file ("../data/usuarios_registrados");
  ht.CreateDataBase(file);
  Uid uid(1234);
  Usuario usuario("Laura", "ey", uid);
  IniciarSesion iniciar(usuario);
  if (iniciar.ValidarCuenta(ht)) {
    std::cout<<"Encontrado"<<'\n';
  }
}