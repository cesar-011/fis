#ifndef CREARCUENTA_H_
#define CREARCUENTA_H_

#include "../User/Usuario.h"
#include "../HashTable/HashTable.h"

#include <fstream>

class CrearCuenta {
 public:
  CrearCuenta (const Usuario& user, std::fstream& base_datos) : user_(user), base_datos_(base_datos) {}
  void AñadirCuenta(HashTable<Uid>&);
 private:
  Usuario user_;
  std::fstream& base_datos_;
};

#endif //CREARCUENTA_H_const