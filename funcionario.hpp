#ifndef FUNCIONARIO_HPP
#define FUNCIONARIO_HPP
#include <iostream>
#include "util.hpp"
using namespace std;

class Funcionario {
    private:
    string salario;
    string matricula;
    Data ingressoEmpresa;
    int faltas;

    public:
    string getSalario();
    void setSalario(string salario);
    string getMatricula();
    void setMatricula(string matricula);
    Data getIngressoEmpresa();
    void setIngressoEmpresa(Data ingressoEmpresa);
    int getFaltas();
    void setFaltas(int diasfaltas);
    virtual float calcularSalario()=0;
    virtual float calcularRecisao(Data desligamento)=0;
};

#endif