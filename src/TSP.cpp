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
    for (int i = 0; i < caminho.size() * 10; i++)
        std::cout<<" ";
    std::cout << k << ", {";
    for (int j : caminho){
        std::cout << j << " ";
    }
    std::cout << "} \n";

    if(caminho.size() == 0){
        std::cout << calculaDistancia(k, primeiraCidade) << "\n";
        return calculaDistancia(k, primeiraCidade);
    }

    double resposta = buscaSub_rota(k, caminho);
    
    if(resposta == INFINITO){
        double temp;
        for(int i : caminho){
            std::cout << "i: " <<i << "\n";
            temp = calculaSub_Rota(i, remove_elm_caminho(caminho, i)) + calculaDistancia(k,i);
            
            for (int i = 0; i < caminho.size() * 10; i++)
                std::cout<<" ";
            std::cout << temp << "\n";
            resposta = temp < resposta ? temp:resposta;
        }
        guardaSub_rota(k, caminho, resposta);
    }
    else{
        
    }

    return resposta;
}

double TSP::calculaDistancia(int c1, int c2)
{   
    return std::sqrt(pow(cidades[c1].x - cidades[c2].x, 2) + pow(cidades[c1].y - cidades[c2].y, 2));
}

double TSP::buscaSub_rota(int k, std::set<int> c_buscado)
{   
    
    std::cout<<"Busca: " << "\n";
    // std::cout << "[" << k << "][" << c_buscado.size() << "]: ";
    Sub_rota* aux = &(rotas_Armazenadas[k][c_buscado.size()]);
    double res = INFINITO;

    while (aux && res == INFINITO)
    {   
        std::cout << "{ ";
        for (int i : aux->elementos){
            std::cout << i << " ";
        }
        std::cout << "}, ";

        if(aux->elementos == c_buscado){
            std::cout<<"Achou";
            res = aux->distancia;
        }
        
        aux = aux->prox;
    }
    std::cout<<"\n";
    return res;
}

void TSP::guardaSub_rota(int k, std::set<int> c_novo, double dist)
{
    
    Sub_rota* aux = &rotas_Armazenadas[k][c_novo.size()];
    // std::cout<< "aux no insere:"<<aux->distancia << "\n";

    if (!aux->distancia){
        std::cout << "Inserção (p):\n";
        Sub_rota nova = Sub_rota{c_novo, dist};
        rotas_Armazenadas[k][c_novo.size()] = nova;
        std::cout << "[" << k << "][" << c_novo.size() << "]: "<<nova.distancia << "\n";
        return;
    }

    std::cout << "Inserção (d):\n";

    while (aux->prox)
    {
        aux = aux->prox;
    }
    Sub_rota nova = Sub_rota{c_novo, dist};
    
    Sub_rota** ref_prox = &aux->prox;

    *ref_prox = &nova;
    std::cout << "[" << k << "][" << c_novo.size() << "]: "<<nova.distancia << "\n";
}

std::set<int> TSP::remove_elm_caminho(std::set<int> caminho, int i)
{
    caminho.erase(i);
    return caminho;
}
