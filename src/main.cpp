#include <iostream>
#include <set>
#include "TSP.hpp"

using namespace std;

int main(int argc, char * argv[]){
    
    if(argc < 1){
        return EXIT_FAILURE;
    }

    TSP tsp{argv[1]};
    std::set<int> sas;

    for (int i = 1; i < 9; i++){
        sas.insert(i);
    }

    cout <<tsp.calculaSub_Rota(0,sas)<< "\n";

    return 0;
}