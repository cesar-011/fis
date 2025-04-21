#ifndef DISPERSIONFUNCTION_H_
#define DISPERSIONFUNCTION_H_

template <class Key>
class DispersionFunction {
  public:
   virtual unsigned operator()(const Key&) const = 0;
};

#endif //DISPERSIONFUNCTION_H_