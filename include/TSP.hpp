#pragma once
#include <vector>
#include <string>
#include <set>
#include <utility>
#include <unordered_map>
#include "Cidade.hpp"

#define INFINITO 0xffffffff

using namespace std;
class TSP
{
private:
    vector<Cidade> cidades;
    //Matriz que armazena os caminhos já calculados
    vector<vector<unordered_map<string, pair<string, double>>>> rotas_Armazenadas;
    int primeiraCidade = 0;

public:
    int nCidades;
    
    TSP(string fileName);
    pair<string, double> calculaCaminho();
    pair<string, double> calculaSub_Rota(int k, set<int> caminho);

private:
    double calculaDistancia(int c1, int c2);
    pair<string, double> buscaSub_rota(int k, int tam, string c_buscado);
    void guardaSub_rota(int k, int tam, string c_novo, pair<string, double> rota);
    set<int> remove_elm_caminho(set<int> caminho, int i);
    string caminho_toString(set<int> caminho);

};
