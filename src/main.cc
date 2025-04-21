#include "../include/Login/IniciarSesion.h"
#include "../include/HashTable/DispersionFunction/SumBased.h"


int main() {
  SumBased<Uid> df(6);
  HashTable<Uid> ht(6, df);
  std::ifstream file ("../data/usuarios_registrados");
  ht.CreateDataBase(file);
  Uid uid(8798);
  Usuario usuario("Cesar", "contraseña", uid);
  IniciarSesion iniciar;
  if (iniciar.ValidarCuenta(ht, usuario)) {
    std::cout<<"Encontrado"<<'\n';
  }

}