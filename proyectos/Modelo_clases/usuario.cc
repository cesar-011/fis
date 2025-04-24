#include "usuario.h"

Usuario::Usuario(const std::string& uid) : uid_(uid) {}

std::string Usuario::getUID() const {
  return uid_;
}
