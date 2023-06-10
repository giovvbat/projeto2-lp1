#include <iostream>
#include "gerente.hpp"
#include "util.hpp"
#include "funcionario.hpp"
#include "pessoa.hpp"
using namespace std;

Gerente::Gerente() {}
Gerente::Gerente(float lucro) { this->participacaoLucros=lucro; }
float Gerente::getParticipacaoLucros() { return this->participacaoLucros; }
void Gerente::setParticipacaoLucros(float lucro) { this->participacaoLucros=lucro; }
float Gerente::calcularSalario() {
    int diasfaltas=getFaltas();
    float salario=stof(getSalario());
    salario-=(salario/30)*diasfaltas;
    salario+=participacaoLucros;
    salario+=getQtdFilhos()*100;
    return salario;
}
float Gerente::calcularRecisao(Data desligamento) {
    float desligamentodias, ingressodias;
    ingressodias=getIngressoEmpresa().ano*365+(getIngressoEmpresa().mes)*30+getIngressoEmpresa().dia;
    desligamentodias=desligamento.ano*365+desligamento.mes*30+desligamento.dia;
    float diferencaano=(desligamentodias-ingressodias)/365;
    float adicional=stof(getSalario())*diferencaano;
    return adicional;
}