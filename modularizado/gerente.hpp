#ifndef GERENTE_HPP
#define GERENTE_HPP
#include <iostream>
#include "funcionario.hpp"
#include "pessoa.hpp"
#include "util.hpp"
using namespace std;

class Gerente:public Pessoa, public Funcionario {
    private:
    float participacaoLucros;

    public:
    Gerente();
    Gerente(float lucro);
    float getParticipacaoLucros();
    void setParticipacaoLucros(float lucro);
    float calcularSalario();
    float calcularRecisao(Data desligamento);
};

#endif