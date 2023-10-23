#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;


// Estructura para almacenar sufijos y sus índices originales
struct Suffix {
    string suffix;
    int index;
};

// Función de comparación para ordenar sufijos
bool compareSuffixes(const Suffix& a, const Suffix& b) {
    return a.suffix < b.suffix;
}

// Construir un arreglo de sufijos
vector<int> buildSuffixArray(const string& text) {
    int n = text.length();
    vector<Suffix> suffixes(n);

    // Crear un vector de sufijos
    for (int i = 0; i < n; i++) {
        suffixes[i].suffix = text.substr(i);
        suffixes[i].index = i;
    }

    // Ordenar los sufijos lexicográficamente
    sort(suffixes.begin(), suffixes.end(), compareSuffixes);

    // Almacena los índices de los sufijos ordenados
    vector<int> suffixArray(n);
    for (int i = 0; i < n; i++) {
        suffixArray[i] = suffixes[i].index;
    }

    return suffixArray;
}

// Búsqueda binaria en el arreglo de sufijos
int binarySearch(const string& pattern, const string& text, const vector<int>& suffixArray) {
    int left = 0;
    int right = text.length() - 1;
    int count = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        string suffix = text.substr(suffixArray[mid], pattern.length());

        if (pattern == suffix) {
            count++;
            int nextMid = mid + 1;

            // Buscar otras ocurrencias hacia la derecha
            while (nextMid < text.length()) {
                string nextSuffix = text.substr(suffixArray[nextMid], pattern.length());
                if (pattern == nextSuffix) {
                    count++;
                    nextMid++;
                } else {
                    break;
                }
            }

            int prevMid = mid - 1;

            // Buscar otras ocurrencias hacia la izquierda
            while (prevMid >= 0) {
                string prevSuffix = text.substr(suffixArray[prevMid], pattern.length());
                if (pattern == prevSuffix) {
                    count++;
                    prevMid--;
                } else {
                    break;
                }
            }

            return count;
        } else if (pattern < suffix) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return count;
}

int cuenta_SuffixArray(const string& text, const string& pattern) {
    vector<int> suffixArray = buildSuffixArray(text);
    int count = binarySearch(pattern, text, suffixArray);
    return count;
}

void mide_SuffixArray() {
    string fileName = "datasets/input1/input1.txt";
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
    }
    string pattern = "for";
    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    int occurrences = cuenta_SuffixArray(text, pattern);

    file.close();

    cout << "El patrón '" << pattern << "' aparece " << occurrences << " veces en el archivo." << endl;

}


//////////////////////////


vector<int> precomputeShifts(const string& pattern) 
{
    vector<int> shifts(256, pattern.length());
    int m = pattern.length();
    for (int i = 0; i < m - 1; ++i) {
        shifts[static_cast<unsigned char>(pattern[i])] = m - 1 - i;
    }
    return shifts;
}

int cuenta_Horspool(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();

    vector<int> shifts = precomputeShifts(pattern);
    int i = 0;
    int count = 0;

    while (i <= n - m) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[i + j]) {
            j--;
        }

        if (j < 0) {
            count++;
            i += shifts[static_cast<unsigned char>(text[i + m - 1])];
        } else {
            i += shifts[static_cast<unsigned char>(text[i + m - 1])];
        }
    }

    return count;
}

void mide_Horspool()
{
  string fileName = "datasets/input1/input1.txt";
  ifstream file(fileName);
  if (!file.is_open()) {
      cerr << "No se pudo abrir el archivo." << endl;
  }
  string pattern = "for";
  string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

  int occurrences = cuenta_Horspool(text, pattern);

  file.close();

  cout << "El patrón '" << pattern << "' aparece " << occurrences << " veces en el archivo." << endl;

}


//PARA TOMAR EL TIEMPO
long long execution_time_ms(int id_proceso_seleccionado) {

  auto start_time = std::chrono::high_resolution_clock::now();
  switch (id_proceso_seleccionado)
  {
  case 1: //Boyer-Moore-Horspool
    mide_Horspool();
    break;

  case 2: //Sufijos
    mide_SuffixArray();
    break;

  case 3: //FM-Index
    break;

  default:
    break;
  }

  auto end_time = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
}

