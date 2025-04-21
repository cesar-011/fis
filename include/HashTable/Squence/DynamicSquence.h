#ifndef DYNAMICSQUENCE_H_
#define DYNAMICSQUENCE_H_

#include "Squence.h"
#include "../Functions/functions.h"


#include <vector>
#include <iostream>

template <class Key>
class DynamicSquence : public Squence<Key> {
  public:
   virtual bool search(const Key& k) override;
   virtual bool insert(const Key& k) override;
   virtual void Print() const override;

  private:
   std::vector<Key> dynamic_squence_; //vector para guardar los valores de la hash_table sin limite de espacio
};

/// @brief Metodo para buscar un valor en la secuencia
/// @tparam Key 
/// @param k El valor a buscar
/// @return Si se encontró o no
template <class Key>
bool DynamicSquence<Key>::search(const Key& k){
  //Se podria hacer una funcion qu compruebe si el vector ya está ordenado para no hacer siempre Quicksort
  QuickSort(0, dynamic_squence_.size() - 1, dynamic_squence_);
  int pos = BinarySearch(dynamic_squence_, 0, dynamic_squence_.size() - 1, k);
  return pos != -1;
}

/// @brief Metodo para insertar un valor en la secuencia
/// @tparam Key 
/// @param k Valor a insertar
/// @return Si se pudo insertar o no
template <class Key>
bool DynamicSquence<Key>::insert(const Key& k) {
  InsertSorted(dynamic_squence_, k);
  return true;
}

/// @brief Metodo para imprimir la secuencia
/// @tparam Key 
template <class Key>
void DynamicSquence<Key>::Print() const {
  for (const auto& item : dynamic_squence_) {
    std::cout << item << " ";
  }
  std::cout << std::endl;
}

#endif //DYNAMICSQUENCE_H_