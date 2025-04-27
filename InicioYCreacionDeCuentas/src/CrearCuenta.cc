#include "../include/Login/CrearCuenta.h"


void CrearCuenta::AñadirCuenta(HashTable<Uid>& base_datos) {
  //Buscar si el uid ya exite, en ese caso, no añadirla ya que ya está añadida
  if (base_datos.search(this->user_.get_uid())) {
    std::cerr<<"La cuenta que estás intentando crear ya está creada"<<'\n';
    //Si no existe, añadir el usuario a la base de datos de usuarios
  } else {
    this->base_datos_ << this->user_.get_name() <<":"<<this->user_.get_password()<<":"<<this->user_.get_uid();
  }

}
