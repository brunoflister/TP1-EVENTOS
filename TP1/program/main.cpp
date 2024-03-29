/*
UNIVERSIDADE FEDERAL DE MINAS GERAIS - 2019/2
Programação e Desenvolvimento de Software II

Trabalho Prático - Parte 1
Sistema de gerenciamento de vendas de eventos e controle de usuários

Grupo:
- Bruno Flister Viana (2018048567)
- Ruhann Carlos Pereira de Almeida (2018105501)
- Vítor Gabriel Peixoto Pessoa (2018048451)

*/

#include <bits/stdc++.h> 
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "funcoes.h"


int le_usuarios(int &j, int &qcria, int &qadult, int &qidos, std::string file_usuarios, int *depend, int *idad, vector<Crianca> &crianca, vector<Adulto> &adulto, vector<Idoso> &idoso){
    // Definindo auxiliares
    int id = 0;
    float saldo = 0.0;
    string nome, categoria;

    // Abrindo arquivo
    std::ifstream file_a(file_usuarios);

    if(file_a.is_open()){
        // Separar em uma função
        std::string linha, linha_aux;
        std::vector<string> tratamento;
        
        while(getline(file_a, linha)){
            stringstream X(linha);
            while(getline(X, linha_aux, ',')){
                tratamento.push_back(linha_aux);
            }

            int i = 0;
            id = stoi(tratamento[i]); i++;
            categoria = (tratamento[i]); i++;
            nome = (tratamento[i]); i++;
            idad[j] = stoi(tratamento[i]); i++;
            saldo = stof(tratamento[i]); i++;

            if(categoria == "crianca"){
                depend[qcria] = stoi(tratamento[i]); i++;

                Crianca c(id, categoria, nome, idad[j], saldo, depend[qcria]);
                crianca.push_back(c);
                qcria++;;

            } else if(categoria == "adulto"){
                
                Adulto a(id, categoria, nome, idad[j], saldo);
                adulto.push_back(a);
                qadult++;

            } else if(categoria == "idoso"){
                Idoso ido(id, categoria, nome, idad[j], saldo);
                idoso.push_back(ido);
                qidos++;

            } else {
                cout << "Houve um erro na leitura do arquivo, garanta que as classes de usuários foram identificadas corretamente!" << endl;
                return EXIT_FAILURE;
            }


            j++;

            tratamento.clear();
        }

        
    } else {
        cout << "Erro, nao deu pra abrir!" << endl;
        return EXIT_FAILURE;
    }

}

int le_eventos(int &contagem_donos, int &qBoate, int &qShow, int &qCine, int &qFanto, int *IdDono, int &maiorQuota, int &idMaiorQuota, std::string file_eventos, vector<Cinema> &cinema, vector<Show> &show, vector<Boate> &boate, vector<TeatroFantoche> &fantoche, map<double, int> &precos){
    // Definindo auxiliares
    int NumTipos = 0;
    int IdEven = 0;
    std::string categoriaEven;
    std::string subcategEven;
    std::string nomeEven;
    int quotaIdoso = 0;
    int duracao = 0;
    int horaIni = 0;
    int horaFim = 0;
    int abertura = 0;

    // Abrindo arquivo
    std::ifstream file_b(file_eventos);

    if(file_b.is_open()){
        // Separar em uma função
        std::string linha, linha_aux;
        std::vector<string> tratamento2;
        
        
        while(getline(file_b, linha)){
            stringstream Y(linha);
            while(getline(Y, linha_aux, ',')){
                tratamento2.push_back(linha_aux);
            }
            
            int i = 0;
            IdEven = stoi(tratamento2[i]); i++;

            categoriaEven = tratamento2[i]; i++;

            // Se evento for do tipo cinema, ele não tem subcategoria
            if(categoriaEven != "cinema"){
                subcategEven = tratamento2[i]; i++;
            }

            nomeEven = tratamento2[i]; i++;

            IdDono[contagem_donos] = stoi(tratamento2[i]); i++;

            NumTipos = stoi(tratamento2[i]); i++;

            int *ingEven = new int[NumTipos];
            int *ValorEven = new int[NumTipos];

            for(int aux_tipos = 0; aux_tipos < NumTipos; aux_tipos++){

                ingEven[aux_tipos] = stoi(tratamento2[i]); i++;

                ValorEven[aux_tipos] = stof(tratamento2[i]); i++;

                precos[ValorEven[aux_tipos]] += ingEven[aux_tipos];
            }

            int *horarios = new int[999];
            // Se o evento não for do tipo Adulto, a leitura dos horários é realizada
            int aux_size = tratamento2.size() - i;
            if(categoriaEven == "infantil"){
                for(int aux_h = 0; aux_h < aux_size; aux_h++){
                    horarios[aux_h] = stoi(tratamento2[i]); i++;
                }
                
                TeatroFantoche fan(horarios, IdEven, nomeEven, IdDono[contagem_donos], ingEven, ValorEven);
                fantoche.push_back(fan);
                qFanto++;

            } else if(categoriaEven == "cinema"){
                for(int aux_h = 0; aux_h < aux_size - 1; aux_h++){
                    horarios[aux_h] = stoi(tratamento2[i]); i++;
                }
                
                duracao = stoi(tratamento2[i]); i++;

                Cinema cine(IdEven, nomeEven, IdDono[contagem_donos], ingEven, ValorEven, horarios, duracao);
                cinema.push_back(cine);
                qCine++;

            } else if(categoriaEven == "adulto"){
                quotaIdoso = stoi(tratamento2[i]); i++;

                if(quotaIdoso > maiorQuota){
                    maiorQuota = quotaIdoso;
                    idMaiorQuota = IdEven;
                }

                if(subcategEven == "boate"){
                    horaIni = stoi(tratamento2[i]); i++;
                    horaFim = stoi(tratamento2[i]); i++;

                    Boate boa(quotaIdoso, horaIni, horaFim, IdEven, nomeEven, IdDono[contagem_donos], ingEven, ValorEven);
                    boate.push_back(boa);
                    qBoate++;

                } else if(subcategEven == "show"){
                    abertura = stoi(tratamento2[i]); i++;
                    
                    string *artistas = new string[999];
                    int aux_arts = 0;
                    for(; i <= tratamento2.size(); i++){
                        artistas[aux_arts] = tratamento2[i];
                        aux_arts++;
                    }

                    Show sho(quotaIdoso, abertura, artistas, IdEven, nomeEven, IdDono[contagem_donos], ingEven, ValorEven);
                    show.push_back(sho);
                    qShow++;

                    delete [] artistas;
                }


            } else {
                cout << "Houve um erro na leitura do arquivo, garanta que as classes de usuários foram identificadas corretamente!" << endl;
                return EXIT_FAILURE;

            }

            delete [] horarios;
            delete [] ingEven;
            delete [] ValorEven;

            contagem_donos++;

            tratamento2.clear();
        }

    } else {
        cout << "Erro, nao deu pra abrir!" << endl;
        return EXIT_FAILURE;
    }

}


int main(){

/* ---------- Criação de Objetos - USUÁRIOS ---------- */
    vector<Crianca> crianca; //iniciar o vetor de crianças
    vector<Crianca>::iterator itc;

    vector<Adulto> adulto; //iniciar o vetor de adultos
    vector<Adulto>::iterator ita;

    vector<Idoso> idoso; //iniciar o vetor de idosos
    vector<Idoso>::iterator itd;

/* ---------- Váriaveis Auxiliares - USUÁRIOS ---------- */
    int *depend = new int[999];                //vetor de id dependentes
    depend[0] = -1;                       // usado para caso extremo de nenhum dependente
    int *idad = new int[999];

    // Contadores
    int qcria = 0, qadult = 0, qidos = 0;

/* ---------- Tratando Entrada - USUÁRIOS ---------- */
    std::cout << "Para ler o arquivo, digite o nome de cada arquivo correspondente a seguir, no formato 'arquivo.csv'." << endl;
    std::cout << "O arquivo desejado preferencialmente deve se encontrar na mesma pasta do programa e *deve* usar ; como separador" << endl;
    string file_usuarios;
    std::cout << "Digite o nome do arquivo de USUARIOS que deseja abrir: ";
    std::cin >> file_usuarios;
    
    int contagem_users = 0;
    le_usuarios(contagem_users, qcria, qadult, qidos, file_usuarios, depend, idad, crianca, adulto, idoso);
 
/* ---------- Criação de Objetos - EVENTOS ---------- */
    vector<Cinema> cinema;
    vector<Cinema>::iterator itcine;

    vector<Show> show;
    vector<Show>::iterator itshow;

    vector<Boate> boate;
    vector<Boate>::iterator itboate;

    vector<TeatroFantoche> fantoche;
    vector<TeatroFantoche> itfan;

    map<double, int> precos;
    map<double, int>::iterator itprecos;

/* ---------- Váriaveis Auxiliares - EVENTOS ---------- */
    int *IdDono = new int[999];
    int maiorQuota = 0, idMaiorQuota = 0;
    // Contadores
    int qBoate = 0, qShow = 0, qCine = 0, qFanto = 0;

/* ---------- Tratando Entrada - EVENTOS ---------- */
    string file_eventos;
    std::cout << "Digite o nome do arquivo de EVENTOS que voce quer abrir: ";
    std::cin >> file_eventos;

    int contagem_donos = 0;
    le_eventos(contagem_donos, qBoate, qShow, qCine, qFanto, IdDono, maiorQuota, idMaiorQuota, file_eventos, cinema, show, boate, fantoche, precos);

/* ---------- Saída do Programa ---------- */

// 0 - USUÁRIOS
//   0.1 - Número de crianças, adultos e idosos
    std::cout << endl << "Número de usuários:" << endl;
    std::cout << "Crianças: " << qcria << endl;
    std::cout << "Adultos: " << qadult + qidos << endl;
    std::cout << "Idosos: " << qidos << endl << endl;

//   0.2 - Idade mínima, máxima e média para todos os usuários
    IdadeDosUsuarios(idad, contagem_users);

//   0.3 - Número mínimo, médio e máximo de dependentes por adulto
    NumeroDependentes(depend, qcria, qadult + qidos);

//   0.4 - Lista de dependentes por adulto
    std::cout << "Dependentes:" << endl;
    for(itc = crianca.begin(); itc != crianca.end();itc++){
        for(ita = adulto.begin(); ita != adulto.end(); ita++){
            if(itc->get_id_responsavel() == ita->get_id()){
                std::cout << ita->get_nome() << " (ID: " << ita->get_id() << "): " << itc->get_nome() << " (ID: " << itc->get_id_responsavel() << "), " << endl;
        }
    }}

    for(itc = crianca.begin(); itc != crianca.end();itc++){
        for(itd = idoso.begin(); itd != idoso.end(); itd++){
            if(itc->get_id_responsavel() == itd->get_id()){
                std::cout << itd->get_nome() << " (ID: " << itd->get_id() << "): " << itc->get_nome() << " (ID: " << itc->get_id_responsavel() << "), " << endl;
        }
    }}

// 1 - EVENTOS
//   1.1 - Número de eventos de cada tipo
    std::cout << endl << "Número de eventos:" << endl;
    std::cout << "Adultos:" << endl;
    std::cout << "\tBoate: " << qBoate << endl;
    std::cout << "\tShow: " << qShow << endl;
    std::cout << "Livres:" << endl;
    std::cout << "\tCinema: " << qCine << endl;
    std::cout << "Infantis:" << endl;
    std::cout << "\tTeatro de Fantoches: " << qFanto << endl << endl;

//   1.2 - Número de eventos vendidos por cada usuário
    std::cout << "Número de eventos que o usuário possui:" << endl;
    //Criação de map para armazenar numero eventos por dono
    map<int, int> dono;
    map<int, int>::iterator itdono;

    //Passagem para o Map
    for(int d = 0; d < contagem_donos; d++){
        dono[IdDono[d]]++;
    }
    for(itdono = dono.begin(); itdono != dono.end(); itdono++){
        for(ita = adulto.begin(); ita != adulto.end(); ita++){
            if(itdono->first == ita->get_id()){
                std::cout << ita->get_nome() << " (ID: " << ita->get_id() << "): " << itdono->second << endl;
            }
        }
     }
     for(itdono = dono.begin(); itdono != dono.end(); itdono++){
        for(itd = idoso.begin(); itd != idoso.end(); itd++){
            if(itdono->first == itd->get_id()){
                std::cout << itd->get_nome() << " (ID: " << itd->get_id() << "): " << itdono->second << endl;
            }
        }
     }

//   1.3 - Nome e ID do evento com a maior cota para idosos
    std::cout << endl << "Evento com maior cota para idoso:" << endl;
    for(itshow = show.begin(); itshow != show.end(); itshow++){
        if(itshow->get_id() == idMaiorQuota){
                std::cout << itshow->get_nome() << " (ID: " << itshow->get_id() << "): " << maiorQuota << endl;
        }
    }
    for(itboate = boate.begin(); itboate != boate.end(); itboate++){
        if(itboate->get_id() == idMaiorQuota){
                std::cout << itboate->get_nome() << " (ID: " << itboate->get_id() << "): " << maiorQuota << endl;
        }
    }

//   1.4 - Número total de bilhetes de cada valor
    std::cout << endl << "Número de ingressos por preço:" << endl;
    for(itprecos = precos.begin(); itprecos != precos.end(); itprecos++){
        std::cout << "R$" << itprecos->first << ": " << itprecos->second << endl;
    }


    delete [] depend;
    delete [] idad;
    delete [] IdDono;

    return 0;
}