#include <iostream>
#include <utility>

class Nodo {
  public:
    Nodo(int x, int y, int x_meta, int y_meta, int g);
    Nodo() {};
    // void set_padre(Nodo* padre);

    // Nodo* get_padre() const { return padre_; }
    int get_x() const { return x_; }
    int get_y() const { return y_; }
    int get_g() const { return g_; }
    int get_f() const { return f_; }
    int get_h() const { return h_; }
    void set_g(int g) { g_ = g; }
    void recalcule_f(int g) { f_ = g + h_; } // recalcular f con
    bool operator<(const Nodo& nodo) const { // ordenar por f
      if (f_ != nodo.f_) {
        return f_ < nodo.f_;
      }
      if (x_ != nodo.x_) { // si f es igual, ordenar por x
        return x_ < nodo.x_;
      }
      return y_ < nodo.y_; // si x es igual, ordenar por y
    }
    
    void operator=(const Nodo& nodo) {
      x_ = nodo.x_;
      y_ = nodo.y_;
      h_ = nodo.h_;
      g_ = nodo.g_;
      f_ = nodo.f_;
    }
    bool operator==(const Nodo& nodo) const {
      return x_ == nodo.x_ && y_ == nodo.y_;
    }


  
  private:
    int x_;
    int y_;
    int h_;
    int g_;
    int f_;
    // Nodo* padre_;
};