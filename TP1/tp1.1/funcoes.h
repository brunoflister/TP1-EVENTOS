#ifndef FUNCOES_H
#define FUNCOES_H

#include "adulto.h"
#include "crianca.h"
#include "idoso.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iterator>
#include <set>
#include <map>

using namespace std;

void le_arquivo(fstream &file, vector<string> &linha);

void IdadeDosUsuarios(int *idad, int max);

void NumeroDependentes(int *depend, int qp);

void ListagemDependentes(int *depend, vector<Adulto> a, vector<Idoso> ido);

#endif