#include "matriz_lab.h"

#define RESET   "\033[0m"
#define WALL    "\033[40m" // Fondo rojo
#define START   "\033[42m" // Fondo verde
#define END     "\033[44m" // Fondo azul
#define PATH    "\033[43m" // Fondo amarillo
#define EMPTY   "\033[47m" // Fondo blanco


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



std::map<std::pair<int, int>, std::pair<int, int> > MatrizLab::get_padres() const {
  return padres_;
}

void MatrizLab::A_estrella() {
  Nodo nodo_inicial(x_inicio_, y_inicio_, x_meta_, y_meta_, 0);
  abiertos_.push(nodo_inicial);
  g_scores_[std::make_pair(x_inicio_, y_inicio_)] = 0; // Coste acumulado del nodo inicial


  while (!abiertos_.empty()) {
    Nodo nodo_actual = abiertos_.top();
    abiertos_.pop();
    std::pair<int, int> pos_actual = std::make_pair(nodo_actual.get_x(), nodo_actual.get_y()); // Posición actual del nodo

    nodos_inspeccionados++;
    if (pos_actual.first == x_meta_ && pos_actual.second == y_meta_) {
      std::cout << "Nodo meta encontrado" << std::endl;
      std::cout << "Nodos generados: " << nodos_generados << std::endl;
      std::cout << "Nodos inspeccionados: " << nodos_inspeccionados << std::endl;
      // coste total del camino
      std::cout << "Coste total del camino: " << nodo_actual.get_g() << std::endl;
      return;
    }
    cerrados_.insert(pos_actual); // Añado el nodo actual a cerrados
    explorar_vecinos(nodo_actual, abiertos_, cerrados_, padres_, g_scores_);
  }
  
}

void MatrizLab::explorar_vecinos(const Nodo& nodo_actual, std::priority_queue<Nodo, std::vector<Nodo>, NodoComparador>& abiertos_, std::set<std::pair<int, int> >& cerrados_, std::map<std::pair<int, int>, std::pair<int, int> >& padres_, std::map<std::pair<int, int>, int>& g_scores_) {
  int costes[] = {5, 7};
  for (int dx = -1; dx <= 1; ++dx) {
    for (int dy = -1; dy <= 1; ++dy) {
      if (dx == 0 && dy == 0) continue; // No se puede ir a sí mismo como vecino
      int nx = nodo_actual.get_x() + dx; // Posición x del vecino 
      int ny = nodo_actual.get_y() + dy; // Posición y del vecino

      if (nx >= 0 && nx < filas_ && ny >= 0 && ny < columnas_ && matriz_con_mapa_[nx][ny] != 1) { // Si no se sale de la matriz y no es una pared
        std::pair<int, int> vecino_pos = std::make_pair(nx, ny); // Posición del vecino
        if (cerrados_.count(vecino_pos)) continue; // Si el vecino está en cerrados, lo ignoro. Count devuelve 1 si está, 0 si no

        int coste = (dx == 0 || dy == 0) ? costes[0] : costes[1]; // Coste de moverse al vecino (5 si es horizontal o vertical, 7 si es diagonal)
        int tentative_g = g_scores_[std::make_pair(nodo_actual.get_x(), nodo_actual.get_y())] + coste; // Coste acumulado de ir al vecino

        if (!g_scores_.count(vecino_pos) || tentative_g < g_scores_[vecino_pos]) { // Si no está en g_scores o el nuevo camino es mejor
          g_scores_[vecino_pos] = tentative_g; // Actualizo el coste acumulado del vecino 
          Nodo vecino(nx, ny, x_meta_, y_meta_, tentative_g); // Creo el nodo vecino con el coste acumulado
          abiertos_.push(vecino); // Añado el vecino a abiertos con su coste acumulado
          padres_[vecino_pos] = std::make_pair(nodo_actual.get_x(), nodo_actual.get_y()); // Guardo el padre del vecino en el mapa de padres
          nodos_generados++;
        }
      }
    }
  }
}

void MatrizLab::imprimir_padres() {
  for (const auto& par : padres_) {
    std::cout << "Nodo: (" << par.first.first << ", " << par.first.second << ") ";
    std::cout << "Padre: (" << par.second.first << ", " << par.second.second << ")" << std::endl;
  }
}


void MatrizLab::guardar_camino() {
  std::pair<int, int> pos_actual = std::make_pair(x_meta_, y_meta_);
  while (pos_actual.first != x_inicio_ || pos_actual.second != y_inicio_) {
    camino_.push_back(pos_actual);
    pos_actual = padres_[pos_actual];
  }
  camino_.push_back(std::make_pair(x_inicio_, y_inicio_));
}

void MatrizLab::imprimir_camino() {
  guardar_camino();
  // se tiene que imprimir al revés
  // si es el inicio, imprimir la coordenada y un 3 y si es la meta, imprimir la coordenada y un 4
  for (int i = camino_.size() - 1; i >= 0; i--) {
    if (i == 0) {
      std::cout << "\n" <<"("<< camino_[i].first << " " << camino_[i].second << ") "<<"-> final" << std::endl;
    } else if (i == camino_.size() - 1) {
      std::cout << "(" << camino_[i].first << " " << camino_[i].second << ") "<< "-> inicio" << std::endl;
    } else {
      std::cout << "(" << camino_[i].first << " " << camino_[i].second << ") ";
    }
  }
}

// imprimir el camino en el mapa donde el camino son * 
void MatrizLab::imprimir_camino_en_mapa() {
  guardar_camino();
  for (int i = 0; i < filas_; i++) {
    for (int j = 0; j < columnas_; j++) {
      if (std::find(camino_.begin(), camino_.end(), std::make_pair(i, j)) != camino_.end()) {
        if (i == x_inicio_ && j == y_inicio_) {
          std::cout << "3 ";
        } else if (i == x_meta_ && j == y_meta_) {
          std::cout << "4 ";
        } else {
          std::cout << "* ";
        }
      } else {
        std::cout << matriz_con_mapa_[i][j] << " ";
      }
    }
    std::cout << std::endl;
  }
}


void MatrizLab::imprimir_lab_con_colores() {
  guardar_camino();
  for (int i = 0; i < filas_; i++) {
    for (int j = 0; j < columnas_; j++) {
      if (std::find(camino_.begin(), camino_.end(), std::make_pair(i, j)) != camino_.end()) {
        if (i == x_inicio_ && j == y_inicio_) {
          std::cout << START << "3 " << RESET;  // Fondo verde con "3"
        } else if (i == x_meta_ && j == y_meta_) {
          std::cout << END << "4 " << RESET;    // Fondo azul con "4"
        } else {
          std::cout << PATH << "  " << RESET;
        }
      } else {
        if (matriz_con_mapa_[i][j] == 1) {
          std::cout << WALL << "  " << RESET;
        } else {
          std::cout << EMPTY << "  " << RESET;
        }
      }
    }
    std::cout << std::endl;
  }
}
