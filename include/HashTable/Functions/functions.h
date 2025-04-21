#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

//--------------------------------------------------------Funciones para DynamicSquence-----------------------------------------------//

/// @brief Funcion para realizar la particion que se usara en la funcion quicksort
/// @tparam Key 
/// @param l Indice menor
/// @param h Indice mayor
/// @param sequence La secuencia que se quiere ordenar
/// @return La parte con el pivote en su posicion final
template <typename Key>
int Partition(int l, int h, std::vector<Key>& sequence) {
  Key pivot = sequence[l];
  int i = l;
  int j = h;
  // Mientras i sea < j, intercambiar los elementos para que a un lado queden los menores y al otro lado los mayores
  while (i < j) {
    while (i <= h && sequence[i] <= pivot) {
      i++;
    }
    while (j >= l && sequence[j] > pivot) {
      j--;
    }
    if (i < j) {
      std::swap(sequence[i], sequence[j]);
    }
  }
  // Al final, cambiamos el pivote con la posicion de j, y el pivote quedará en su posicion final
  std::swap(sequence[l], sequence[j]);
  //Retornamos la posicion de particion
  return j;
}

/// @brief Funcion Quicksort para ordenar una secuencia
/// @tparam Key 
/// @param l Indice menor
/// @param h Indice mayor
/// @param sequence La secuencia ordenada
template <typename Key>
void QuickSort(int l, int h, std::vector<Key>& sequence) {
  if (l < h) {
    int j = Partition(l, h, sequence);
    QuickSort(l, j - 1, sequence);
    QuickSort(j + 1, h, sequence);
  }
}

/// @brief Funcion para hacer una busqueda binaria de forma recursiva
/// @tparam Key 
/// @param squence La secuencia donde se quiere buscar
/// @param i Indice izquierdo
/// @param d Indice derecho
/// @param elem El elemento que se quiere buscar
/// @return La posición donde se encontró. -1 en caso de no encontrarse
template <typename Key>
int BinarySearch(const std::vector<Key>& squence, int i, int d, const Key& elem) {
  if (i > d) return -1;
  int c = (i + d) / 2;
  if (squence[c] == elem) return c;
  if (elem < squence[c]) return BinarySearch(squence, i, c - 1, elem);
  else return BinarySearch(squence, c + 1, d, elem);
}

/// @brief Funcion para insertar valor k en una secuencia de forma ordenada
/// @tparam Key 
/// @param squence La secuencia donde se quiere insertar
/// @param k El valor a insertar
template <typename Key>
void InsertSorted(std::vector<Key>& squence, const Key& k) {
  bool is_insert = false;
  for (int i = 0; i < squence.size() && is_insert; i++) {
    if (k <= squence[i]) {
      //Si k el <= que el valor que se está mirando, lo insertamos
      squence.insert(squence.begin() + i, k); 
      is_insert = true;
    }
  }
  //Si no, lo insertamos al final
  squence.push_back(k);
}

//---------------------------------------------------------Funciones para StaticSquence----------------------------------------------//

/// @brief Funcion para hacer una busqueda lineal en una secuencia
/// @tparam Key 
/// @param squence La secuencia donde se busca
/// @param block_size EL tamaño de la secuencia
/// @param k El valor a buscar
/// @return El indice donde se encontró. -1 enn caso de no encontrarse
template <class Key>
int LinealSearch(const Key* squence, int block_size, const Key& k) {
  for (int i = 0; i < block_size; i++) {
    if (squence[i] == k) {
      return i;
    }
  }
  return -1;
}

//-------------------------------------------------------------main--------------------------------------------------------------//



#endif //FUNCTIONS_H_