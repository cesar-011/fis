#ifndef INICIARSESION_H_
#define INICIARSESION_H_


#include "../User/Usuario.h"
#include "../HashTable/HashTable.h"

#include <fstream>



class IniciarSesion {
 public:
  bool ValidarCuenta(HashTable<Uid>&, const Usuario&);
  

 private:
  Usuario user;

};


#endif //INICIARSESION_H_