#include <chrono>
#include "heaps.h"
#include <fstream>

using namespace std;

int main(int argv, char* argc[]) {
  srand(time(NULL)); 

  long n;
  string dir_csv;
  string proceso_selecionado;
  int id_proceso_selecionado;
  string nombre_archivo_salida;

  cout<<"INICIO"<<endl;

  //TIPOS DE PRUEBAS
  switch(atoi(argc[1]))
  {

    case 1: proceso_selecionado = "binomial_heap-insercion"; break;
    case 2: proceso_selecionado = "binomial_heap-union"; break;
    case 3: proceso_selecionado = "binomial_heap-eliminacion"; break;

    case 4: proceso_selecionado = "binary_heap-insercion"; break;
    case 5: proceso_selecionado = "binary_heap-union"; break;
    case 6: proceso_selecionado = "binary_heap-eliminacion"; break;

    default: proceso_selecionado = ""; break;
  }

  //DEFINE DIRECTORIO DE CSV
  dir_csv = "csv/";

  //SI VIENE CON PARÁMETRO "head" entonces solamente crea la cabecera del archivo CSV
  if((strcmp(argc[2],"--head") == 0))
  {
    nombre_archivo_salida = dir_csv + proceso_selecionado + "_results.csv";
    ofstream outfile(nombre_archivo_salida);
    outfile << "n,tiempo[ms]\n";

    return 0;
  }
  else
  {
    //LEE EL TAMAÑO DEL VECTOR
    cin>>n;

    //BUSQUEDA SELECCIONADA COMO PARAMETRO
    id_proceso_selecionado = atoi(argc[1]);

    //DEFINE MATRICES DE ENTRADA
    vector<int> A(n);   //VECTOR A

    //LEE VECTOR
    for(auto &row : A)
      {
          cin>>row;
      }

    nombre_archivo_salida = dir_csv + proceso_selecionado + "_results.csv";
    ofstream outfile(nombre_archivo_salida,std::ios::app);

    double mm_total_time = 0;
    int numero_de_experimentos=30;
    for(int j = 0; j < numero_de_experimentos; j++){ 
      
      long long single_execution_time = execution_time_ms(A, id_proceso_selecionado);
      
      mm_total_time += single_execution_time;
    }
    double mm_avg_time = mm_total_time / numero_de_experimentos;

    outfile << n << "," << mm_avg_time <<endl;
    outfile.close(); 
    
    return 0;
  }



}
