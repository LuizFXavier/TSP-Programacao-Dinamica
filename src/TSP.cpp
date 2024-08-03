#include <fstream>
#include <iostream>
#include <cmath>
#include "TSP.hpp"
#define PI 3.141592

TSP::TSP(std::string fileName)
{
    //Leitura inicial das coordenadas

    std::ifstream file(fileName);

    file >> nCidades;

    for(int i = 0; i < nCidades; i++){
        double x, y;
        file >> x;
        file >> y;

        int deg = (int)x;
        double min = x - deg;
        double radX = PI * (deg + 5.0 * min/3.0) / 180.0;

        deg = (int)y;
        min = y - deg;
        double radY = PI * (deg + 5.0 * min/3.0) / 180.0;

        cidades.push_back(Cidade{radX, radY});
    }

    file.close();

    //Preparação da matriz que armazenará os resultados já calculados
    rotas_Armazenadas.resize(nCidades);
    for (int i = 0; i < nCidades; i++){
        rotas_Armazenadas[i].resize(nCidades);
    }
}

/*
* Método que prepara o caminho a ser calculado e chama a função recursiva, que efetivamente calcula as sub_rotas
*/
pair<string, double> TSP::calculaCaminho()
{
    pair<string, double> res;
    std::set<int> cidades;

    for (int i = 1; i < nCidades; i++){
        cidades.insert(i);
    }
    res = calculaSub_Rota(primeiraCidade, cidades);

    //Remoção do último "-" na string do caminho
    res.first.pop_back();
    return res;
}

/**
* Método recursivo que calcula a distância percorrida no sub-caminho
* @param k é a cidade pela qual o caminho está passando no momento
* @param caminho é o subconjunto de cidades que formarão o caminho
**/
pair<string, double> TSP::calculaSub_Rota(int k, std::set<int> caminho)
{   
    // Se o tamanho do subconjunto que representa as cidades a serem atravessadas for 0,
    //a distância entre k e a cidade inicial é retornada
    if(caminho.size() == 0){

        return { to_string(primeiraCidade) + "-" + to_string(k) + "-" , calculaDistancia(k, primeiraCidade) };
    }

    std::string chave_caminho = caminho_toString(caminho);

    //Primeiro haverá a busca na matriz armazenda para verificar se já existe registro na matriz com
    //esse conjunto de cidades e a cidade atual
    std::pair<string, double> resposta = buscaSub_rota(k, caminho.size(), chave_caminho);
   

   //Caso não encontre, a função será chamada recursivamente para calcular o sub caminho inferior
    if(resposta.second == INFINITO){
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
    
    return resposta;
}

/*
*Método que retorna a distância euclidiana entre as cidades
*/
double TSP::calculaDistancia(int c1, int c2)
{   
    double const RRR = 6378.388;

    // double q1 = cos(cidades[c1].x - cidades[c2].x);
    // double q2 = cos(cidades[c1].y - cidades[c2].y);
    // double q3 = cos(cidades[c1].y + cidades[c2].y);

    // return (int)(RRR * acos(0.5 * ((1.0 + q1)*q2 - (1.0 - q1)*q3) ) + 1.0);
    double lt1 = cidades[c1].x;
    double lt2 = cidades[c2].x;
    double lg1 = cidades[c1].y;
    double lg2 = cidades[c2].y;

    return 2 * RRR * asin( sqrt(pow(sin( (lt1-lt2)/2 ), 2) + cos(lt1) * cos(lt2) * pow(sin((lg1-lg2)/2),2)));
}

/*
*Método que busca a distância e o caminho armazenado na matriz de memorização.
*A matriz guarda o menor caminho que passe pelos elementos de em c_buscado e por fim passa por k
* @param k cidade pelo qual o caminho está passando no momento
* @param tam tamanho do sub conjunto de cidades que forma o sub caminho
* @param c_buscado chave do caminho a ser encontrado, contendo as cidades a serem atravessadas
*/
pair<string, double> TSP::buscaSub_rota(int k, int tam, std::string c_buscado)
{   
    std::pair<string, double> res;
    res = rotas_Armazenadas[k][tam][c_buscado];

    if(res.second == 0){
        res.second = INFINITO;
    }
    
    return res;
}
/*
*Método que busca a distância e o caminho armazenado na matriz de memorização
* @param k cidade pelo qual o caminho está passando no momento
* @param tam tamanho do sub conjunto de cidades que forma o sub caminho
* @param c_novo chave do caminho a ser armazenado, contendo as cidades a serem atravessadas
* @param rota par de caminho a ser atravessado (na ordem correta) e sua distância
*/
void TSP::guardaSub_rota(int k, int tam,std::string c_novo, std::pair<string, double> rota)
{   
    rotas_Armazenadas[k][tam][c_novo] = rota;

}
/*
* Retorno do mesmo conjunto, porém sem um de seus elementos
* @param caminho conjunto de números que representam cidades
* @param i elemento que será removido na cópia
*/
std::set<int> TSP::remove_elm_caminho(std::set<int> caminho, int i)
{
    caminho.erase(i);
    return caminho;
}
/*
* Transformação de um conjunto em uma string para poder ser utilizado como chave no std::unordered_map
* @param caminho conjunto a ser convertido
*/
std::string TSP::caminho_toString(std::set<int> caminho)
{
    std::string retorno = "";

    for (int i : caminho){
        retorno += std::to_string(i) + "-";
    }
    
    if(retorno.size() > 1)
        retorno.pop_back();

    return retorno;
}
