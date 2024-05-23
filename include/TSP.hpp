#pragma once
#include <vector>
#include <string>
#include <set>
#include "Cidade.hpp"
#include "Sub_rota.hpp"
#define INFINITO 0xffffffff

class TSP
{
private:
    std::vector<Cidade> cidades;
    std::vector<std::vector<Sub_rota>> rotas_Armazenadas;
    int nCidades;
    int primeiraCidade = 0;

public:
    TSP(std::string fileName);
    double calculaCaminho();
    double calculaSub_Rota(int k, std::set<int> caminho);

private:
    double calculaDistancia(int c1, int c2);
    double buscaSub_rota(int k, std::set<int> c_buscado);
    void guardaSub_rota(int k, std::set<int> c_novo, double dist);
    std::set<int> remove_elm_caminho(std::set<int> caminho, int i);
    // unsigned numSubConj();
};
