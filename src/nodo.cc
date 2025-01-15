#include "nodo.h"

Nodo::Nodo(int x, int y, int x_meta, int y_meta, int g) {
  x_ = x;
  y_ = y;

  // Calcular la heurística h(n)
  int W = 3;  // Peso W
  h_ = (abs(x_meta - x) + abs(y_meta - y)) * W;

  // Coste acumulado g(n)
  g_ = g;

  // Coste total f(n) = g(n) + h(n)
  f_ = h_ + g_;
}


// void Nodo::set_padre(Nodo* padre) {
//   padre_ = padre;
// }
