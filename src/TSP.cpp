#include <fstream>
#include <iostream>
#include <cmath>
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

    distancias_Armazenadas.resize(nCidades);
    for (int i = 0; i < nCidades; i++){
        distancias_Armazenadas[i].resize(nCidades);
    }
}

double TSP::calculaSub_Rota(int k, std::set<int> caminho)
{   
    
    for (int i = 0; i < caminho.size() * 10; i++)
        std::cout<<" ";
    std::cout << k << ", {";
    for (int j : caminho){
        std::cout << j << " ";
    }
    std::cout << "} \n";

    if(caminho.size() == 0){
        std::cout<<"Base! ";
        std::cout << calculaDistancia(k, primeiraCidade) << "\n";
        return calculaDistancia(k, primeiraCidade);
    }

    std::string chave_caminho = caminho_toString(caminho);

    double resposta = buscaSub_rota(k, caminho.size(), chave_caminho);
    
    if(resposta == INFINITO){
        std::cout << "Foi buscar!\n";
        double temp;
        for(int i : caminho){
            
            temp = calculaSub_Rota(i, remove_elm_caminho(caminho, i)) + calculaDistancia(k,i);
            
            resposta = temp < resposta ? temp:resposta;
        }
        guardaSub_rota(k, caminho.size(), chave_caminho, resposta);
    }
    else{
        std::cout << "Achou!\n";
    }
    
    return resposta;
}

double TSP::calculaDistancia(int c1, int c2)
{   
    return std::sqrt(pow(cidades[c1].x - cidades[c2].x, 2) + pow(cidades[c1].y - cidades[c2].y, 2));
}

double TSP::buscaSub_rota(int k, int tam, std::string c_buscado)
{   
    
    std::cout<<"Busca [" << k << "][" << tam <<"]: " << "\n";
    double res = distancias_Armazenadas[k][tam][c_buscado];

    if(res == 0){
        res = INFINITO;
    }
    std::cout<<"\n";
    return res;
}

void TSP::guardaSub_rota(int k, int tam,std::string c_novo, double dist)
{   
    distancias_Armazenadas[k][tam][c_novo] = dist;

}

std::set<int> TSP::remove_elm_caminho(std::set<int> caminho, int i)
{
    caminho.erase(i);
    return caminho;
}

std::string TSP::caminho_toString(std::set<int> caminho)
{
    std::string retorno = "";

    for (int i : caminho){
        retorno += std::to_string(i) + "-";
    }
    
    if(retorno.size() > 1)
        retorno.pop_back();

    std::cout<<"Chave:" + retorno + "\n";

    return retorno;
}
