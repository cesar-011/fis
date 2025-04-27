#include "usuario.h"

Usuario2::Usuario2(const std::string& uid) : uid_(uid) {}

std::string Usuario2::getUID() const {
  return uid_;
}
