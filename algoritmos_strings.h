#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

vector<int> precomputeShifts(const string& pattern) 
{
    std::vector<int> shifts(256, pattern.length());
    int m = pattern.length();
    for (int i = 0; i < m - 1; ++i) {
        shifts[static_cast<unsigned char>(pattern[i])] = m - 1 - i;
    }
    return shifts;
}

int searchHorspoolInText(const string& text, const string& pattern) {
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

void cuenta_Horspool()
{
  string fileName = "datasets/input1/input5.txt";
  ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
    }
    string pattern = "for";
    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    int occurrences = searchHorspoolInText(text, pattern);

    file.close();

    cout << "El patrón '" << pattern << "' aparece " << occurrences << " veces en el archivo." << endl;

}


//PARA TOMAR EL TIEMPO
long long execution_time_ms(int id_proceso_seleccionado) {

  auto start_time = std::chrono::high_resolution_clock::now();
  switch (id_proceso_seleccionado)
  {
  case 1: //Boyer-Moore-Horspool
    cuenta_Horspool();
    break;

  case 2: //Sufijos
    break;

  case 3: //FM-Index
    break;

  default:
    break;
  }


  auto end_time = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
}

