#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <vector>
#include <cstdlib>
#include <string.h>
#include <fstream>
using namespace std;

int main(){
    char a = 'a';
    string aux = "dios";
    string solucion;

    solucion.push_back(a);
    solucion.push_back(aux);
    cout << solucion << endl;
    }