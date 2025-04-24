#include "../include/Login/CrearCuenta.h"


void CrearCuenta::AñadirCuenta(HashTable<Uid>& base_datos) {
  //Buscar si el uid ya exite, en ese caso, no añadirla ya que ya está añadida
  if (base_datos.search(this->user_.get_uid())) {
    
  }
}
