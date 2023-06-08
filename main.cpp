#include <iostream>
#include "util.hpp"
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Pessoa {
    private:
    string nome;
    string cpf;
    Data dataNascimento;
    Endereco enderecoPessoal;
    string estadoCivil;
    int qtdFilhos;

    public:
    Pessoa() {}
    Pessoa(string nome, string cpf, Data dataNascimento, Endereco enderecoPessoal, string estadociv, int qtdFilhos) {
        this->nome=nome;
        this->cpf=cpf;
        this->dataNascimento=dataNascimento;
        this->enderecoPessoal=enderecoPessoal;
        this->estadoCivil=estadociv;
        this->qtdFilhos=qtdFilhos;
    }

    string getNome() { return this->nome; }
    void setNome(string nome) { this->nome=nome; }
    string getCpf() { return this->cpf; }
    void setCpf(string cpf) { this->cpf=cpf; }
    Data getDataNascimento() { return this->dataNascimento; }
    void setDataNascimento(Data dataNascimento) { this->dataNascimento=dataNascimento; }
    Endereco getEnderecoPessoal() { return this->enderecoPessoal; }
    void setEnderecoPessoal(Endereco enderecoPessoal) { this->enderecoPessoal=enderecoPessoal; }
    string getEstadoCivil() { return this->estadoCivil; }
    void setEstadoCivil(string estadoCivil) { this->estadoCivil=estadoCivil; }
    int getQtdFilhos() { return this->qtdFilhos; }
    void setQtdFilhos(int qtdFilhos) { this->qtdFilhos=qtdFilhos; }
};

class Funcionario {
    private:
    string salario;
    string matricula;
    Data ingressoEmpresa;
    int faltas;

    public:
    string getSalario() { return this->salario; }
    void setSalario(string salario) { this->salario=salario; }
    string getMatricula() { return this->matricula; }
    void setMatricula(string matricula) { this->matricula=matricula; }
    Data getIngressoEmpresa() { return this->ingressoEmpresa; }
    void setIngressoEmpresa(Data ingressoEmpresa) { this->ingressoEmpresa=ingressoEmpresa; }
    int getFaltas() { return this->faltas; }
    void setFaltas(int diasfaltas) { this->faltas=diasfaltas; }
    virtual float calcularSalario()=0;
    virtual float calcularRecisao(Data desligamento)=0;
};

class Asg:public Pessoa, public Funcionario {
    private:
    float adicionalInsalubridade;

    public:
    Asg() {}
    Asg(string nome, string cpf, Data nasc, Endereco end, string estadocivil, int filhos, string salario, string matr, Data ingresso, int faltas, float adicional) {
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
    float getAdicionalInsalubridade() { return this->adicionalInsalubridade; }
    void setAdicionalInsalubridade(float adicional) { this->adicionalInsalubridade=adicional; }
    float calcularSalario() {
        int diasFaltas=getFaltas();
        float salario=stof(getSalario());
        salario-=(salario/30)*diasFaltas;
        salario*=adicionalInsalubridade;
        salario+=getQtdFilhos()*100;
        return salario;
    }
    float calcularRecisao(Data desligamento) {
        float desligamentodias, ingressodias;
        ingressodias=getIngressoEmpresa().ano*365+(getIngressoEmpresa().mes)*30+getIngressoEmpresa().dia;
        desligamentodias=desligamento.ano*365+desligamento.mes*30+desligamento.dia;
        float diferencaano=(desligamentodias-ingressodias)/365;
        float adicional=stof(getSalario())*diferencaano;
        return adicional;
    }
};

class Vendedor:public Pessoa, public Funcionario {
    private:
    char tipoVendedor;

    public:
    Vendedor() {}
    Vendedor(string nome, string cpf, Data nasc, Endereco end, string estadocivil, int filhos, string salario, string matr, Data ingresso, int faltas, char tipo) {
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
        this->tipoVendedor=tipo;
    }
    char getTipoVendedor() { return this->tipoVendedor; }
    void setTipoVendedor(char tipo) { this->tipoVendedor=tipo; }
    float calcularSalario() {
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
    float calcularRecisao(Data desligamento) {
        float desligamentodias, ingressodias;
        ingressodias=getIngressoEmpresa().ano*365+(getIngressoEmpresa().mes)*30+getIngressoEmpresa().dia;
        desligamentodias=desligamento.ano*365+desligamento.mes*30+desligamento.dia;
        float diferencaano=(desligamentodias-ingressodias)/365;
        float adicional=stof(getSalario())*diferencaano;
        return adicional;
    }
};

class Gerente:public Pessoa, public Funcionario {
    private:
    float participacaoLucros;

    public:
    Gerente() {}
    Gerente(string nome, string cpf, Data nasc, Endereco end, string estadocivil, int filhos, string salario, string matr, Data ingresso, int faltas, float lucro) {
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
        this->participacaoLucros=lucro;
    }
    float getParticipacaoLucros() { return this->participacaoLucros; }
    void setParticipacaoLucros(float lucro) { this->participacaoLucros=lucro; }
    float calcularSalario() {
        int diasfaltas=getFaltas();
        float salario=stof(getSalario());
        salario-=(salario/30)*diasfaltas;
        salario+=participacaoLucros;
        salario+=getQtdFilhos()*100;
        return salario;
    }
    float calcularRecisao(Data desligamento) {
        float desligamentodias, ingressodias;
        ingressodias=getIngressoEmpresa().ano*365+(getIngressoEmpresa().mes)*30+getIngressoEmpresa().dia;
        desligamentodias=desligamento.ano*365+desligamento.mes*30+desligamento.dia;
        float diferencaano=(desligamentodias-ingressodias)/365;
        float adicional=stof(getSalario())*diferencaano;
        return adicional;
    }
};

class Empresa {
    private:
    float faturamentoMensal;
    string nomeEmpresa;
    string cnpj;
    Pessoa dono;
    vector<Asg> asgs;
    vector<Vendedor> vendedores;
    vector<Gerente> gerentes;

    public:
    Empresa() {}
    Empresa(string nome, string cnpj, float faturamento) {
        this->cnpj=cnpj;
        this->faturamentoMensal=faturamento;
        this->nomeEmpresa=nome;
    }
    float getFaturamentoMensal() { return this->faturamentoMensal; }
    void setFaturamentoMensal(float faturamento) { this->faturamentoMensal=faturamento; }
    string getNomeEmpresa() { return this->nomeEmpresa; }
    void setNomeEmpresa(string nome) { this->nomeEmpresa=nome; }
    string getCnpj() { return this->cnpj; }
    void setCnpj(string cnpj) { this->cnpj=cnpj; }
    void carregarFuncoes();
    void carregarEmpresa();
    void carregarAsg();
    void carregaDono();
    void carregarVendedor();
    void carregarGerente();
    void imprimeAsgs();
    void imprimeVendedores();
    void imprimeGerentes();
    void imprimeDono();
    bool buscaFuncionario(int matricula);
    float calculaSalarioFuncionario(int matricula);
    void calculaTodosOsSalarios();
    float calcularRecisao(int matricula, Data desligamento);
};

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
            buscaFuncionario(stoi(parametro));
        }
        else if(linha=="calculaSalarioFuncionario()") {
            string parametro;
            getline(file, parametro);
            calculaSalarioFuncionario(stoi(parametro));
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

            calcularRecisao(stoi(matricula), data);
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
        cout<<"Endereço: "<<i.getEnderecoPessoal().rua<<", "<<i.getEnderecoPessoal().numero<<endl;
        cout<<"Estado civil: "<<i.getEstadoCivil()<<endl;
        cout<<"Número de filhos: "<<i.getQtdFilhos()<<endl;
        cout<<"Salário: "<<i.getSalario()<<endl;
        cout<<"Matrícula: "<<i.getMatricula()<<endl;
        cout<<"Data de nascimento: "<<i.getIngressoEmpresa().dia<<"/"<<i.getIngressoEmpresa().mes<<"/"<<i.getIngressoEmpresa().ano<<endl;
        cout<<"**********************************"<<endl;
    }
}
 
void Empresa::imprimeVendedores() {
    cout<<"Lista de vendedores:"<<endl;
    for(auto i:vendedores) {
        cout<<"Nome: "<<i.getNome()<<endl;
        cout<<"CPF: "<<i.getCpf()<<endl;
        cout<<"Data de nascimento: "<<i.getDataNascimento().dia<<"/"<<i.getDataNascimento().mes<<"/"<<i.getDataNascimento().ano<<endl;
        cout<<"Endereço: "<<i.getEnderecoPessoal().rua<<", "<<i.getEnderecoPessoal().numero<<endl;
        cout<<"Estado civil: "<<i.getEstadoCivil()<<endl;
        cout<<"Número de filhos: "<<i.getQtdFilhos()<<endl;
        cout<<"Salário: "<<i.getSalario()<<endl;
        cout<<"Matrícula: "<<i.getMatricula()<<endl;
        cout<<"Data de nascimento: "<<i.getIngressoEmpresa().dia<<"/"<<i.getIngressoEmpresa().mes<<"/"<<i.getIngressoEmpresa().ano<<endl;
        cout<<"**********************************"<<endl;
    }
}

void Empresa::imprimeGerentes() {
    cout<<"Lista de gerentes:"<<endl;
    for(auto i:gerentes) {
        cout<<"Nome: "<<i.getNome()<<endl;
        cout<<"CPF: "<<i.getCpf()<<endl;
        cout<<"Data de nascimento: "<<i.getDataNascimento().dia<<"/"<<i.getDataNascimento().mes<<"/"<<i.getDataNascimento().ano<<endl;
        cout<<"Endereço: "<<i.getEnderecoPessoal().rua<<", "<<i.getEnderecoPessoal().numero<<endl;
        cout<<"Estado civil: "<<i.getEstadoCivil()<<endl;
        cout<<"Número de filhos: "<<i.getQtdFilhos()<<endl;
        cout<<"Salário: "<<i.getSalario()<<endl;
        cout<<"Matrícula: "<<i.getMatricula()<<endl;
        cout<<"Data de nascimento: "<<i.getIngressoEmpresa().dia<<"/"<<i.getIngressoEmpresa().mes<<"/"<<i.getIngressoEmpresa().ano<<endl;
        cout<<"**********************************"<<endl;
    }
}

void Empresa::imprimeDono() {
    cout<<"Informações sobre dono:"<<endl;
    cout<<"Nome: "<<dono.getNome()<<endl;
    cout<<"CPF: "<<dono.getCpf()<<endl;
    cout<<"Data de nascimento: "<<dono.getDataNascimento().dia<<"/"<<dono.getDataNascimento().mes<<"/"<<dono.getDataNascimento().ano<<endl;
    cout<<"Endereço: "<<dono.getEnderecoPessoal().rua<<", "<<dono.getEnderecoPessoal().numero<<endl;
    cout<<"Estado civil: "<<dono.getEstadoCivil()<<endl;
    cout<<"Número de filhos: "<<dono.getQtdFilhos()<<endl;
}

bool Empresa::buscaFuncionario(int matricula) {
    for(auto i:asgs) {
        if(stoi(i.getMatricula())==matricula) {
            cout<<"Funcionário encontrado!"<<endl;
            return true;
        }
    }
    for(auto i:vendedores) {
        if(stoi(i.getMatricula())==matricula) {
            cout<<"Funcionário encontrado!"<<endl;
            return true;
        }
    }
    for(auto i:gerentes) {
        if(stoi(i.getMatricula())==matricula) {
            cout<<"Funcionário encontrado!"<<endl;
            return true;
        }
    }
    cout<<"Funcionário não encontrado no sistema!"<<endl;
    return false;
}

float Empresa::calculaSalarioFuncionario(int matricula) {
    if(buscaFuncionario(matricula)==false) {
        cout<<"Funcionário não encontrado no sistema!"<<endl;
        return 0;
    }
    for(auto i:asgs) {
        if(stoi(i.getMatricula())==matricula) 
            return stof(i.getSalario());
    }
    for(auto i:vendedores) {
        if(stoi(i.getMatricula())==matricula) 
            return stof(i.getSalario());
    }
    for(auto i:gerentes) {
        if(stoi(i.getMatricula())==matricula) 
            return stof(i.getSalario());
    }
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
    cout<<"Total de salários dos funcionários ASG: "<<totala<<endl;file<<"Total de salários de funcionários ASG: "<<totala<<endl;
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

float Empresa::calcularRecisao(int matricula, Data desligamento) {
    if(buscaFuncionario(matricula)==false) {
        cout<<"Funcionário não encontrado no sistema!"<<endl;
        return 0;
    }
    for(auto i:asgs) {
        if(stoi(i.getMatricula())==matricula) 
            return i.calcularRecisao(desligamento);
    }
    for(auto i:vendedores) {
        if(stoi(i.getMatricula())==matricula) 
            return i.calcularRecisao(desligamento);
    }
    for(auto i:gerentes) {
        if(stoi(i.getMatricula())==matricula) 
            return i.calcularRecisao(desligamento);
    }
}

int main() {
    Empresa *atacadoDosCalcados=new Empresa("Atacado dos Calçados", "40.101.588/0001-98", 156289.56);
    atacadoDosCalcados->carregarFuncoes();
}

/*testar*/
/*modularizar*/
/*testar*/