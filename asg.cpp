#include <iostream>
#include "asg.hpp"
#include "funcionario.hpp"
#include "pessoa.hpp"
using namespace std;

Asg::Asg() {}
Asg::Asg(string nome, string cpf, Data nasc, Endereco end, string estadocivil, int filhos, string salario, string matr, Data ingresso, int faltas, float adicional) {
        setNome(nome);
        setCpf(cpf);
        setDataNascimento(nasc);
        setEnderecoPessoal(end);
        setEstadoCivil(estadocivil);
        setQtdFilhos(filhos);
        setSalario(salario);
        setMatricula(matr);
        setIngressoEmpresa(ingresso);
        setFaltas(faltas);
        this->adicionalInsalubridade=adicional; 
}
float Asg::getAdicionalInsalubridade() { return this->adicionalInsalubridade; }
void Asg::setAdicionalInsalubridade(float adicional) { this->adicionalInsalubridade=adicional; }
float Asg::calcularSalario() {
    float salario=stof(getSalario());
    salario-=(salario/30)*getFaltas();
    salario=salario*(1+adicionalInsalubridade);
    salario=salario+getQtdFilhos()*100;
    return salario;
}
float Asg::calcularRecisao(Data desligamento) {
    float desligamentodias, ingressodias;
    ingressodias=getIngressoEmpresa().ano*365+(getIngressoEmpresa().mes)*30+getIngressoEmpresa().dia;
    desligamentodias=desligamento.ano*365+desligamento.mes*30+desligamento.dia;
    float diferencaano=(desligamentodias-ingressodias)/365;
    float adicional=stof(getSalario())*diferencaano;
    return adicional;
}