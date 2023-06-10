#include <iostream>
#include "vendedor.hpp"
#include "util.hpp"
#include "funcionario.hpp"
#include "pessoa.hpp"
using namespace std;

Vendedor::Vendedor() {}
Vendedor::Vendedor(char tipo) { this->tipoVendedor=tipo; }
char Vendedor::getTipoVendedor() { return this->tipoVendedor; }
void Vendedor::setTipoVendedor(char tipo) { this->tipoVendedor=tipo; }
float Vendedor::calcularSalario() {
    int diasFaltas=getFaltas();
    float salario=stof(getSalario());
    salario-=(salario/30)*diasFaltas;
    if(tipoVendedor=='A')
        salario*=1.25;
    else if(tipoVendedor=='B')
        salario*=1.1;
    else if(tipoVendedor=='C')
        salario*=1.05;
    salario+=getQtdFilhos()*100;
    return salario;
}
float Vendedor::calcularRecisao(Data desligamento) {
    float desligamentodias, ingressodias;
    ingressodias=getIngressoEmpresa().ano*365+(getIngressoEmpresa().mes)*30+getIngressoEmpresa().dia;
    desligamentodias=desligamento.ano*365+desligamento.mes*30+desligamento.dia;
    float diferencaano=(desligamentodias-ingressodias)/365;
    float adicional=stof(getSalario())*diferencaano;
    return adicional;
}
