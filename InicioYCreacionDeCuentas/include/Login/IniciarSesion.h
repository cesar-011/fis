#ifndef INICIARSESION_H_
#define INICIARSESION_H_


#include "../User/Usuario.h"
#include "../HashTable/HashTable.h"

#include <fstream>



class IniciarSesion {
 public:
  IniciarSesion(const Usuario user) : user_(user){}
  bool ValidarCuenta(HashTable<Uid>&);
  

 private:
  Usuario user_;

};


#endif //INICIARSESION_H_