#include "../include/Login/IniciarSesion.h"


bool IniciarSesion::ValidarCuenta(HashTable<Uid>& base_datos_cuentas) {
  bool coincide_nombre = false;
  bool coincide_contraseña = false;
  //Si se encuentra el uid en la tabla hash es que el usuario está registrado
  bool existe = base_datos_cuentas.search(this->user_.get_uid());
  
  for (int i = 0; i < base_datos_cuentas.get_users().size(); i++) {
    if (base_datos_cuentas.get_users()[i].get_uid() == this->user_.get_uid()){
      if (base_datos_cuentas.get_users()[i].get_name() == this->user_.get_name()) {
        coincide_nombre = true;
      }
      if (base_datos_cuentas.get_users()[i].get_password() == this->user_.get_password()) {
        coincide_contraseña= true;
      }
    }
  }
  

  return (existe && coincide_contraseña && coincide_nombre);

}