#include "../include/User/Uid.h"


Uid::Uid (const Uid& other) {
  *this = other;
}

bool Uid::operator ==(const Uid& other) const {
  return this->uid_ == other.uid_;
}

bool  Uid::operator !=(const Uid& other) const {
  return this->uid_ != other.uid_;
}
bool  Uid::operator <(const Uid& other) const {
  return this->uid_ < other.uid_;
}
bool  Uid::operator <=(const Uid& other) const {
  return this->uid_ <= other.uid_;
}
/* bool  Uid::operator >(const Uid& other) const {
  return this->uid_ > other.uid_;
} */
bool  Uid::operator >=(const Uid& other) const {
  return this->uid_ >= other.uid_;
}
Uid& Uid::operator +=(const Uid& other) {
  this->uid_ = this->uid_ + other.uid_;
  return *this;
}



Uid& Uid::operator =(const Uid& other) {
  this->uid_ = other.uid_;
  return *this;
}


std::ostream& operator<<(std::ostream& os, const Uid& uid) {
  os << uid.get_uid();
  return os;
}
