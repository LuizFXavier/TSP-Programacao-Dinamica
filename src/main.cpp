#include <iostream>
#include <set>
#include "TSP.hpp"

using namespace std;

int main(int argc, char * argv[]){
    
    //Necessário o arquivo com as coordenadas na linha de comando
    if(argc < 1){
        return EXIT_FAILURE;
    }

    TSP tsp{argv[1]};
    
    std::pair<string, double> a = tsp.calculaCaminho();

    cout <<a.first<< " " << a.second<< "\n";

    return 0;
}