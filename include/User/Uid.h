#ifndef UID_H_
#define UID_H_

#include <iostream>


class Uid {
 public:
  Uid (const int uid) : uid_(uid) {}
  Uid (const Uid&);
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

 private:
  int uid_;
};





#endif //UID_H_