#ifndef UID_H_
#define UID_H_

#include <iostream>
#include <string>

class Uid {
 public:
  Uid (const int uid) : uid_(uid) {}
  Uid (const Uid&);
  Uid () = default;
  int get_uid() const {return uid_;}
  operator int() {return this->uid_;}
  bool operator ==(const Uid&) const;
  bool operator !=(const Uid&) const;
  bool operator <(const Uid&) const;
  bool operator <=(const Uid&) const;
/*   bool operator >(const Uid&) const; */
  bool operator >=(const Uid&) const;
  Uid& operator =(const Uid&);
  Uid& operator +=(const Uid&);
  friend std::ostream& operator <<(std::ostream& os, const Uid& uid);
  std::string to_string() const;
  Uid(const std::string& str_uid) : uid_(std::stoi(str_uid)) {}

 private:
  int uid_;
};





#endif //UID_H_