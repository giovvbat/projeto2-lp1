#include "util.hpp"
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <vector>

class Pessoa {
private:
  string nome;

  string cpf;

  Data nascimento;
  Endereco enderecoPessoal;

  string estadoCivil;

  int qtdFilhos;

public:
  Pessoa(){};

  Pessoa(string nome, string cpf, Data nascimento, Endereco enderecoPessoal,
         string estadoCivil, int qtdFilhos) {
    this->nome = nome;
    this->cpf = cpf;
    this->nascimento = nascimento;
    this->enderecoPessoal = enderecoPessoal;
    this->estadoCivil = estadoCivil;
    this->qtdFilhos = qtdFilhos;
  }
  // ● gets e set (para todos os atributos)
  void setNome(string nome) { this->nome = nome; };
  string getNome() { return this->nome; };
  void setCpf(string cpf) { this->cpf = cpf; };
  string getCpf() { return this->cpf; };
  void setEstadoCivil(string estadoCivil) { this->estadoCivil = estadoCivil; };
  string getEstadoCivil() { return this->estadoCivil; };
  void setFilhos(int qtdFilhos) { this->qtdFilhos = qtdFilhos; };
  int getFilhos() { return this->qtdFilhos; };
  Data getDataNascimento() { return this->nascimento; };
  void setDataNascimento(Data nascimento) { this->nascimento = nascimento; };
  Endereco getEnderecoPessoal() const { return this->enderecoPessoal; };
  void setEnderecoPessoal(Endereco enderecoPessoal) {
    this->enderecoPessoal = enderecoPessoal;
  };
};

class Funcionario {

  // atributos privados
private:
  int faltas;

  string salario;

  string matricula;

  Data ingressoEmpresa;

public:
  void setFaltas(int faltas) { this->faltas = faltas; };

  int getFaltas() { return this->faltas; };

  void setSalario(string salario) { this->salario = salario; };
  string getSalario() { return this->salario; };
  void setMatricula(string matricula) { this->matricula = matricula; };
  string getMatricula() { return this->matricula; };
  void setIngressoEmpresa(Data ingressoEmpresa) {
    this->ingressoEmpresa = ingressoEmpresa;
  };
  Data getIngressoEmpresa() { return this->ingressoEmpresa; };

  virtual float calcularSalario() = 0;

  virtual float calcularRecisao(Data desligamento) = 0;
};

class Asg : public Pessoa, public Funcionario {
  // Crie um classe concreta chamada Asg que herda de Pessoa e Funcionario
  // (herança múltipla) com os seguintes atributos:
private:
  // privado
  float adicionalInsalubridade;

public:
  Asg(){};
  // ● construtor parametrizados (com todos os atributos);
  Asg(float adcionalInsalubridade) {
    this->adicionalInsalubridade = adicionalInsalubridade;
  };
  // ● gets e set (para todos os atributos);
  void setAdicionalInsalubridade(float adicionalInsalubridade) {
    this->adicionalInsalubridade = adicionalInsalubridade;
  };
  float getAdicionalInsalubridade() { return this->adicionalInsalubridade; };

  // ● métodos abstratos da classe Funcionario implementados.

  float calcularSalario() {
    // recebe as faltas
    int faltas = this->getFaltas();
    // recebe o salario base
    float salarioAsg = stof(this->getSalario());
    // subtrai o valor relativo aos dias de falta
    salarioAsg = salarioAsg - (faltas * (salarioAsg / 30));
    // adiciona o adicional de insalubridade referente ao salario RECEBIDO
    salarioAsg += (salarioAsg * adicionalInsalubridade);
    // soma o adiocional de 100 reais referente a cada filho que o Asg possui
    salarioAsg += (this->getFilhos() * 100);
    return salarioAsg;
  };

  float calcularRecisao(Data desligamento) {
    // dados de desligamento
    int diaDesligamento = desligamento.dia;
    int mesDesligamento = desligamento.mes;
    int anoDesligamento = desligamento.ano;
    // dados de ingresso
    int diaIngresso = getIngressoEmpresa().dia;
    int mesIngresso = getIngressoEmpresa().mes;
    int anoingresso = getIngressoEmpresa().dia;
    // matematica envolvida pra colocar tudo em função de dia
    float Desligamento =
        ((anoDesligamento * 365) + (mesDesligamento * 30) + diaDesligamento);
    float Ingresso = ((anoingresso * 365) + (mesIngresso * 30) + diaIngresso);
    // colocando tudo em função de ano pra calcular o salario
    float salarioAsg = stof(this->getSalario());
    float rescisao = ((Desligamento - Ingresso) / 365) * salarioAsg;
    return rescisao;
  };
};

class Vendedor : public Pessoa, public Funcionario {
private:
  char tipoVendedor;

public:
  // ● construtor vazio;
  Vendedor(){};
  // ● construtor parametrizados (com todos os atributos);
  Vendedor(char tipoVendedor) { this->tipoVendedor = tipoVendedor; };
  // ● gets e set (para todos os atributos);
  void setTipoVendedor(char tipoVendedor) {
    this->tipoVendedor = tipoVendedor;
  };
  char getTipoVendedor() { return this->tipoVendedor; };
  float calcularSalario() {
    // recebe as faltas
    int faltas = this->getFaltas();
    //  recebe o salario base
    float salarioVendedor = stof(getSalario());
    //  subtrai o valor relativo aos dias de falta
  salarioVendedor = salarioVendedor - (faltas * (salarioVendedor/30));
  // adiciona a bonificação referente ao tipo do vendedor
    if (tipoVendedor == 'A' ){
      salarioVendedor += (0.25 * salarioVendedor);
    }
    if (tipoVendedor == 'B'){
      salarioVendedor += (0.1 * salarioVendedor);
    }
    else{
      salarioVendedor += (0.05 * salarioVendedor);
    }
  // soma o adiocional de 100 reais referente a cada filho que o Vendedor possui
  salarioVendedor += (this->getFilhos() * 100);
  return salarioVendedor;

  };
  float calcularRecisao(Data desligamento) {
    // dados de desligamento
    int diaDesligamento = desligamento.dia;
    int mesDesligamento = desligamento.mes;
    int anoDesligamento = desligamento.ano;
    // dados de ingresso
    int diaIngresso = getIngressoEmpresa().dia;
    int mesIngresso = getIngressoEmpresa().mes;
    int anoingresso = getIngressoEmpresa().dia;
    // matematica envolvida pra colocar tudo em função de dia
    float Desligamento =
        ((anoDesligamento * 365) + (mesDesligamento * 30) + diaDesligamento);
    float Ingresso = ((anoingresso * 365) + (mesIngresso * 30) + diaIngresso);
    // colocando tudo em função de ano pra calcular o salario
    float salarioVendedor = stof(this->getSalario());
    float rescisao = ((Desligamento - Ingresso) / 365) * salarioVendedor;
    return rescisao;
  };
};

class Gerente : public Pessoa, public Funcionario {
private:
  float participacaoLucros;

public:
  Gerente(){};
  Gerente(float participacaoLucros) {
    this->participacaoLucros = participacaoLucros;
  };

  void setParticipacaoLucros(float participacaoLucros) {
    this->participacaoLucros = participacaoLucros;
  };

  float getParticipacaoLucros() { return this->participacaoLucros; }
  float calcularSalario() {
    // recebe as faltas do funcionario
    int faltas = this->getFaltas();
    // recebe o salario base
    float salarioGerente = stof(this->getSalario());
    // subtrai o valor relativo aos dias de falta
  salarioGerente = salarioGerente - (faltas * (salarioGerente/30));
  // adiciona a participação dos lucros
  salarioGerente += participacaoLucros;
  // soma o adiocional de 100 reais referente a cada filho que o Gerente possui
  int filhosGerente = this->getFilhos();
  salarioGerente += ( filhosGerente * 100);
  return salarioGerente;
  };
  float calcularRecisao(Data desligamento) {
    // dados de desligamento
    int diaDesligamento = desligamento.dia;
    int mesDesligamento = desligamento.mes;
    int anoDesligamento = desligamento.ano;
    // dados de ingresso
    int diaIngresso = getIngressoEmpresa().dia;
    int mesIngresso = getIngressoEmpresa().mes;
    int anoingresso = getIngressoEmpresa().dia;
    // matematica envolvida pra colocar tudo em função de dia
    float Desligamento =
        ((anoDesligamento * 365) + (mesDesligamento * 30) + diaDesligamento);
    float Ingresso = ((anoingresso * 365) + (mesIngresso * 30) + diaIngresso);
    // colocando tudo em função de ano pra calcular o salario
    float salarioGerente = stof(this->getSalario());
    float rescisao = ((Desligamento - Ingresso) / 365) * salarioGerente;
    return rescisao;
  };
};

class Empresa {
private:
  // ● faturamentoMensal (float);
  float faturamentoMensal;
  // ● nomeEmpresa (string);
  string nomeEmpresa;
  // ● cnpj (string);
  string cnpj;
  // ● dono (Pessoa);
  Pessoa dono;
  // ● asgs (vector<Asg>);
  vector<Asg> asgs;
  // ● vendedores (vector<Vendedor>) ;
  vector<Vendedor> vendedores;
  // ● gerentes (vector<Gerente>);
  vector<Gerente> gerentes;
  // e os seguintes métodos:

public:
  // ● construtor vazio;
  Empresa(){};
  // ● construtor parametrizados (apenas com o nomeEmpresa, cnpj e
  // faturamentoMensal);
  Empresa(string nomeEmpresa, string cnpj, float faturamentoMensal) {
    this->nomeEmpresa = nomeEmpresa;
    this->cnpj = cnpj;
    this->faturamentoMensal = faturamentoMensal;
  };

  // ● gets e set (faturamentoMensal, nomeEmpresa, cnpj));
  float getFaturamentoMensal() { return this->faturamentoMensal; };
  void setFaturamentoMensal(float faturamentoMensal) {
    this->faturamentoMensal = faturamentoMensal;
  };
  string getNomeEmpresa() { return this->nomeEmpresa; };
  void setNomeEmpresa(string nomeEmpresa) { this->nomeEmpresa = nomeEmpresa; };
  string getCnpj() { return this->cnpj; };
  void setCnpj(string cnpj) { this->cnpj = cnpj; };

  void carregaDono() {
    ifstream donotemp("dono.txt");
    string temp;
    getline(donotemp, temp);
    getline(donotemp, temp);
    getline(donotemp, temp);
    dono.setNome(temp);
    getline(donotemp, temp);
    dono.setCpf(temp);
    getline(donotemp, temp);
    dono.setFilhos(stoi(temp));
    getline(donotemp, temp);
    dono.setEstadoCivil(temp);
    getline(donotemp, temp);
    Endereco lugar;
    lugar.cidade = temp;
    getline(donotemp, temp);
    lugar.cep = temp;
    getline(donotemp, temp);
    lugar.bairro = temp;
    getline(donotemp, temp);
    lugar.rua = temp;
    getline(donotemp, temp);
    lugar.numero = stoi(temp);
    dono.setEnderecoPessoal(lugar);
    Data nasci;
    getline(donotemp, temp);
    nasci.ano = stoi(temp);
    getline(donotemp, temp);
    nasci.mes = stoi(temp);
    getline(donotemp, temp);
    nasci.dia = stoi(temp);
    dono.setDataNascimento(nasci);

    donotemp.close();
  };

  void imprimeDono() {
    cout << "Nome do dono:" << dono.getNome() << endl;
    cout << "Cpf do dono: " << dono.getCpf() << endl;
    cout << "Quantidade de filhos do dono: " << dono.getFilhos() << endl;
    cout << "Estado civil do dono: " << dono.getEstadoCivil() << endl;
    cout << "Endereço do dono: " << dono.getEnderecoPessoal().rua << " "
         << dono.getEnderecoPessoal().numero << ", "
         << dono.getEnderecoPessoal().bairro << " - "
         << dono.getEnderecoPessoal().cep << "/"
         << dono.getEnderecoPessoal().cidade << endl;
    cout << "Data de nascimento do dono: " << dono.getDataNascimento().dia
         << "/" << dono.getDataNascimento().mes << "/"
         << dono.getDataNascimento().ano << endl;
  };

  void carregarAsgs(){
    ifstream arquivoAsg("asg.txt");
    string temp;
    Asg asgTemp;
    Data nasciAsg;
    Data ingressoAsg;
    Endereco lugar;
    while (getline(arquivoAsg, temp)) {
      getline(arquivoAsg, temp);
      getline(arquivoAsg, temp);
        
      getline(arquivoAsg, temp);
      asgTemp.setNome(temp);
      getline(arquivoAsg, temp);
      asgTemp.setCpf(temp);
      getline(arquivoAsg, temp);
      asgTemp.setFilhos(stoi(temp));
      getline(arquivoAsg, temp);
      asgTemp.setEstadoCivil(temp);
        
      getline(arquivoAsg, temp);
        
      getline(arquivoAsg, temp);
      lugar.cidade = temp;
      getline(arquivoAsg, temp);
      lugar.cep = temp;
      getline(arquivoAsg, temp);
      lugar.bairro = temp;
      getline(arquivoAsg, temp);
      lugar.rua = temp;
      getline(arquivoAsg, temp);
      lugar.numero = stoi(temp);
      asgTemp.setEnderecoPessoal(lugar);
        
      getline(arquivoAsg, temp);
        
      getline(arquivoAsg, temp);
      nasciAsg.ano = stoi(temp);
      getline(arquivoAsg, temp);
      nasciAsg.mes = stoi(temp);
      getline(arquivoAsg, temp);
      nasciAsg.dia = stoi(temp);
      asgTemp.setDataNascimento(nasciAsg);
        
      getline(arquivoAsg, temp);
        
      getline(arquivoAsg, temp);
      asgTemp.setMatricula(temp);
      getline(arquivoAsg, temp);
      asgTemp.setSalario(temp);
      getline(arquivoAsg, temp);
      asgTemp.setAdicionalInsalubridade(stof(temp));
      getline(arquivoAsg,temp);
      asgTemp.setFaltas(stoi(temp));
        
      getline(arquivoAsg, temp);
        
      getline(arquivoAsg, temp);
      ingressoAsg.ano = stoi(temp);
      getline(arquivoAsg, temp);
      ingressoAsg.mes = stoi(temp);
      getline(arquivoAsg, temp);
      ingressoAsg.dia = stoi(temp);
      asgTemp.setIngressoEmpresa(ingressoAsg);

      asgs.push_back(asgTemp);
    }
  };

  void imprimeAsgs(){
    cout << "Lista de funcionarios ASG: " << endl;
    for (auto i : asgs) {
      cout << "Nome: " << i.getNome() << endl;
      cout << "Cpf: " << i.getCpf() << endl;
      cout << "Quantidade de filhos: " << i.getFilhos() << endl;
      cout << "Estado civil: " << i.getEstadoCivil() << endl;
      cout << "Endereço: " << i.getEnderecoPessoal().rua << " "
           << i.getEnderecoPessoal().numero << ", "
           << i.getEnderecoPessoal().bairro << " - "
           << i.getEnderecoPessoal().cep << "/" << i.getEnderecoPessoal().cidade << endl;
      cout << "Data de nascimento: " << i.getDataNascimento().dia << "/"
           << i.getDataNascimento().mes << "/" << i.getDataNascimento().ano
           << endl;
      cout << "Matricula: " << i.getMatricula() << endl;
      cout << "Salario mensal(base): " << i.getSalario() << endl;
      cout << "Porcentagem de insalubridade: " << i.getAdicionalInsalubridade()
           << endl;
      cout << "Faltas: " << i.getFaltas() << endl;
      cout << "Data de ingresso: " << i.getIngressoEmpresa().dia << "/"
           << i.getIngressoEmpresa().mes << "/" << i.getIngressoEmpresa().ano
           << endl;
    }
  };

  void carregarGerente(){
    ifstream arquivoGerente("gerente.txt");
    string temp;
    Gerente GerenteTemp;
    Data nasciGerente;
    Data ingressoGerente;
    Endereco lugar;
    while (getline(arquivoGerente, temp)) {
      getline(arquivoGerente, temp);
      getline(arquivoGerente, temp);
        
      getline(arquivoGerente, temp);
      GerenteTemp.setNome(temp);
      getline(arquivoGerente, temp);
      GerenteTemp.setCpf(temp);
      getline(arquivoGerente, temp);
      GerenteTemp.setFilhos(stoi(temp));
      getline(arquivoGerente, temp);
      GerenteTemp.setEstadoCivil(temp);
        
      getline(arquivoGerente, temp);
        
      getline(arquivoGerente, temp);
      lugar.cidade = temp;
      getline(arquivoGerente, temp);
      lugar.cep = temp;
      getline(arquivoGerente, temp);
      lugar.bairro = temp;
      getline(arquivoGerente, temp);
      lugar.rua = temp;
      getline(arquivoGerente, temp);
      lugar.numero = stoi(temp);
      GerenteTemp.setEnderecoPessoal(lugar);
        
      getline(arquivoGerente, temp);
        
      getline(arquivoGerente, temp);
      nasciGerente.ano = stoi(temp);
      getline(arquivoGerente, temp);
      nasciGerente.mes = stoi(temp);
      getline(arquivoGerente, temp);
      nasciGerente.dia = stoi(temp);
      GerenteTemp.setDataNascimento(nasciGerente);
        
      getline(arquivoGerente, temp);
        
      getline(arquivoGerente, temp);
      GerenteTemp.setMatricula(temp);
      getline(arquivoGerente, temp);
      GerenteTemp.setSalario(temp);
      getline(arquivoGerente, temp);
      GerenteTemp.setParticipacaoLucros(stof(temp));
      getline(arquivoGerente,temp);
      GerenteTemp.setFaltas(stoi(temp));
        
      getline(arquivoGerente, temp);
        
      getline(arquivoGerente, temp);
      ingressoGerente.ano = stoi(temp);
      getline(arquivoGerente, temp);
      ingressoGerente.mes = stoi(temp);
      getline(arquivoGerente, temp);
      ingressoGerente.dia = stoi(temp);
      GerenteTemp.setIngressoEmpresa(ingressoGerente);

      gerentes.push_back(GerenteTemp);
    };
  };

  void imprimeGerentes() {
    cout << "Lista de Gerentes:" << endl;
    for (auto i : gerentes) {
      cout << "Nome: " << i.getNome() << endl;
      cout << "Cpf: " << i.getCpf() << endl;
      cout << "Quantidade de filhos: " << i.getFilhos() << endl;
      cout << "Estado civil: " << i.getEstadoCivil() << endl;
      cout << "Endereço: " << i.getEnderecoPessoal().rua << " "
           << i.getEnderecoPessoal().numero << ", "
           << i.getEnderecoPessoal().bairro << " - "
           << i.getEnderecoPessoal().cep << "/" << i.getEnderecoPessoal().cidade
           << endl;
      cout << "Data de nascimento: " << i.getDataNascimento().dia << "/"
           << i.getDataNascimento().mes << "/" << i.getDataNascimento().ano
           << endl;
      cout << "Matricula: " << i.getMatricula() << endl;
      cout << "Salario mensal(base): " << i.getSalario() << endl;
      cout << "Participação nos Lucros: " << i.getParticipacaoLucros() << endl;
      cout << "Faltas: " << i.getFaltas() << endl;
      cout << "Data de ingresso: " << i.getIngressoEmpresa().dia << "/"
           << i.getIngressoEmpresa().mes << "/" << i.getIngressoEmpresa().ano
           << endl;
    }
  };

  void carregaVendedor(){
    ifstream arquivoVendedor("vendedor.txt");
    string temp;
    Vendedor VendedorTemp;
    Data nasciVendedor;
    Data ingressoAsg;
    Endereco lugar;
    while (getline(arquivoVendedor, temp)) {
      getline(arquivoVendedor, temp);
      getline(arquivoVendedor, temp);
      getline(arquivoVendedor, temp);
      VendedorTemp.setNome(temp);
      getline(arquivoVendedor, temp);
      VendedorTemp.setCpf(temp);
      getline(arquivoVendedor, temp);
      VendedorTemp.setFilhos(stoi(temp));
      getline(arquivoVendedor, temp);
      VendedorTemp.setEstadoCivil(temp);
      getline(arquivoVendedor, temp);
      getline(arquivoVendedor, temp);
      lugar.cidade = temp;
      getline(arquivoVendedor, temp);
      lugar.cep = temp;
      getline(arquivoVendedor, temp);
      lugar.bairro = temp;
      getline(arquivoVendedor, temp);
      lugar.rua = temp;
      getline(arquivoVendedor, temp);
      lugar.numero = stoi(temp);
      getline(arquivoVendedor, temp);
      getline(arquivoVendedor, temp);
      nasciVendedor.ano = stoi(temp);
      getline(arquivoVendedor, temp);
      nasciVendedor.mes = stoi(temp);
      getline(arquivoVendedor, temp);
      nasciVendedor.dia = stoi(temp);
      getline(arquivoVendedor, temp);
      getline(arquivoVendedor, temp);
      VendedorTemp.setMatricula(temp);
      getline(arquivoVendedor, temp);
      VendedorTemp.setSalario(temp);
      getline(arquivoVendedor, temp);
      char c = temp[0];
      VendedorTemp.setTipoVendedor(c);
      getline(arquivoVendedor,temp);
      VendedorTemp.setFaltas(stoi(temp));
      getline(arquivoVendedor, temp);
      getline(arquivoVendedor, temp);
      ingressoAsg.ano = stoi(temp);
      getline(arquivoVendedor, temp);
      ingressoAsg.mes = stoi(temp);
      getline(arquivoVendedor, temp);
      ingressoAsg.dia = stoi(temp);
    };
  };

  // função de imprimir os vendedores
  void imprimeVendedores() {
    cout << "Lista de Vendedores:" << endl;
    for (auto i : vendedores) {
      cout << "Nome: " << i.getNome() << endl;
      cout << "Cpf: " << i.getCpf() << endl;
      cout << "Quantidade de filhos: " << i.getFilhos() << endl;
      cout << "Estado civil: " << i.getEstadoCivil() << endl;
      cout << "Endereço: " << i.getEnderecoPessoal().rua << " "<< i.getEnderecoPessoal().numero << ", "<< i.getEnderecoPessoal().bairro << " - "<< i.getEnderecoPessoal().cep << "/" << i.getEnderecoPessoal().cidade<< endl;
      cout << "Data de nascimento: " << i.getDataNascimento().dia << "/"<< i.getDataNascimento().mes << "/" << i.getDataNascimento().ano<< endl;
      cout << "Matricula: " << i.getMatricula() << endl;
      cout << "Salario mensal(base): " << i.getSalario() << endl;
      cout << "Tipagem do funcionário: " << i.getTipoVendedor() << endl;
      cout << "Faltas: " << i.getFaltas() << endl;
      cout << "Data de ingresso: " << i.getIngressoEmpresa().dia << "/"<< i.getIngressoEmpresa().mes << "/" << i.getIngressoEmpresa().ano<< endl;
    };
  };

  // função pra carregar os dados da Empresa
  void carregaEmpresa() {
    ifstream empresa("empresa.txt");
    string temp;
    getline(empresa, temp);
    getline(empresa, temp);
    getline(empresa, temp);
    setNomeEmpresa(temp);
    getline(empresa, temp);
    setCnpj(temp);
    getline(empresa, temp);
    setFaturamentoMensal(stof(temp));
    getline(empresa, temp);
  };

  void buscaFuncionario(string matricula) {
    cout << "Buscando Funcionario..." << endl;
    // faz a busca no vector dos asgs e imprime dados basicos do funcionario, se
    // encontrar
    for (auto &asg : asgs) {
      if (asg.getMatricula() == matricula) {
        cout << "Funcionario encontrado! " << endl;
        cout << "Nome: " << asg.getNome() << endl;
        cout << "Função: Associdado de Serviços Gerais" << endl;
      }
    }
    // faz a busca no vector dos vendedores e imprime dados basicos do
    // funcionario, se encontrar
    for (auto &vendedor : vendedores) {
      if (vendedor.getMatricula() == matricula) {
        cout << "Funcionario encontrado! " << endl;
        cout << "Nome: " << vendedor.getNome() << endl;
        cout << "Função: Vendedor de tipo " << vendedor.getTipoVendedor()
             << endl;
      }
    }
    // faz a busca no vector dos Gerentes e imprime dados basicos do
    // funcionario, se encontrar
    for (auto &Gerente : gerentes) {
      if (Gerente.getMatricula() == matricula) {
        cout << "Funcionario encontrado! " << endl;
        cout << "Nome: " << Gerente.getNome() << endl;
        cout << "Função: Gerente" << endl;
      }
    }
    // informa que não encontrou o funcionario requisitado
    cout << "Funcionario não encontrado no sistema" << endl;
  };

  void calculaSalarioFuncionario(string matricula) {
    // faz a busca no vector dos asgs e imprime dados basicos do funcionario
    // juntamente de seu salario, se encontrar
    for (auto &asg : asgs) {
      if (asg.getMatricula() == matricula) {
        int faltas = asg.getFaltas();
        cout << "Nome: " << asg.getNome() << endl;
        cout << "Função: Associado de serviços gerais" << endl;
        float salario = asg.calcularSalario();
        cout << "Salario: " << salario << endl;
      }
    }
    // faz a busca no vector dos asgs e imprime dados basicos do funcionario
    // juntamente de seu salario, se encontrar
    for (auto &vendedor : vendedores) {
      if (vendedor.getMatricula() == matricula) {
        int faltas1 = vendedor.getFaltas();
        cout << "Nome: " << vendedor.getNome() << endl;
        cout << "Função: Associado de serviços gerais" << endl;
        float salario1 = vendedor.calcularSalario();
        cout << "Salario: " << salario1 << endl;
      }
    }
    // faz a busca no vector dos Gerentes e imprime dados basicos do funcionario
    // junto de seu salario, se encontrar
    for (auto &Gerente : gerentes) {
      if (Gerente.getMatricula() == matricula) {
        int faltas2 = Gerente.getFaltas();
        cout << "Nome: " << Gerente.getNome() << endl;
        cout << "Função: Associado de serviços gerais" << endl;
        float salario2 = Gerente.calcularSalario();
        cout << "Salario: " << salario2 << endl;
      }
    }

    cout << "funcionario não encontrado no sistema" << endl;
  };

  void calcularRecisao(string matricula, Data desligamento) {
    for (auto &asg : asgs) {
      if (asg.getMatricula() == matricula) {
        int dia = asg.getIngressoEmpresa().dia;
        int mes = asg.getIngressoEmpresa().mes;
        int ano = asg.getIngressoEmpresa().ano;

        Data saida;
        saida.dia = dia;
        saida.mes = mes;
        saida.ano = ano;
        float recisao = asg.calcularRecisao(saida);

        cout << "A recisao do funcionario de matricula " << asg.getMatricula()
             << " é de R$ " << recisao << endl;
      }
    }
    for (auto &vendedor : vendedores) {
      if (vendedor.getMatricula() == matricula) {
        int dia = vendedor.getIngressoEmpresa().dia;
        int mes = vendedor.getIngressoEmpresa().mes;
        int ano = vendedor.getIngressoEmpresa().ano;

        Data saida;
        saida.dia = dia;
        saida.mes = mes;
        saida.ano = ano;
        float recisao = vendedor.calcularRecisao(saida);

        cout << "A recisao do funcionario de matricula "
             << vendedor.getMatricula() << " é de R$ " << recisao << endl;
      }
    }

    for (auto &Gerente : gerentes) {
      if (Gerente.getMatricula() == matricula) {
        int dia = Gerente.getIngressoEmpresa().dia;
        int mes = Gerente.getIngressoEmpresa().mes;
        int ano = Gerente.getIngressoEmpresa().ano;

        Data saida;
        saida.dia = dia;
        saida.mes = mes;
        saida.ano = ano;
        float recisao = Gerente.calcularRecisao(saida);

        cout << "A recisao do funcionario de matricula "
             << Gerente.getMatricula() << " é de R$ " << recisao << endl;
      }
    }

    cout << "Funcionario não encontrado no sistema" << endl;
  };

  void carregaFuncoes() {
    ifstream funcoes("funcoes.txt");
    string temp;
    while (getline(funcoes, temp)) {
      if (temp == "carregaEmpresa()") {
        carregaEmpresa();
      };
      if (temp == "carregarAsgs()") {
        carregarAsgs();
      };
      if (temp == "carregarGerente") {
        carregarGerente();
      };
      if (temp == "carregaVendedor()") {
        carregaVendedor();
      };
      if (temp == "carregaDono()") {
        carregaDono();
      };
      if (temp == "imprimeAsgs()") {
        imprimeAsgs();
      };
      if (temp == "imprimeVendedores()") {
        imprimeVendedores();
      };
      if (temp == "imprimeGerentes()") {
        imprimeGerentes();
      };
      if (temp == "imprimeDono()") {
        imprimeDono();
      };
      if (temp == "buscaFuncionario()") {
        getline(funcoes, temp);
        buscaFuncionario(temp);
      };
      if (temp == "calculaSalarioFuncionario()") {
        getline(funcoes, temp);
        calculaSalarioFuncionario(temp);
      }
      if (temp == "calculaTodosOsSalarios()") {
        calculaTodosOsSalarios();
      };
      if (temp == "calcularRecisao()") {
        getline(funcoes, temp);
        string matricula = temp;
        Data recisao;
        getline(funcoes, temp);
        recisao.ano = stoi(temp);
        getline(funcoes, temp);
        recisao.mes = stoi(temp);
        getline(funcoes, temp);
        recisao.ano = stoi(temp);
        calcularRecisao(matricula, recisao);
      };
    };
  };

  void calculaTodosOsSalarios() {
    ofstream arquivo("salarios.txt");
    string temp;
    arquivo << "Relatório de salarios da Empresa:" << endl;
    arquivo << "" << endl;
    for (auto i : asgs) {
      string nome = i.getNome();
      i.calcularSalario();
      float salario = i.calcularSalario();
      float geralSalarios;
      geralSalarios += i.calcularSalario();
      arquivo << "######################################################"
              << endl;
      arquivo << "Nome do funcionario: " << nome << endl;
      arquivo << "Cargo: Auxiliar de Serviços Gerais" << endl;
      arquivo << "Salário: " << salario << endl;
    };
    for (auto i : gerentes) {
      string nome = i.getNome();
      i.calcularSalario();
      float salario = i.calcularSalario();
      float geralSalarios;
      geralSalarios += i.calcularSalario();
      arquivo << "######################################################"
              << endl;
      arquivo << "Nome do funcionario: " << nome << endl;
      arquivo << "Cargo: Gerente" << endl;
      arquivo << "Salário: " << salario << endl;
    };
    for (auto i : vendedores) {
      string nome = i.getNome();
      i.calcularSalario();
      char tipo = i.getTipoVendedor();
      float salario = i.calcularSalario();
      float geralSalarios;
      geralSalarios += i.calcularSalario();
      arquivo << "######################################################"
              << endl;
      arquivo << "Nome do funcionario: " << nome << endl;
      arquivo << "Cargo: Vendedore de tipo " << tipo << endl;
      arquivo << "Salário: " << salario << endl;
    }
    arquivo << "######################################################" << endl;
  };
};
int main(){

  Empresa empresa;
  empresa.carregaFuncoes();

  return 0;
}