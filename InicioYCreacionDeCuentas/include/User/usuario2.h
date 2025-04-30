#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario2 {
 public:
  Usuario2(const std::string& uid);
  std::string getUID() const;

 private:
  std::string uid_;
};

#endif
