#include "nodo.h"
#include <vector>
#include <set>
#include <map>
#include <utility>

// matriz que representa el laberinto con las paredes y emplea el algoritmo A*

class MatrizLab {
  public:
    MatrizLab(int** matriz_con_mapa, int filas, int columnas, int x_inicio, int y_inicio, int x_meta, int y_meta);
    int get_filas() const;
    int get_columnas() const;
    int get_x_inicio() const;
    int get_y_inicio() const;
    int get_x_meta() const;
    int get_y_meta() const;
    std::set<Nodo> get_abiertos() const;
    std::set<Nodo> get_cerrados() const;
    std::map<std::pair<int, int>, std::pair<int, int> > get_padres() const;
    void A_estrella();
    // función explorar vecinos que paso el nodo por referencia
    void explorar_vecinos(Nodo&);
    void imprimir_padres();
  private:
    int filas_;
    int columnas_;
    int x_inicio_;
    int y_inicio_;
    int x_meta_;
    int y_meta_;
    std::set<Nodo> abiertos_;
    std::set<Nodo> cerrados_;
    int** matriz_con_mapa_;
    // mapa que contendra de cada nodo, el nodo padre (coordenadas x, y)
    std::map<std::pair<int, int>, std::pair<int, int> > padres_; // el primer pair es el nodo, el segundo pair es el padre
};
