#ifndef ASG_HPP
#define ASG_HPP
#include <iostream>
#include "util.hpp"
#include "pessoa.hpp"
#include "funcionario.hpp"

using namespace std;

class Asg:public Pessoa, public Funcionario {
    private:
    float adicionalInsalubridade;

    public:
    Asg();
    Asg(string nome, string cpf, Data nasc, Endereco end, string estadocivil, int filhos, string salario, string matr, Data ingresso, int faltas, float adicional);
    float getAdicionalInsalubridade();
    void setAdicionalInsalubridade(float adicional);
    float calcularSalario();
    float calcularRecisao(Data desligamento);
};

#endif