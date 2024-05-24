#pragma once
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include "Cidade.hpp"
#include "Sub_rota.hpp"
#define INFINITO 0xffffffff

class TSP
{
private:
    int buscas = 50;
    std::vector<Cidade> cidades;
    std::vector<std::vector<Sub_rota>> rotas_Armazenadas;
    std::vector< std::vector <std::unordered_map<std::string, double>>> distancias_Armazenadas;
    int primeiraCidade = 0;

public:
    int nCidades;

    TSP(std::string fileName);
    double calculaCaminho();
    double calculaSub_Rota(int k, std::set<int> caminho);

private:
    double calculaDistancia(int c1, int c2);
    double buscaSub_rota(int k, int tam, std::string c_buscado);
    void guardaSub_rota(int k, int tam, std::string c_novo, double dist);
    std::set<int> remove_elm_caminho(std::set<int> caminho, int i);
    std::string caminho_toString(std::set<int> caminho);

    // unsigned numSubConj();
};
