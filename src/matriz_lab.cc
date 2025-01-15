#include "matriz_lab.h"

MatrizLab::MatrizLab(int** matriz_con_mapa, int filas, int columnas, int x_inicio, int y_inicio, int x_meta, int y_meta) {
  filas_ = filas;
  columnas_ = columnas;
  x_inicio_ = x_inicio;
  y_inicio_ = y_inicio;
  x_meta_ = x_meta;
  y_meta_ = y_meta;
  matriz_con_mapa_ = matriz_con_mapa;
}

int MatrizLab::get_filas() const {
  return filas_;
}

int MatrizLab::get_columnas() const {
  return columnas_;
}

int MatrizLab::get_x_inicio() const {
  return x_inicio_;
}

int MatrizLab::get_y_inicio() const {
  return y_inicio_;
}

int MatrizLab::get_x_meta() const {
  return x_meta_;
}

int MatrizLab::get_y_meta() const {
  return y_meta_;
}

std::set<Nodo> MatrizLab::get_abiertos() const {
  return abiertos_;
}

std::set<Nodo> MatrizLab::get_cerrados() const {
  return cerrados_;
}

std::map<std::pair<int, int>, std::pair<int, int> > MatrizLab::get_padres() const {
  return padres_;
}

void MatrizLab::A_estrella() {
  Nodo nodo_inicial(x_inicio_, y_inicio_, x_meta_, y_meta_, 0);
  abiertos_.insert(nodo_inicial);
  Nodo auxiliar_nodo;
  std::set<Nodo> vecinos_nodo_actual;
  while (!abiertos_.empty()) { // mientras no esté vacío
    auxiliar_nodo = *abiertos_.begin(); // nodo con menor f (nodo actual)
    // si el nodo actual es el nodo meta
    if (auxiliar_nodo.get_x() == x_meta_ && auxiliar_nodo.get_y() == y_meta_) {
      std::cout << "Nodo meta encontrado" << std::endl;
      return;
    }
    // si no es el nodo meta, lo eliminamos de la lista de abiertos y lo añadimos a la lista de cerrados
    abiertos_.erase(auxiliar_nodo);
    cerrados_.insert(auxiliar_nodo);
    // explorar los vecinos del nodo actual
    explorar_vecinos(auxiliar_nodo);

  }
}

void MatrizLab::explorar_vecinos(Nodo& nodo_actual) {
  // cuando avanzo recto, el coste es 5
  // cuando avanzo en diagonal, el coste es 7
  // si el vecino está en la lista de cerrados, lo ignoro
  // si el vecino está en la lista de abiertos, compruebo si el nuevo camino es mejor
  // si el vecino no está en ninguna lista, lo añado a la lista de abiertos
  
  // vecino arriba
  if (nodo_actual.get_x() - 1 > filas_ && matriz_con_mapa_[nodo_actual.get_x() - 1][nodo_actual.get_y()] != 1) {
    // comprueba si el vecino no se sale de la matriz (no puede ser menor que 0) y si no es una pared
    Nodo vecino(nodo_actual.get_x() - 1, nodo_actual.get_y(), x_meta_, y_meta_, nodo_actual.get_g() + 5);
    // si el vecino no está ni en la lista de abiertos ni en la de cerrados
    if (abiertos_.find(vecino) == abiertos_.end() && cerrados_.find(vecino) == cerrados_.end()) {
      abiertos_.insert(vecino);
      // guardo el padre del vecino
      padres_[std::make_pair(vecino.get_x(), vecino.get_y())] = std::make_pair(nodo_actual.get_x(), nodo_actual.get_y());
    }
    // si el vecino está en la lista de abiertos
    if (abiertos_.find(vecino) != abiertos_.end()) {
      Nodo auxiliar = *abiertos_.find(vecino); // obtengo el nodo de la lista de abiertos
      if (vecino.get_g() < auxiliar.get_g()) {
        abiertos_.erase(auxiliar);
        abiertos_.insert(vecino);
        // cambio el padre del vecino
        padres_[std::make_pair(vecino.get_x(), vecino.get_y())] = std::make_pair(nodo_actual.get_x(), nodo_actual.get_y());
      }
    }
    // en otro caso, el vecino está en la lista de cerrados y lo ignoro
  }

  // vecino abajo
  if (nodo_actual.get_x() + 1 < filas_ && matriz_con_mapa_[nodo_actual.get_x() + 1][nodo_actual.get_y()] != 1) {
    Nodo vecino(nodo_actual.get_x() + 1, nodo_actual.get_y(), x_meta_, y_meta_, nodo_actual.get_g() + 5);
    // si el vecino no está ni en la lista de abiertos ni en la de cerrados
    if (abiertos_.find(vecino) == abiertos_.end() && cerrados_.find(vecino) == cerrados_.end()) {
      abiertos_.insert(vecino);
      // cambio el padre del vecino
      padres_[std::make_pair(vecino.get_x(), vecino.get_y())] = std::make_pair(nodo_actual.get_x(), nodo_actual.get_y());
    }
    // si el vecino está en la lista de abiertos
    if (abiertos_.find(vecino) != abiertos_.end()) {
      Nodo auxiliar = *abiertos_.find(vecino);
      if (vecino.get_g() < auxiliar.get_g()) {
        abiertos_.erase(auxiliar);
        abiertos_.insert(vecino);
        // cambio el padre del vecino
        padres_[std::make_pair(vecino.get_x(), vecino.get_y())] = std::make_pair(nodo_actual.get_x(), nodo_actual.get_y());
      }
    }
  }
  // vecino izquierda
  if (nodo_actual.get_y() - 1 > columnas_ && matriz_con_mapa_[nodo_actual.get_x()][nodo_actual.get_y() - 1] != 1) {
    Nodo vecino(nodo_actual.get_x(), nodo_actual.get_y() - 1, x_meta_, y_meta_, nodo_actual.get_g() + 5);
    // si el vecino no está ni en la lista de abiertos ni en la de cerrados
    if (abiertos_.find(vecino) == abiertos_.end() && cerrados_.find(vecino) == cerrados_.end()) {
      abiertos_.insert(vecino);
      // cambio el padre del vecino
      padres_[std::make_pair(vecino.get_x(), vecino.get_y())] = std::make_pair(nodo_actual.get_x(), nodo_actual.get_y());
    }
    // si el vecino está en la lista de abiertos
    if (abiertos_.find(vecino) != abiertos_.end()) {
      Nodo auxiliar = *abiertos_.find(vecino);
      if (vecino.get_g() < auxiliar.get_g()) {
        abiertos_.erase(auxiliar);
        abiertos_.insert(vecino);
        // cambio el padre del vecino
        padres_[std::make_pair(vecino.get_x(), vecino.get_y())] = std::make_pair(nodo_actual.get_x(), nodo_actual.get_y());
      }
    }
  }
  // vecino derecha
  if (nodo_actual.get_y() + 1 < columnas_ && matriz_con_mapa_[nodo_actual.get_x()][nodo_actual.get_y() + 1] != 1) {
    Nodo vecino(nodo_actual.get_x(), nodo_actual.get_y() + 1, x_meta_, y_meta_, nodo_actual.get_g() + 5);
    // si el vecino no está ni en la lista de abiertos ni en la de cerrados
    if (abiertos_.find(vecino) == abiertos_.end() && cerrados_.find(vecino) == cerrados_.end()) {
      abiertos_.insert(vecino);
      // cambio el padre del vecino
      padres_[std::make_pair(vecino.get_x(), vecino.get_y())] = std::make_pair(nodo_actual.get_x(), nodo_actual.get_y());
    }
    // si el vecino está en la lista de abiertos
    if (abiertos_.find(vecino) != abiertos_.end()) {
      Nodo auxiliar = *abiertos_.find(vecino);
      if (vecino.get_g() < auxiliar.get_g()) {
        abiertos_.erase(auxiliar);
        abiertos_.insert(vecino);
        // cambio el padre del vecino
        padres_[std::make_pair(vecino.get_x(), vecino.get_y())] = std::make_pair(nodo_actual.get_x(), nodo_actual.get_y());
      }
    }
  }
  // vecino arriba izquierda (diagonal => coste 7)
  if (nodo_actual.get_x() - 1 > filas_ && nodo_actual.get_y() - 1 > columnas_ && matriz_con_mapa_[nodo_actual.get_x() - 1][nodo_actual.get_y() - 1] != 1) {
    Nodo vecino(nodo_actual.get_x() - 1, nodo_actual.get_y() - 1, x_meta_, y_meta_, nodo_actual.get_g() + 7);
    // si el vecino no está ni en la lista de abiertos ni en la de cerrados
    if (abiertos_.find(vecino) == abiertos_.end() && cerrados_.find(vecino) == cerrados_.end()) {
      abiertos_.insert(vecino);
      // cambio el padre del vecino
      padres_[std::make_pair(vecino.get_x(), vecino.get_y())] = std::make_pair(nodo_actual.get_x(), nodo_actual.get_y());
    }
    // si el vecino está en la lista de abiertos
    if (abiertos_.find(vecino) != abiertos_.end()) {
      Nodo auxiliar = *abiertos_.find(vecino);
      if (vecino.get_g() < auxiliar.get_g()) {
        abiertos_.erase(auxiliar);
        abiertos_.insert(vecino);
        // cambio el padre del vecino
        padres_[std::make_pair(vecino.get_x(), vecino.get_y())] = std::make_pair(nodo_actual.get_x(), nodo_actual.get_y());
      }
    }
  }
  // vecino arriba derecha
  if (nodo_actual.get_x() - 1 > filas_ && nodo_actual.get_y() + 1 < columnas_ && matriz_con_mapa_[nodo_actual.get_x() - 1][nodo_actual.get_y() + 1] != 1) {
    Nodo vecino(nodo_actual.get_x() - 1, nodo_actual.get_y() + 1, x_meta_, y_meta_, nodo_actual.get_g() + 7);
    // si el vecino no está ni en la lista de abiertos ni en la de cerrados
    if (abiertos_.find(vecino) == abiertos_.end() && cerrados_.find(vecino) == cerrados_.end()) {
      abiertos_.insert(vecino);
      // cambio el padre del vecino
      padres_[std::make_pair(vecino.get_x(), vecino.get_y())] = std::make_pair(nodo_actual.get_x(), nodo_actual.get_y());
    }
    // si el vecino está en la lista de abiertos
    if (abiertos_.find(vecino) != abiertos_.end()) {
      Nodo auxiliar = *abiertos_.find(vecino);
      if (vecino.get_g() < auxiliar.get_g()) {
        abiertos_.erase(auxiliar);
        abiertos_.insert(vecino);
        // cambio el padre del vecino
        padres_[std::make_pair(vecino.get_x(), vecino.get_y())] = std::make_pair(nodo_actual.get_x(), nodo_actual.get_y());
      }
    }
  }
  // vecino abajo izquierda
  if (nodo_actual.get_x() + 1 < filas_ && nodo_actual.get_y() - 1 > columnas_ && matriz_con_mapa_[nodo_actual.get_x() + 1][nodo_actual.get_y() - 1] != 1) {
    Nodo vecino(nodo_actual.get_x() + 1, nodo_actual.get_y() - 1, x_meta_, y_meta_, nodo_actual.get_g() + 7);
    // si el vecino no está ni en la lista de abiertos ni en la de cerrados
    if (abiertos_.find(vecino) == abiertos_.end() && cerrados_.find(vecino) == cerrados_.end()) {
      abiertos_.insert(vecino);
      // cambio el padre del vecino
      padres_[std::make_pair(vecino.get_x(), vecino.get_y())] = std::make_pair(nodo_actual.get_x(), nodo_actual.get_y());
    }
    // si el vecino está en la lista de abiertos
    if (abiertos_.find(vecino) != abiertos_.end()) {
      Nodo auxiliar = *abiertos_.find(vecino);
      if (vecino.get_g() < auxiliar.get_g()) {
        abiertos_.erase(auxiliar);
        abiertos_.insert(vecino);
        // cambio el padre del vecino
        padres_[std::make_pair(vecino.get_x(), vecino.get_y())] = std::make_pair(nodo_actual.get_x(), nodo_actual.get_y());
      }
    }
  }
  // vecino abajo derecha
  if (nodo_actual.get_x() + 1 < filas_ && nodo_actual.get_y() + 1 < columnas_ && matriz_con_mapa_[nodo_actual.get_x() + 1][nodo_actual.get_y() + 1] != 1) {
    Nodo vecino(nodo_actual.get_x() + 1, nodo_actual.get_y() + 1, x_meta_, y_meta_, nodo_actual.get_g() + 7);
    // si el vecino no está ni en la lista de abiertos ni en la de cerrados
    if (abiertos_.find(vecino) == abiertos_.end() && cerrados_.find(vecino) == cerrados_.end()) {
      abiertos_.insert(vecino);
      // cambio el padre del vecino
      padres_[std::make_pair(vecino.get_x(), vecino.get_y())] = std::make_pair(nodo_actual.get_x(), nodo_actual.get_y());
    }
    // si el vecino está en la lista de abiertos
    if (abiertos_.find(vecino) != abiertos_.end()) {
      Nodo auxiliar = *abiertos_.find(vecino);
      if (vecino.get_g() < auxiliar.get_g()) {
        abiertos_.erase(auxiliar);
        abiertos_.insert(vecino);
        // cambio el padre del vecino
        padres_[std::make_pair(vecino.get_x(), vecino.get_y())] = std::make_pair(nodo_actual.get_x(), nodo_actual.get_y());
      }
    }
  }  
}

void MatrizLab::imprimir_padres() {
  for (auto it = padres_.begin(); it != padres_.end(); ++it) {
    std::cout << "Nodo: " << it->first.first << " " << it->first.second << " Padre: " << it->second.first << " " << it->second.second << std::endl;
  }
}
