#include "show.h"
#include <iostream>
#include <string>

Show::Show(int quota_idoso, int aberturaPortoes, string &artistas,int id, string nome, int id_responsavel, int &capacidade, int &precos):
    EventoAdulto(id, nome, id_responsavel, capacidade, precos,quota_idoso){
    _artistas = &artistas;
    _aberturaPortoes = aberturaPortoes;
}