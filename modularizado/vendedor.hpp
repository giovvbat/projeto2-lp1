#ifndef VENDEDOR_HPP
#define VENDEDOR_HPP
#include <iostream>
#include "util.hpp"
#include "pessoa.hpp"
#include "funcionario.hpp"

using namespace std;

class Vendedor:public Pessoa, public Funcionario {
    private:
    char tipoVendedor;

    public:
    Vendedor();
    Vendedor(char tipo);
    char getTipoVendedor();
    void setTipoVendedor(char tipo);
    float calcularSalario();
    float calcularRecisao(Data desligamento);
};

#endif