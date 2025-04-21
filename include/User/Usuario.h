#ifndef USUARIO_H_
#define USUARIO_H_

#include "Uid.h"

#include <string>

class Usuario {
 public:
  Usuario (const std::string& name, const std::string password, const Uid& uid) : name_(name), password_(password), uid_(uid) {}
  const Uid& get_uid() const {return uid_;}
 private:
  std::string name_;
  std::string password_;
  Uid uid_;
};

#endif //USUARIO_H_