#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Boyer-Moore-Horspool
// Función para preprocesar el patrón y calcular la tabla de saltos de Horspool
vector<int> calculateShiftTable(const string& pattern) {
    int m = pattern.length();
    vector<int> shiftTable(256, m); // Inicializar con el tamaño del patrón

    for (int i = 0; i < m - 1; i++) {
        shiftTable[static_cast<int>(pattern[i])] = m - 1 - i;
    }

    return shiftTable;
}

// Función para contar las ocurrencias del patrón en el texto utilizando Horspool
int count(const string& T, const string& p) {
    int n = T.length();
    int m = p.length();
    vector<int> shiftTable = calculateShiftTable(p);
    int count = 0;
    int i = 0;

    while (i <= n - m) {
        int j = m - 1;
        while (j >= 0 && T[i + j] == p[j]) {
            j--;
        }

        if (j < 0) {
            count++;
            i += shiftTable[static_cast<int>(T[i + m - 1])];
        } else {
            i += shiftTable[static_cast<int>(T[i + m - 1])];
        }
    }

    return count;
}



//PARA TOMAR EL TIEMPO
long long execution_time_ms(int id_proceso_seleccionado) {

  string T = "aaaaabcababcababcabcabc";
  string p = "abc";
  int occurrences = 0;

  auto start_time = std::chrono::high_resolution_clock::now();
  switch (id_proceso_seleccionado)
  {
  case 1: //Boyer-Moore-Horspool
    occurrences = count(T, p);
    cout << "El patrón '" << p << "' aparece " << occurrences << " veces en el texto." << endl;
    break;

  case 2: //Sufijos
    break;

  case 3: //FM-Index
    break;

  default:
    break;
  }


/*
    switch (id_proceso_seleccionado)
    {
      case 1: 
        int occurrences = count(T, p);
        cout << "El patrón '" << p << "' aparece " << occurrences << " veces en el texto." << endl;
        break;



      default:
    }
*/
  auto end_time = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
}

