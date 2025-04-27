#ifndef SUMBASED_H_
#define SUMBASED_H_

#include "DispersionFunction.h"

template <class Key>
class SumBased : public DispersionFunction<Key> {
  public:
   //Constructor
   SumBased(const int table_size) : table_size_(table_size) {}
   virtual unsigned operator()(const Key&) const override;

  private:
   int table_size_; //Tamaño de la tabla
};

/// @brief Sobrecarga del operador funcion para poder hacer la funcion de dispersion SumBased
/// @tparam Key 
/// @param k El valor con el que se opera
/// @return El resultado de la operacion
template <class Key>
unsigned SumBased<Key>::operator()(const Key& k) const {
  Key temp = k;
  Key sum = 0;
  // Se extraen los valores de k y se suman entre ellos
  while (temp > 0) {
    sum += temp % 10;
    temp = temp / 10;
  }
  // Se devuelve la suma de los valores de k con el modulo del tamaño de la tabla
  return sum % table_size_;
}

#endif //SUMBASED_H_