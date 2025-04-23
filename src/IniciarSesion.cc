#include "../include/Login/IniciarSesion.h"


bool IniciarSesion::ValidarCuenta(HashTable<Uid>& base_datos_cuentas) {
  //Si se encuentra el uid en la tabla hash es que el usuario está registrado
  return base_datos_cuentas.search(this->user_.get_uid());
}