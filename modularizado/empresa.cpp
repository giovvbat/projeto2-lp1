#include <iostream>
#include "util.hpp"
#include "pessoa.hpp"
#include "asg.hpp"
#include "gerente.hpp"
#include "vendedor.hpp"
#include "empresa.hpp"
#include <fstream>
#include <vector>

using namespace std;

Empresa::Empresa() {}
Empresa::Empresa(string nome, string cnpj, float faturamento) {
    this->cnpj=cnpj;
    this->faturamentoMensal=faturamento;
    this->nomeEmpresa=nome;
}
float Empresa::getFaturamentoMensal() { return this->faturamentoMensal; }
void Empresa::setFaturamentoMensal(float faturamento) { this->faturamentoMensal=faturamento; }
string Empresa::getNomeEmpresa() { return this->nomeEmpresa; }
void Empresa::setNomeEmpresa(string nome) { this->nomeEmpresa=nome; }
string Empresa::getCnpj() { return this->cnpj; }
void Empresa::setCnpj(string cnpj) { this->cnpj=cnpj; }
vector<Asg> Empresa::getAsgs() { return this->asgs; }
vector<Vendedor> Empresa::getVendedores() { return this->vendedores; }
vector<Gerente> Empresa::getGerentes() { return this->gerentes; }


void Empresa::carregarFuncoes() {
    ifstream file("funcoes.txt");
    string linha;
    if (!(file.is_open())) {
        cout<<"Arquivo não pôde ser aberto!"<<endl;
        return;
    }

    while(getline(file, linha)) {
        if(linha=="carregarEmpresa()") carregarEmpresa();
        else if(linha=="carregarAsg()") carregarAsg();
        else if(linha=="carregarVendedor()") carregarVendedor();
        else if(linha=="carregarGerente()") carregarGerente();
        else if(linha=="carregaDono()") carregaDono();
        else if(linha=="imprimeAsgs()") imprimeAsgs();
        else if(linha=="imprimeVendedores()") imprimeVendedores();
        else if(linha=="imprimeGerentes()") imprimeGerentes();
        else if(linha=="imprimeDono()") imprimeDono();
        else if(linha=="buscaFuncionario()") {
            string parametro;
            getline(file, parametro);
            buscaFuncionario(parametro);
        }
        else if(linha=="calculaSalarioFuncionario()") {
            string parametro;
            getline(file, parametro);
            calculaSalarioFuncionario(parametro);
        }
        else if(linha=="calculaTodoOsSalarios()") calculaTodosOsSalarios();
        else if(linha=="calcularRecisao()") {
            string matricula;
            string datas;
            Data data;

            getline(file, matricula);

            getline(file, datas);
            data.ano=stoi(datas);
            getline(file, datas);
            data.mes=stoi(datas);
            getline(file, datas);
            data.dia=stoi(datas);

            calcularRecisao(matricula, data);
        }
    }
}

void Empresa::carregaDono() {
    ifstream file("dono.txt");
    string linha;
    if (!(file.is_open())) {
        cout<<"Arquivo não pôde ser aberto!"<<endl;
        return;
    }

    getline(file, linha);
    getline(file, linha);

    getline(file, linha);
    dono.setNome(linha);

    getline(file, linha);
    dono.setCpf(linha);

    getline(file, linha);
    int filhos=stoi(linha);
    dono.setQtdFilhos(filhos);

    getline(file, linha);
    dono.setEstadoCivil(linha);

    Endereco endereco;
    getline(file, linha);
    endereco.cidade=linha;
    getline(file, linha);
    endereco.cep=linha;
    getline(file, linha);
    endereco.bairro=linha;
    getline(file, linha);
    endereco.rua=linha;
    getline(file, linha);
    int num=stoi(linha);
    endereco.numero=num;
    dono.setEnderecoPessoal(endereco);

    Data nascimento;
    getline(file, linha);
    int ano=stoi(linha);
    nascimento.ano=ano;
    getline(file, linha);
    int mes=stoi(linha);
    nascimento.mes=mes;
    getline(file, linha);
    int dia=stoi(linha);
    nascimento.dia=dia;
    dono.setDataNascimento(nascimento);

    file.close();
}

void Empresa::carregarEmpresa() {
    ifstream file("empresa.txt");
    string linha;
    if (!(file.is_open())) {
        cout<<"Arquivo não pôde ser aberto!"<<endl;
        return;
    }

    getline(file, linha);
    getline(file, linha);

    getline(file, linha);
    setNomeEmpresa(linha);
    getline(file, linha);
    setCnpj(linha);
    getline(file, linha);
    setFaturamentoMensal(stof(linha));

    file.close();
}

void Empresa::carregarAsg() {
    ifstream file("asg.txt");
    string linha;
    if (!(file.is_open())) {
        cout<<"Arquivo não pôde ser aberto!"<<endl;
        return;
    }

    Asg asg;
    Endereco endereco;
    Data datan, datai;

    while(getline(file, linha)) {
        getline(file, linha);
        getline(file, linha);

        getline(file, linha);
        asg.setNome(linha);
        getline(file, linha);
        asg.setCpf(linha);
        getline(file, linha);
        asg.setQtdFilhos(stoi(linha));
        getline(file, linha);
        asg.setEstadoCivil(linha);

        getline(file, linha);

        getline(file, linha);
        endereco.cidade=linha;
        getline(file, linha);
        endereco.cep=linha;
        getline(file, linha);
        endereco.bairro=linha;
        getline(file, linha);
        endereco.rua=linha;
        getline(file, linha);
        endereco.numero=stoi(linha);
        asg.setEnderecoPessoal(endereco);

        getline(file, linha);

        getline(file, linha);
        datan.ano=stoi(linha);
        getline(file, linha);
        datan.mes=stoi(linha);
        getline(file, linha);
        datan.dia=stoi(linha);
        asg.setDataNascimento(datan);

        getline(file, linha);

        getline(file, linha);
        asg.setMatricula(linha);
        getline(file, linha);
        asg.setSalario(linha);
        getline(file, linha);
        asg.setAdicionalInsalubridade(stof(linha));
        getline(file, linha);
        asg.setFaltas(stoi(linha));

        getline(file, linha);

        getline(file, linha);
        datai.ano=stoi(linha);
        getline(file, linha);
        datai.mes=stoi(linha);
        getline(file, linha);
        datai.dia=stoi(linha);
        asg.setIngressoEmpresa(datai);

        asgs.push_back(asg);
    }
    
    file.close();
}

void Empresa::carregarVendedor() {
    ifstream file("vendedor.txt");
    string linha;
    if (!(file.is_open())) {
        cout<<"Arquivo não pôde ser aberto!"<<endl;
        return;
    }

    Vendedor vendedor;
    Endereco endereco;
    Data datan, datai;

    while(getline(file, linha)) {
        getline(file, linha);
        getline(file, linha);

        getline(file, linha);
        vendedor.setNome(linha);
        getline(file, linha);
        vendedor.setCpf(linha);
        getline(file, linha);
        vendedor.setQtdFilhos(stoi(linha));
        getline(file, linha);
        vendedor.setEstadoCivil(linha);

        getline(file, linha);

        getline(file, linha);
        endereco.cidade=linha;
        getline(file, linha);
        endereco.cep=linha;
        getline(file, linha);
        endereco.bairro=linha;
        getline(file, linha);
        endereco.rua=linha;
        getline(file, linha);
        endereco.numero=stoi(linha);
        vendedor.setEnderecoPessoal(endereco);

        getline(file, linha);

        getline(file, linha);
        datan.ano=stoi(linha);
        getline(file, linha);
        datan.mes=stoi(linha);
        getline(file, linha);
        datan.dia=stoi(linha);
        vendedor.setDataNascimento(datan);

        getline(file, linha);

        getline(file, linha);
        vendedor.setMatricula(linha);
        getline(file, linha);
        vendedor.setSalario(linha);
        getline(file, linha);
        char tipo=linha[0];
        vendedor.setTipoVendedor(tipo);
        getline(file, linha);
        vendedor.setFaltas(stoi(linha));

        getline(file, linha);

        getline(file, linha);
        datai.ano=stoi(linha);
        getline(file, linha);
        datai.mes=stoi(linha);
        getline(file, linha);
        datai.dia=stoi(linha);
        vendedor.setIngressoEmpresa(datai);

        vendedores.push_back(vendedor);
    }
    
    file.close();
}

void Empresa::carregarGerente() {
    ifstream file("gerente.txt");
    string linha;
    if (!(file.is_open())) {
        cout<<"Arquivo não pôde ser aberto!"<<endl;
        return;
    }

    Gerente gerente;
    Endereco endereco;
    Data datan, datai;

    while(getline(file, linha)) {
        getline(file, linha);
        getline(file, linha);

        getline(file, linha);
        gerente.setNome(linha);
        getline(file, linha);
        gerente.setCpf(linha);
        getline(file, linha);
        gerente.setQtdFilhos(stoi(linha));
        getline(file, linha);
        gerente.setEstadoCivil(linha);

        getline(file, linha);

        getline(file, linha);
        endereco.cidade=linha;
        getline(file, linha);
        endereco.cep=linha;
        getline(file, linha);
        endereco.bairro=linha;
        getline(file, linha);
        endereco.rua=linha;
        getline(file, linha);
        endereco.numero=stoi(linha);
        gerente.setEnderecoPessoal(endereco);

        getline(file, linha);

        getline(file, linha);
        datan.ano=stoi(linha);
        getline(file, linha);
        datan.mes=stoi(linha);
        getline(file, linha);
        datan.dia=stoi(linha);
        gerente.setDataNascimento(datan);

        getline(file, linha);

        getline(file, linha);
        gerente.setMatricula(linha);
        getline(file, linha);
        gerente.setSalario(linha);
        getline(file, linha);
        gerente.setParticipacaoLucros(stof(linha));
        getline(file, linha);
        gerente.setFaltas(stoi(linha));

        getline(file, linha);

        getline(file, linha);
        datai.ano=stoi(linha);
        getline(file, linha);
        datai.mes=stoi(linha);
        getline(file, linha);
        datai.dia=stoi(linha);
        gerente.setIngressoEmpresa(datai);

        gerentes.push_back(gerente);
    }
    
    file.close();
}

void Empresa::imprimeAsgs() {
    cout<<"Lista de profissionais ASG:"<<endl;
    for(auto i:asgs) {
        cout<<"Nome: "<<i.getNome()<<endl;
        cout<<"CPF: "<<i.getCpf()<<endl;
        cout<<"Data de nascimento: "<<i.getDataNascimento().dia<<"/"<<i.getDataNascimento().mes<<"/"<<i.getDataNascimento().ano<<endl;
        cout<<"Endereço: Rua "<<i.getEnderecoPessoal().rua<<", "<<i.getEnderecoPessoal().numero<<endl;
        cout<<"Estado civil: "<<i.getEstadoCivil()<<endl;
        cout<<"Número de filhos: "<<i.getQtdFilhos()<<endl;
        cout<<"Salário: "<<i.calcularSalario()<<endl;
        cout<<"Número de faltas: "<<i.getFaltas()<<endl;
        cout<<"Matrícula: "<<i.getMatricula()<<endl;
        cout<<"Data de ingresso na empresa: "<<i.getIngressoEmpresa().dia<<"/"<<i.getIngressoEmpresa().mes<<"/"<<i.getIngressoEmpresa().ano<<endl;
        cout<<"**********************************"<<endl;
    }
}
 
void Empresa::imprimeVendedores() {
    cout<<"Lista de vendedores:"<<endl;
    for(auto i:vendedores) {
        cout<<"Nome: "<<i.getNome()<<endl;
        cout<<"CPF: "<<i.getCpf()<<endl;
        cout<<"Data de nascimento: "<<i.getDataNascimento().dia<<"/"<<i.getDataNascimento().mes<<"/"<<i.getDataNascimento().ano<<endl;
        cout<<"Endereço: Rua "<<i.getEnderecoPessoal().rua<<", "<<i.getEnderecoPessoal().numero<<endl;
        cout<<"Estado civil: "<<i.getEstadoCivil()<<endl;
        cout<<"Número de filhos: "<<i.getQtdFilhos()<<endl;
        cout<<"Salário: "<<i.calcularSalario()<<endl;
        cout<<"Número de faltas: "<<i.getFaltas()<<endl;
        cout<<"Matrícula: "<<i.getMatricula()<<endl;
        cout<<"Data de ingresso na empresa: "<<i.getIngressoEmpresa().dia<<"/"<<i.getIngressoEmpresa().mes<<"/"<<i.getIngressoEmpresa().ano<<endl;
        cout<<"**********************************"<<endl;
    }
}

void Empresa::imprimeGerentes() {
    cout<<"Lista de gerentes:"<<endl;
    for(auto i:gerentes) {
        cout<<"Nome: "<<i.getNome()<<endl;
        cout<<"CPF: "<<i.getCpf()<<endl;
        cout<<"Data de nascimento: "<<i.getDataNascimento().dia<<"/"<<i.getDataNascimento().mes<<"/"<<i.getDataNascimento().ano<<endl;
        cout<<"Endereço: Rua "<<i.getEnderecoPessoal().rua<<", "<<i.getEnderecoPessoal().numero<<endl;
        cout<<"Estado civil: "<<i.getEstadoCivil()<<endl;
        cout<<"Número de filhos: "<<i.getQtdFilhos()<<endl;
        cout<<"Salário: "<<i.calcularSalario()<<endl;
        cout<<"Número de faltas: "<<i.getFaltas()<<endl;
        cout<<"Matrícula: "<<i.getMatricula()<<endl;
        cout<<"Data de ingresso na empresa: "<<i.getIngressoEmpresa().dia<<"/"<<i.getIngressoEmpresa().mes<<"/"<<i.getIngressoEmpresa().ano<<endl;
        cout<<"**********************************"<<endl;
    }
}

void Empresa::imprimeDono() {
    cout<<"Informações sobre dono:"<<endl;
    cout<<"Nome: "<<dono.getNome()<<endl;
    cout<<"CPF: "<<dono.getCpf()<<endl;
    cout<<"Data de nascimento: "<<dono.getDataNascimento().dia<<"/"<<dono.getDataNascimento().mes<<"/"<<dono.getDataNascimento().ano<<endl;
    cout<<"Endereço: Rua "<<dono.getEnderecoPessoal().rua<<", "<<dono.getEnderecoPessoal().numero<<endl;
    cout<<"Estado civil: "<<dono.getEstadoCivil()<<endl;
    cout<<"Número de filhos: "<<dono.getQtdFilhos()<<endl;
}

bool Empresa::buscaFuncionario(string matricula) {
    for(auto i:asgs) {
        if(i.getMatricula()==matricula) {
            cout<<"Funcionário encontrado!"<<endl;
            return true;
        }
    }
    for(auto i:vendedores) {
        if(i.getMatricula()==matricula) {
            cout<<"Funcionário encontrado!"<<endl;
            return true;
        }
    }
    for(auto i:gerentes) {
        if(i.getMatricula()==matricula) {
            cout<<"Funcionário encontrado!"<<endl;
            return true;
        }
    }
    cout<<"Funcionário não encontrado no sistema!"<<endl;
    return false;
}

float Empresa::calculaSalarioFuncionario(string matricula) {
    for(auto i:asgs) {
        if(i.getMatricula()==matricula) {
            cout<<"O salário do funcionário é: "<<i.calcularSalario()<<endl;
            return i.calcularSalario();
        }
    }
    for(auto i:vendedores) {
        if(i.getMatricula()==matricula) {
            cout<<"O salário do funcionário é: "<<i.calcularSalario()<<endl;
            return i.calcularSalario();
        }
    }
    for(auto i:gerentes) {
        if(i.getMatricula()==matricula) {
            cout<<"O salário do funcionário é: "<<i.calcularSalario()<<endl;
            return i.calcularSalario();
        }
    }
    cout<<"Funcionário não encontrado no sistema!"<<endl;
    return -1;
}

void Empresa::calculaTodosOsSalarios() {
    float total=0, totala=0, totalv=0, totalg=0;
    ofstream file("salarios.txt");
    if (!(file.is_open())) {
        cout<<"Arquivo não pôde ser aberto!"<<endl;
        return;
    }

    for(auto i:asgs) {
        file<<"Nome do funcionário: "<<i.getNome()<<endl;
        cout<<"Nome do funcionário: "<<i.getNome()<<endl;
        file<<"Cargo do funcionário: ASG"<<endl;
        cout<<"Cargo do funcionário: ASG"<<endl;
        file<<"Salário do funcionário: "<<i.calcularSalario()<<endl;
        cout<<"Salário do funcionário: "<<i.calcularSalario()<<endl;
        file<<"****************************************"<<endl;
        cout<<"****************************************"<<endl;
        total+=i.calcularSalario();
        totala+=i.calcularSalario();
    }
    file<<"-----------------------------"<<endl;
    cout<<"-----------------------------"<<endl;
    for(auto i:vendedores) {
        file<<"Nome do funcionário: "<<i.getNome()<<endl;
        cout<<"Nome do funcionário: "<<i.getNome()<<endl;
        file<<"Cargo do funcionário: vendedor"<<endl;
        cout<<"Cargo do funcionário: vendedor"<<endl;
        file<<"Salário do funcionário: "<<i.calcularSalario()<<endl;
        cout<<"Salário do funcionário: "<<i.calcularSalario()<<endl;
        file<<"****************************************"<<endl;
        cout<<"****************************************"<<endl;
        total+=i.calcularSalario();
        totalv+=i.calcularSalario();
    }
    file<<"-----------------------------"<<endl;
    cout<<"-----------------------------"<<endl;
    for(auto i:gerentes) {
        file<<"Nome do funcionário: "<<i.getNome()<<endl;
        cout<<"Nome do funcionário: "<<i.getNome()<<endl;
        file<<"Cargo do funcionário: gerente"<<endl;
        cout<<"Cargo do funcionário: gerente"<<endl;
        file<<"Salário do funcionário: "<<i.calcularSalario()<<endl;
        cout<<"Salário do funcionário: "<<i.calcularSalario()<<endl;
        file<<"****************************************"<<endl;
        cout<<"****************************************"<<endl;
        total+=i.calcularSalario();
        totalg+=i.calcularSalario();
    }
    file<<"-----------------------------"<<endl;
    cout<<"-----------------------------"<<endl;

    file<<"Total de salários dos funcionários ASG: "<<totala<<endl;
    cout<<"Total de salários dos funcionários ASG: "<<totala<<endl;
    file<<"Total de salários dos vendedores: "<<totalv<<endl;
    cout<<"Total de salários dos vendedores: "<<totalv<<endl;
    file<<"Total de salários dos gerentes: "<<totalg<<endl;
    cout<<"Total de salários dos gerentes: "<<totalg<<endl;

    file<<"-----------------------------"<<endl;
    cout<<"-----------------------------"<<endl;
    file<<"Total de salários dos funcionários: "<<total<<endl;
    cout<<"Total de salários dos funcionários: "<<total<<endl;

    file.close();
}

float Empresa::calcularRecisao(string matricula, Data desligamento) {
    for(auto i:asgs) {
        if(i.getMatricula()==matricula) {
            cout<<"A recisão do funcionário é: "<<i.calcularRecisao(desligamento)<<endl;
            return i.calcularRecisao(desligamento);
        }
    }
    for(auto i:vendedores) {
        if(i.getMatricula()==matricula) {
            cout<<"A recisão do funcionário é: "<<i.calcularRecisao(desligamento)<<endl;
            return i.calcularRecisao(desligamento);
        }
    }
    for(auto i:gerentes) {
        if(i.getMatricula()==matricula) {
            cout<<"A recisão do funcionário é: "<<i.calcularRecisao(desligamento)<<endl;
            return i.calcularRecisao(desligamento);
        }
    }
    cout<<"Funcionário não encontrado no sistema!"<<endl;
    return -1;
}