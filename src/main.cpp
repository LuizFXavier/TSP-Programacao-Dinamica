#include <iostream>
#include <set>
#include "TSP.hpp"

using namespace std;

int main(int argc, char * argv[]){
    
    if(argc < 1){
        return EXIT_FAILURE;
    }

    TSP tsp{argv[1]};
    
    std::pair<string, double> a = tsp.calculaCaminho();

    cout <<a.first<< " " << a.second<< "\n";

    return 0;
}