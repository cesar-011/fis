#ifndef HASHTABLE_H_
#define HASHTABLE_H_


#include "Squence/DynamicSquence.h"
#include "DispersionFunction/DispersionFunction.h"




#include <iostream>
#include <fstream>
#include <sstream>



template <class Key, class Container = DynamicSquence<Key>>
class HashTable : public Squence<Key> {
public:
  HashTable(unsigned table_size, DispersionFunction<Key>& fd);
  void CreateDataBase(std::ifstream& file);
  virtual bool search(const Key& k) override;
  virtual bool insert(const Key& k) override;
  virtual void Print() const override;

private:
  DynamicSquence<Key>* table_;  //Puntero que apunta a las diferentes posiciones de la tabla
  int table_size_;  //Tamaño de la tabla
  DispersionFunction<Key>& fd_; //Funcion de dispersion
};


//------------------------------------------------------------DYNAMIC SQUENCE----------------------------------------------------

/// @brief Constructor para HashTable abierta
/// @tparam Key 
/// @param table_size Tamaño de la tabla
/// @param fd Funcion de dispersion
template <class Key, class Container>
HashTable<Key, Container>::HashTable(unsigned table_size, DispersionFunction<Key>& fd) : fd_(fd) {
  table_size_ = table_size;
  table_ = new Container[table_size_];
}


template <class Key, class Container>
void HashTable<Key, Container>::CreateDataBase(std::ifstream& file) {
  std::string line;
  while (std::getline(file, line)) {
    std::stringstream stream(line);
    std::string dummy, uid_str;
    std::getline(stream, dummy, ':');
    std::getline(stream, dummy, ':');
    std::getline(stream, uid_str);
    int uids = std::stoi(uid_str);

    Uid uid(uids);
    this->insert(uid);
  }
}


/// @brief Metodo para buscar una clave en la tabla usando la funcion de dispersion
/// @tparam Key 
/// @param k Clave a buscar
/// @return Si se encontro o no
template <class Key, class Container>
bool HashTable<Key, Container>::search(const Key& k) {
  unsigned indice = fd_(k);
  return table_[indice].search(k);
}

/// @brief Metodo para insertar una clave en la tabla usandola funcion de dispersion
/// @tparam Key 
/// @param k Clave a insertar 
/// @return Si se pudo insertar o no
template <class Key, class Container>
bool HashTable<Key, Container>::insert(const Key& k) {
  unsigned indice = fd_(k);
  return table_[indice].insert(k);
}

/// @brief Metodo para imprimir la tabla
/// @tparam Key 
template <class Key, class Container>
void HashTable<Key, Container>::Print() const {
  for (unsigned i = 0; i < table_size_; i++) {
    std::cout << "Índice " << i << ": ";
    table_[i].Print();
  }
}

#endif //HASHTABLE_H_