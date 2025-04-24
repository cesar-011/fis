#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario {
 public:
  Usuario(const std::string& uid);
  std::string getUID() const;

 private:
  std::string uid_;
};

#endif
