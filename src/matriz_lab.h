#include "nodo.h"
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <sstream>

// matriz que representa el laberinto con las paredes y emplea el algoritmo A*
struct NodoComparador {
  bool operator()(const Nodo& a, const Nodo& b) {
    return a.get_f() > b.get_f(); // Cola de prioridad de menor a mayor f
  }
};

class MatrizLab {
  public:
    MatrizLab(int** matriz_con_mapa, int filas, int columnas, int x_inicio, int y_inicio, int x_meta, int y_meta);
    int get_filas() const;
    int get_columnas() const;
    int get_x_inicio() const;
    int get_y_inicio() const;
    int get_x_meta() const;
    int get_y_meta() const;
    std::map<std::pair<int, int>, std::pair<int, int> > get_padres() const;
    void A_estrella();
    // función explorar vecinos que paso el nodo por referencia
    // void explorar_vecinos(Nodo&);
    // void explorar_vecinos(Nodo&, std::priority_queue<Nodo, std::vector<Nodo>, NodoComparador>&, std::set<Nodo>&, std::map<std::pair<int, int>, std::pair<int, int> >&);
    void explorar_vecinos(const Nodo&, std::priority_queue<Nodo, std::vector<Nodo>, NodoComparador>&, std::set<std::pair<int, int> >&, std::map<std::pair<int, int>, std::pair<int, int> >&, std::map<std::pair<int, int>, int>&);
    void imprimir_camino(); // ir hacia atrás
    void imprimir_padres();
    void guardar_camino();
    void imprimir_camino_en_mapa();
    void imprimir_lab_con_colores();
    std::stringstream volcar_camino_en_documento();
  private:
    int filas_;
    int columnas_;
    int x_inicio_;
    int y_inicio_;
    int x_meta_;
    int y_meta_;
    //std::set<Nodo> abiertos_;
    std::priority_queue<Nodo, std::vector<Nodo>, NodoComparador> abiertos_;
    //std::set<Nodo> cerrados_;
    std::set<std::pair<int, int> > cerrados_;
    int** matriz_con_mapa_;
    // mapa que contendra de cada nodo, el nodo padre (coordenadas x, y)
    std::map<std::pair<int, int>, std::pair<int, int> > padres_; // el primer pair es el nodo, el segundo pair es el padre
    std::map<std::pair<int, int>, int> g_scores_;
    // vector donde se guarda las posiciones del camino
    std::vector<std::pair<int, int> > camino_;
    int nodos_generados = 0;
    int nodos_inspeccionados = 0;

};
