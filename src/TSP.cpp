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

    rotas_Armazenadas.resize(nCidades);
    for (int i = 0; i < nCidades; i++){
        rotas_Armazenadas[i].resize(nCidades);
    }
}

pair<string, double> TSP::calculaCaminho()
{
    pair<string, double> res;
    std::set<int> cidades;

    for (int i = 1; i < nCidades; i++){
        cidades.insert(i);
    }
    res = calculaSub_Rota(primeiraCidade, cidades);

    res.first.pop_back();
    return res;
}

pair<string, double> TSP::calculaSub_Rota(int k, std::set<int> caminho)
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
        return { to_string(primeiraCidade) + "-" + to_string(k) + "-" , calculaDistancia(k, primeiraCidade) };
    }

    std::string chave_caminho = caminho_toString(caminho);

    std::pair<string, double> resposta = buscaSub_rota(k, caminho.size(), chave_caminho);
    
    if(resposta.second == INFINITO){
        std::cout << "Foi buscar!\n";
        double temp;
        std::pair<string, double> aux;
        for(int i : caminho){
            aux = calculaSub_Rota(i, remove_elm_caminho(caminho, i));
            temp = aux.second + calculaDistancia(k,i);
            
            if(resposta.second > temp){
                aux.first += to_string(k) + "-";
                aux.second = temp;

                resposta = aux;
            }
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

pair<string, double> TSP::buscaSub_rota(int k, int tam, std::string c_buscado)
{   
    
    std::cout<<"Busca [" << k << "][" << tam <<"]: " << "\n";
    std::pair<string, double> res;
    res = rotas_Armazenadas[k][tam][c_buscado];

    if(res.second == 0){
        res.second = INFINITO;
    }
    std::cout<<"\n";
    return res;
}

void TSP::guardaSub_rota(int k, int tam,std::string c_novo, std::pair<string, double> rota)
{   
    rotas_Armazenadas[k][tam][c_novo] = rota;

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
