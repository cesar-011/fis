#ifndef CREARCUENTA_H_
#define CREARCUENTA_H_

#include "../User/Usuario.h"
#include "../HashTable/HashTable.h"

#include <fstream>

class CrearCuenta {
 public:
  CrearCuenta (const Usuario& user) : user_(user) {}
  void AñadirCuenta(HashTable<Uid>&);
 private:
  Usuario user_;
};

#endif //CREARCUENTA_H_const