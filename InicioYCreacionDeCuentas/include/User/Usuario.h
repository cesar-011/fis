#ifndef USUARIO_H_
#define USUARIO_H_

#include "Uid.h"  // Si prefieres mantener una clase Uid externa
#include <string>

class Usuario {
 public:
  // Constructor completo
  Usuario(const std::string& name, const std::string& password, const Uid& uid)
    : name_(name), password_(password), uid_(uid) {}

  // Constructor solo con string para uid
  Usuario(const std::string& uid_str)
    : uid_(uid_str) {}

  Usuario() = default;

  // Getters
  const Uid& get_uid() const { return uid_; }
  const std::string& get_name() const { return name_; }
  const std::string& get_password() const { return password_; }
  std::string getUID() const { return uid_.to_string(); } 

  // Setters
  void set_name(const std::string& name) { name_ = name; }
  void set_password(const std::string& password) { password_ = password; }

 private:
  std::string name_;
  std::string password_;
  Uid uid_;
};

#endif  // USUARIO_H_




/*#ifndef USUARIO_H_
#define USUARIO_H_

#include "Uid.h"

#include <string>

class Usuario {
 public:
  Usuario (const std::string& name, const std::string password, const Uid& uid) : name_(name), password_(password), uid_(uid) {}
  Usuario () = default;
  const Uid& get_uid() const {return uid_;}
  const std::string& get_name () const {return name_;}
  const std::string& get_password () const {return password_;}
  void set_name(const std::string& name) {name_ = name;}
  void set_password(const std::string& password) {password_ = password;}
 private:
  std::string name_;
  std::string password_;
  Uid uid_;
};

#endif //USUARIO_H_

*/