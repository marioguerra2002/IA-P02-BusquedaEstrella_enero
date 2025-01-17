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
    // en caso de que sea 4, es que se va a solicitar la coordenada de inicio y la de meta
    if (argc == 4) {
      // el cuarto argumento debe de ser la letra 'm'
      if (argv[3][0] != 'm') {
        std::cout << "Error en los argumentos" << std::endl;
        return 1;
      }
      std::cout << "Se solicitará la coordenada de inicio y la de meta" << std::endl;
    } 
  } // en caso de que se ponga el nombre del ejecutable y --help, se mostrará la ayuda
  if (argc == 2) {
    if (std::string(argv[1]) == "--help") {
      std::cout << "Este programa resuelve laberintos con el algoritmo A*." << std::endl;
      std::cout << "El programa recibe un archivo de texto con el laberinto y devuelve un archivo de texto con el laberinto resuelto." << std::endl;
      std::cout << "El archivo de salida contendrá el laberinto resuelto con el camino óptimo." << std::endl;
      std::cout << "En caso de que se quiera introducir la coordenada de inicio y la de meta, se debe de introducir un cuarto argumento que sea la letra 'm'." << std::endl;
      std::cout << "Forma de uso: ./laberinto <archivo_entrada> <archivo_salida> m" << std::endl;
      return 1;
    }
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
  std::cout << "filas: " << filas << " columnas: " << columnas << std::endl;
  // en caso de que hayan 4 argumentos, se solicitará la coordenada de inicio y la de meta
  // despues de que se hayan introducido, en la matriz se sustituye el 3 por la coordenada de inicio y el 4 por la de meta y donde estaba antes la coordenada de inicio y la de meta, se pone un 0
  if (argc == 4) {
    std::cout << "Introduzca la coordenada de inicio x" << std::endl;
    std::cin >> x_inicio;
    std::cout << "Introduzca la coordenada de inicio y" << std::endl;
    std::cin >> y_inicio;
    std::cout << "Introduzca la coordenada de meta x" << std::endl;
    std::cin >> x_meta;
    std::cout << "Introduzca la coordenada de meta y" << std::endl;
    std::cin >> y_meta;
    // sustituir el 3 por la coordenada de inicio y el 4 por la de meta
    for (int i = 0; i < filas; i++) {
      for (int j = 0; j < columnas; j++) {
        aux = input_vector[i][j];
        aux_int = aux - '0';
        if (aux_int == 3) { // inicio
          matriz[i][j] = 0;
        }
        if (aux_int == 4) { // final
          matriz[i][j] = 0;
        }
        if (i == x_inicio && j == y_inicio) {
          matriz[i][j] = 3;
          x_inicio = i;
          y_inicio = j;
        }
        if (i == x_meta && j == y_meta) {
          matriz[i][j] = 4;
          x_meta = i;
          y_meta = j;
        }
        matriz[i][j] = aux - '0';
      }
    }
  } else {
    // no se solicitará la coordenada de inicio y la de meta
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
  // Nodo nodo_inicial(x_inicio, y_inicio, x_meta, y_meta, 0);
  // std::cout << "nodo_inicial: " << nodo_inicial.get_x() << " " << nodo_inicial.get_y() << " " << nodo_inicial.get_g() << " " << nodo_inicial.get_h() << " " << nodo_inicial.get_f() << std::endl;

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

  // volcar el laberinto con el camino en el documento de salida
  std::stringstream ss;
  ss = matriz_lab.volcar_camino_en_documento();
  output << ss.str();



}