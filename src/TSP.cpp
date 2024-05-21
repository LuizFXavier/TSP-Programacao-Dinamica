#include <fstream>
#include <iostream>
#include <math.h>
#include "TSP.hpp"

TSP::TSP(std::string fileName)
{
    std::ifstream file(fileName);

    file >> nCidades;

    for(int i = 0; i < nCidades; i++){
        int x, y;
        file >> x;
        file >> y;

        cidades.push_back(Cidade{x,y});
    }

    file.close();

    rotas_Armazenadas.resize(nCidades);
    for (int i = 0; i < nCidades; i++){
        rotas_Armazenadas[i].resize(nCidades);
    }
}

double TSP::calculaSub_Rota(int k, std::set<int> caminho)
{
    if(caminho.size() == 0){
        return calculaDistancia(k, primeiraCidade);
    }

    double resposta = buscaSub_rota(k, caminho);
    
    if(resposta == INFINITO){
        
    }
}

double TSP::calculaDistancia(int c1, int c2)
{   
    return std::sqrt(pow(cidades[c1].x - cidades[c2].x, 2) + pow(cidades[c1].y - cidades[c2].y, 2));
}
