#ifndef SQUENCE_H_
#define SQUENCE_H_

template <class Key>
class Squence {
  public:
   virtual bool search(const Key& k) = 0;
   virtual bool insert(const Key& k) = 0;
   virtual void Print() const = 0;
};

#endif //SQUENCE_H_