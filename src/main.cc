#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "matriz_lab.h"


int main (int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "Error en los argumentos" << std::endl;
    return 1;
  }
  std::ifstream input(argv[1]);
  std::ofstream output(argv[2]);
  if (!input.is_open()) {
    std::cout << "Error al abrir el archivo" << std::endl;
    return 1;
  }
  if (!output.is_open()) {
    std::cout << "Error al abrir el archivo" << std::endl;
    return 1;
  }
  int filas, columnas;
  std::string input_str;
  std::string auxiliar;
  std::vector<std::string> input_vector;
  // las dos primeras lineas son las dimensiones de la matriz
  // coger la matriz
  if (input.is_open()) {
    while (std::getline(input, auxiliar)) {
      for (unsigned int i = 0; i < auxiliar.size(); i++) { // coge la primera fila
        if (auxiliar[i] != ' ') {
          input_str += auxiliar[i];
        }
      }
      input_vector.push_back(input_str);
      auxiliar.clear();
      input_str.clear();
    }
    
  }
  
  filas = std::stoi(input_vector[0]);
  columnas = std::stoi(input_vector[1]);
  input_vector.erase(input_vector.begin());
  input_vector.erase(input_vector.begin());
  // se borraron las dos primeras lineas que eran las dimensiones de la matriz

  // crear matriz de enteros de filas x columnas
  //std::vector<std::vector<int> > matriz;
  int x_meta, y_meta;
  int x_inicio, y_inicio;
  char aux;
  int aux_int;
  int** matriz = new int*[filas];
  for (int i = 0; i < filas; ++i) {
    matriz[i] = new int[columnas];
  }
  
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      aux = input_vector[i][j];
      aux_int = aux - '0';
      if (aux_int == 3) { // inicio
        x_inicio = i;
        y_inicio = j;
      }
      if (aux_int == 4) { // final
        x_meta = i;
        y_meta = j;
      }
      matriz[i][j] = aux - '0';
    }
  }
  std::cout << "x_inicio: " << x_inicio << " y_inicio: " << y_inicio << std::endl;
  std::cout << "x_meta: " << x_meta << " y_meta: " << y_meta << std::endl;
  // imprimir matriz
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      std::cout << matriz[i][j] << " ";
    }
    std::cout << std::endl;
  }
  //// vamos a crear el nodo inicial como prueba
  Nodo nodo_inicial(x_inicio, y_inicio, x_meta, y_meta, 0);
  std::cout << "nodo_inicial: " << nodo_inicial.get_x() << " " << nodo_inicial.get_y() << " " << nodo_inicial.get_g() << " " << nodo_inicial.get_h() << " " << nodo_inicial.get_f() << std::endl;

  MatrizLab matriz_lab(matriz, filas, columnas, x_inicio, y_inicio, x_meta, y_meta);
  matriz_lab.A_estrella();
  // std::cout << "Numero de padres: " << matriz_lab.get_padres().size() << std::endl;
  // imprimmir padres
  // matriz_lab.imprimir_padres();
  // recorrer atras
  std::cout << "Recorrido atras" << std::endl;
  matriz_lab.imprimir_camino();
  // imprimir camino en mapa
  std::cout << "Camino en mapa" << std::endl;
  matriz_lab.imprimir_camino_en_mapa();
  matriz_lab.imprimir_lab_con_colores();



}