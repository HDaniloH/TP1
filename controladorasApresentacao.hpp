#ifndef CONTROLADORASAPRESENTACAO_HPP
#define CONTROLADORASAPRESENTACAO_HPP

#include "interfaces.hpp"
#include <iostream>
#include <string>
#include <stdexcept>

// ===================== AUTENTICACAO =====================
/// Controladora da camada de apresentacao para autenticacao.
class CntrApresentacaoAutenticacao : public IAAutenticacao {
private:
    ISAutenticacao* cntrServicoAutenticacao;
public:
    void setCntrServicoAutenticacao(ISAutenticacao*);
    bool autenticar(Email*) override;
};

inline void CntrApresentacaoAutenticacao::setCntrServicoAutenticacao(ISAutenticacao* cntr){
    cntrServicoAutenticacao = cntr;
}

inline bool CntrApresentacaoAutenticacao::autenticar(Email* email){
    Senha senha;
    std::string entradaEmail, entradaSenha;
    std::cout << "\n=== Autenticacao ===\n";
    std::cout << "Email: ";
    std::cin  >> entradaEmail;
    std::cout << "Senha: ";
    std::cin  >> entradaSenha;
    try {
        email->setEmail(entradaEmail);
        senha.setSenha(entradaSenha);
    } catch (std::invalid_argument& exc) {
        std::cout << "Dado invalido: " << exc.what() << "\n";
        return false;
    }
    return cntrServicoAutenticacao->autenticar(*email, senha);
}

// ===================== GESTAO DE PESSOA =====================
/// Controladora da camada de apresentacao para gestao de Pessoa.
class CntrApresentacaoPessoa : public IAPessoa {
private:
    ISPessoa* cntrServicoPessoa;   ///< Ligacao com a camada de servico.

    bool lerDadosPessoa(Pessoa&);
    bool lerEmail(Email&);
    void exibirPessoa(const Pessoa&);

public:
    void setCntrServicoPessoa(ISPessoa*);
    void executar(const Email&) override;
};

inline void CntrApresentacaoPessoa::setCntrServicoPessoa(ISPessoa* cntr){
    cntrServicoPessoa = cntr;
}

inline bool CntrApresentacaoPessoa::lerEmail(Email& email){
    std::string entrada;
    std::cout << "Email: ";
    std::cin  >> entrada;
    try {
        email.setEmail(entrada);
    } catch (std::invalid_argument& exc) {
        std::cout << "Email invalido: " << exc.what() << "\n";
        return false;
    }
    return true;
}

inline bool CntrApresentacaoPessoa::lerDadosPessoa(Pessoa& pessoa){
    Nome  nome;
    Email email;
    Senha senha;
    Papel papel;
    std::string entradaNome, entradaEmail, entradaSenha;
    int entradaPapel;

    try {
        std::cout << "Nome: ";
        std::cin  >> entradaNome;
        nome.setNome(entradaNome);

        std::cout << "Email: ";
        std::cin  >> entradaEmail;
        email.setEmail(entradaEmail);

        std::cout << "Senha: ";
        std::cin  >> entradaSenha;
        senha.setSenha(entradaSenha);

        std::cout << "Papel (1-Desenvolvedor, 2-Mestre Scrum, 3-Proprietario): ";
        std::cin  >> entradaPapel;
        papel.setEscolha_papel(entradaPapel);
    } catch (std::invalid_argument& exc) {
        std::cout << "Dado invalido: " << exc.what() << "\n";
        return false;
    }

    pessoa.setNome(nome);
    pessoa.setEmail(email);
    pessoa.setSenha(senha);
    pessoa.setPapel(papel);
    return true;
}

inline void CntrApresentacaoPessoa::exibirPessoa(const Pessoa& pessoa){
    std::cout << "\n--- Dados da Pessoa ---\n";
    std::cout << "Nome : " << pessoa.getNome().getNome()           << "\n";
    std::cout << "Email: " << pessoa.getEmail().getEmail()         << "\n";
    std::cout << "Papel: " << pessoa.getPapel().getEscolha_papel() << "\n";
    std::cout << "-----------------------\n";
}

inline void CntrApresentacaoPessoa::executar(const Email& email){
    int opcao;
    std::cout << "\nBem-vindo(a), " << email.getEmail() << "!\n";

    do {
        std::cout << "\n===== Gestao de Pessoa =====\n";
        std::cout << "1 - Criar\n";
        std::cout << "2 - Ler\n";
        std::cout << "3 - Atualizar\n";
        std::cout << "4 - Excluir\n";
        std::cout << "0 - Sair\n";
        std::cout << "Escolha: ";
        std::cin  >> opcao;

        switch(opcao){
            case 1: {
                Pessoa pessoa;
                if(lerDadosPessoa(pessoa)){
                    if(cntrServicoPessoa->criar(pessoa))
                        std::cout << "Pessoa criada com sucesso!\n";
                    else
                        std::cout << "Nao foi possivel criar (ja existe).\n";
                }
                break;
            }
            case 2: {
                Email chave;
                if(lerEmail(chave)){
                    Pessoa pessoa;
                    pessoa.setEmail(chave);
                    if(cntrServicoPessoa->ler(pessoa))
                        exibirPessoa(pessoa);
                    else
                        std::cout << "Pessoa nao encontrada.\n";
                }
                break;
            }
            case 3: {
                std::cout << "Informe os dados atualizados da pessoa:\n";
                Pessoa pessoa;
                if(lerDadosPessoa(pessoa)){
                    if(cntrServicoPessoa->atualizar(pessoa))
                        std::cout << "Pessoa atualizada com sucesso!\n";
                    else
                        std::cout << "Nao foi possivel atualizar (nao existe).\n";
                }
                break;
            }
            case 4: {
                Email chave;
                if(lerEmail(chave)){
                    if(cntrServicoPessoa->excluir(chave))
                        std::cout << "Pessoa excluida com sucesso!\n";
                    else
                        std::cout << "Nao foi possivel excluir (nao existe).\n";
                }
                break;
            }
            case 0:
                std::cout << "Saindo da gestao...\n";
                break;
            default:
                std::cout << "Opcao invalida.\n";
        }
    } while(opcao != 0);
}
// ===================== GESTAO DE PROJETO =====================
/// Controladora da camada de apresentacao para gestao de Projeto.
class CntrApresentacaoProjeto : public IAProjeto {
private:
    ISProjeto* cntrServicoProjeto;

    bool lerDadosProjeto(Projeto& projeto){
        Codigo codigo; Nome nome; Data inicio, termino;
        std::string entradaCodigo, entradaNome, entradaInicio, entradaTermino;
        try {
            std::cout << "Codigo (5 caracteres, ex: AB123): ";
            std::cin  >> entradaCodigo;
            codigo.setCode(entradaCodigo);
            std::cout << "Nome: ";
            std::cin  >> entradaNome;
            nome.setNome(entradaNome);
            std::cout << "Data de inicio (DD/MM/AAAA): ";
            std::cin  >> entradaInicio;
            inicio.setData(entradaInicio);
            std::cout << "Data de termino (DD/MM/AAAA): ";
            std::cin  >> entradaTermino;
            termino.setData(entradaTermino);
            projeto.setCodigo(codigo);
            projeto.setNome(nome);
            projeto.setData(inicio, termino);
        } catch (std::invalid_argument& exc) {
            std::cout << "Dado invalido: " << exc.what() << "\n";
            return false;
        }
        return true;
    }

    bool lerCodigo(Codigo& codigo){
        std::string entrada;
        std::cout << "Codigo do projeto: ";
        std::cin  >> entrada;
        try {
            codigo.setCode(entrada);
        } catch (std::invalid_argument& exc) {
            std::cout << "Codigo invalido: " << exc.what() << "\n";
            return false;
        }
        return true;
    }

    void exibirProjeto(const Projeto& p){
        std::cout << "\n--- Dados do Projeto ---\n";
        std::cout << "Codigo : " << p.getCodigo().getCode() << "\n";
        std::cout << "Nome   : " << p.getNome().getNome()   << "\n";
        std::cout << "Inicio : " << p.getInicio().getData() << "\n";
        std::cout << "Termino: " << p.getTermino().getData()<< "\n";
        std::cout << "------------------------\n";
    }

public:
    void setCntrServicoProjeto(ISProjeto* cntr){ cntrServicoProjeto = cntr; }
    void executar(const Email&) override;
};

inline void CntrApresentacaoProjeto::executar(const Email& email){
    int opcao;
    do {
        std::cout << "\n===== Gestao de Projeto =====\n";
        std::cout << "1 - Criar\n2 - Ler\n3 - Atualizar\n4 - Excluir\n0 - Voltar\n";
        std::cout << "Escolha: ";
        std::cin  >> opcao;
        switch(opcao){
            case 1: {
                Projeto p;
                if(lerDadosProjeto(p)){
                    if(cntrServicoProjeto->criar(p)) std::cout << "Projeto criado com sucesso!\n";
                    else std::cout << "Nao foi possivel criar (codigo ja existe).\n";
                }
                break;
            }
            case 2: {
                Codigo c;
                if(lerCodigo(c)){
                    Projeto p; p.setCodigo(c);
                    if(cntrServicoProjeto->ler(p)) exibirProjeto(p);
                    else std::cout << "Projeto nao encontrado.\n";
                }
                break;
            }
            case 3: {
                std::cout << "Informe os dados atualizados (mesmo codigo):\n";
                Projeto p;
                if(lerDadosProjeto(p)){
                    if(cntrServicoProjeto->atualizar(p)) std::cout << "Projeto atualizado com sucesso!\n";
                    else std::cout << "Nao foi possivel atualizar (nao existe).\n";
                }
                break;
            }
            case 4: {
                Codigo c;
                if(lerCodigo(c)){
                    if(cntrServicoProjeto->excluir(c)) std::cout << "Projeto excluido com sucesso!\n";
                    else std::cout << "Nao foi possivel excluir (nao existe).\n";
                }
                break;
            }
            case 0: std::cout << "Voltando...\n"; break;
            default: std::cout << "Opcao invalida.\n";
        }
    } while(opcao != 0);
}
// ===================== GESTAO DE PLANO DE SPRINT =====================
/// Controladora da camada de apresentacao para gestao de Plano de Sprint.
class CntrApresentacaoPlanoSprint : public IAPlanoSprint {
private:
    ISPlanoSprint* cntrServicoSprint;

    bool lerDadosSprint(Plano_de_Sprint& sprint){
        Codigo codigo; Texto objetivo; Tempo capacidade;
        std::string entradaCodigo, entradaObjetivo;
        int entradaCapacidade;
        try {
            std::cout << "Codigo (5 caracteres, ex: SP123): ";
            std::cin  >> entradaCodigo;
            codigo.setCode(entradaCodigo);
            std::cin.ignore();
            std::cout << "Objetivo (texto): ";
            std::getline(std::cin, entradaObjetivo);
            objetivo.setTexto(entradaObjetivo);
            std::cout << "Capacidade (dias, 1 a 365): ";
            std::cin  >> entradaCapacidade;
            capacidade.setDuracao(entradaCapacidade);
            sprint.setCodigo(codigo);
            sprint.setObjetivo(objetivo);
            sprint.setCapacidade(capacidade);
        } catch (std::invalid_argument& exc) {
            std::cout << "Dado invalido: " << exc.what() << "\n";
            return false;
        }
        return true;
    }

    bool lerCodigo(Codigo& codigo){
        std::string entrada;
        std::cout << "Codigo do plano de sprint: ";
        std::cin  >> entrada;
        try {
            codigo.setCode(entrada);
        } catch (std::invalid_argument& exc) {
            std::cout << "Codigo invalido: " << exc.what() << "\n";
            return false;
        }
        return true;
    }

    void exibirSprint(const Plano_de_Sprint& s){
        std::cout << "\n--- Dados do Plano de Sprint ---\n";
        std::cout << "Codigo    : " << s.getCodigo().getCode()        << "\n";
        std::cout << "Objetivo  : " << s.getObjetivo().getTexto()     << "\n";
        std::cout << "Capacidade: " << s.getCapacidade().getDuracao() << " dias\n";
        std::cout << "--------------------------------\n";
    }

public:
    void setCntrServicoSprint(ISPlanoSprint* cntr){ cntrServicoSprint = cntr; }
    void executar(const Email&) override;
};

inline void CntrApresentacaoPlanoSprint::executar(const Email& email){
    int opcao;
    do {
        std::cout << "\n===== Gestao de Plano de Sprint =====\n";
        std::cout << "1 - Criar\n2 - Ler\n3 - Atualizar\n4 - Excluir\n0 - Voltar\n";
        std::cout << "Escolha: ";
        std::cin  >> opcao;
        switch(opcao){
            case 1: {
                Plano_de_Sprint s;
                if(lerDadosSprint(s)){
                    if(cntrServicoSprint->criar(s)) std::cout << "Plano de Sprint criado com sucesso!\n";
                    else std::cout << "Nao foi possivel criar (codigo ja existe).\n";
                }
                break;
            }
            case 2: {
                Codigo c;
                if(lerCodigo(c)){
                    Plano_de_Sprint s; s.setCodigo(c);
                    if(cntrServicoSprint->ler(s)) exibirSprint(s);
                    else std::cout << "Plano de Sprint nao encontrado.\n";
                }
                break;
            }
            case 3: {
                std::cout << "Informe os dados atualizados (mesmo codigo):\n";
                Plano_de_Sprint s;
                if(lerDadosSprint(s)){
                    if(cntrServicoSprint->atualizar(s)) std::cout << "Plano de Sprint atualizado com sucesso!\n";
                    else std::cout << "Nao foi possivel atualizar (nao existe).\n";
                }
                break;
            }
            case 4: {
                Codigo c;
                if(lerCodigo(c)){
                    if(cntrServicoSprint->excluir(c)) std::cout << "Plano de Sprint excluido com sucesso!\n";
                    else std::cout << "Nao foi possivel excluir (nao existe).\n";
                }
                break;
            }
            case 0: std::cout << "Voltando...\n"; break;
            default: std::cout << "Opcao invalida.\n";
        }
    } while(opcao != 0);
}
// ===================== CADASTRO =====================
/// Controladora da camada de apresentacao para cadastro de usuario.
class CntrApresentacaoCadastro : public IACadastro {
private:
    ISCadastro* cntrServicoCadastro;
public:
    void setCntrServicoCadastro(ISCadastro* cntr){ cntrServicoCadastro = cntr; }
    bool cadastrar(Nome*, Email*, Senha*, Papel*) override;
};

inline bool CntrApresentacaoCadastro::cadastrar(Nome* nome, Email* email, Senha* senha, Papel* papel){
    std::string entradaNome, entradaEmail, entradaSenha;
    int entradaPapel;
    std::cout << "\n=== Cadastro ===\n";
    try {
        std::cout << "Nome: ";
        std::cin  >> entradaNome;
        nome->setNome(entradaNome);
        std::cout << "Email: ";
        std::cin  >> entradaEmail;
        email->setEmail(entradaEmail);
        std::cout << "\nRegras da senha:\n";
        std::cout << " - 6 caracteres\n";
        std::cout << " - Apenas letras (a-z, A-Z) ou digitos (0-9)\n";
        std::cout << " - Letra nao pode ser seguida de letra, nem digito de digito\n";
        std::cout << " - Pelo menos uma minuscula, uma maiuscula e um digito\n";
        std::cout << " - Exemplo valido: a1B2c3\n";
        std::cout << "Senha: ";
        std::cin  >> entradaSenha;
        senha->setSenha(entradaSenha);

        senha->setSenha(entradaSenha);
        std::cout << "Papel (1-Desenvolvedor, 2-Mestre Scrum, 3-Proprietario): ";
        std::cin  >> entradaPapel;
        papel->setEscolha_papel(entradaPapel);
    } catch (std::invalid_argument& exc) {
        std::cout << "Dado invalido: " << exc.what() << "\n";
        return false;
    }
    return cntrServicoCadastro->cadastrar(*nome, *email, *senha, *papel);
}
// ===================== GESTAO DE HISTORIA DE USUARIO =====================
/// Controladora da camada de apresentacao para gestao de Historia de Usuario.
class CntrApresentacaoHistoria : public IAHistoria {
private:
    ISHistoria* cntrServicoHistoria;

    bool lerDadosHistoria(Historia_de_usuario& h){
        Codigo codigo; Texto titulo, papel, acao, valor; Tempo estimativa;
        Prioridade prioridade; Estado estado;
        std::string eCodigo, eTitulo, ePapel, eAcao, eValor;
        int eEstimativa, ePrioridade, eEstado;
        try {
            std::cout << "Codigo (5 caracteres, ex: HU123): ";
            std::cin  >> eCodigo;  codigo.setCode(eCodigo);
            std::cin.ignore();
            std::cout << "Titulo: ";        std::getline(std::cin, eTitulo);  titulo.setTexto(eTitulo);
            std::cout << "Papel (como...): ";std::getline(std::cin, ePapel);  papel.setTexto(ePapel);
            std::cout << "Acao (eu quero...): "; std::getline(std::cin, eAcao); acao.setTexto(eAcao);
            std::cout << "Valor (para...): ";std::getline(std::cin, eValor);  valor.setTexto(eValor);
            std::cout << "Estimativa (dias, 1 a 365): "; std::cin >> eEstimativa; estimativa.setDuracao(eEstimativa);
            std::cout << "Prioridade (1-ALTA, 2-MEDIA, 3-BAIXA): "; std::cin >> ePrioridade; prioridade.setPrio(ePrioridade);
            std::cout << "Estado (1-A FAZER, 2-FAZENDO, 3-FEITO): "; std::cin >> eEstado; estado.setEstado(eEstado);
            h.setCodigo(codigo); h.setTitulo(titulo); h.setPapel(papel); h.setAcao(acao);
            h.setValor(valor); h.setEstimativa(estimativa); h.setPrioridade(prioridade); h.setEstado(estado);
        } catch (std::invalid_argument& exc) {
            std::cout << "Dado invalido: " << exc.what() << "\n";
            return false;
        }
        return true;
    }

    bool lerCodigo(Codigo& codigo){
        std::string entrada;
        std::cout << "Codigo da historia: ";
        std::cin  >> entrada;
        try { codigo.setCode(entrada); }
        catch (std::invalid_argument& exc) { std::cout << "Codigo invalido: " << exc.what() << "\n"; return false; }
        return true;
    }

    void exibirHistoria(const Historia_de_usuario& h){
        std::cout << "\n--- Dados da Historia de Usuario ---\n";
        std::cout << "Codigo    : " << h.getCodigo().getCode()        << "\n";
        std::cout << "Titulo    : " << h.getTitulo().getTexto()       << "\n";
        std::cout << "Papel     : " << h.getPapel().getTexto()        << "\n";
        std::cout << "Acao      : " << h.getAcao().getTexto()         << "\n";
        std::cout << "Valor     : " << h.getValor().getTexto()        << "\n";
        std::cout << "Estimativa: " << h.getEstimativa().getDuracao() << " dias\n";
        std::cout << "Prioridade: " << h.getPrioridade().getPrio()    << "\n";
        std::cout << "Estado    : " << h.getEstado().getEstado()      << "\n";
        std::cout << "------------------------------------\n";
    }

public:
    void setCntrServicoHistoria(ISHistoria* cntr){ cntrServicoHistoria = cntr; }
    void executar(const Email&) override;
};

inline void CntrApresentacaoHistoria::executar(const Email& email){
    int opcao;
    do {
        std::cout << "\n===== Gestao de Historia de Usuario =====\n";
        std::cout << "1 - Criar\n2 - Ler\n3 - Atualizar\n4 - Excluir\n0 - Voltar\n";
        std::cout << "Escolha: ";
        std::cin  >> opcao;
        switch(opcao){
            case 1: {
                Historia_de_usuario h;
                if(lerDadosHistoria(h)){
                    if(cntrServicoHistoria->criar(h)) std::cout << "Historia criada com sucesso!\n";
                    else std::cout << "Nao foi possivel criar (codigo ja existe).\n";
                }
                break;
            }
            case 2: {
                Codigo c;
                if(lerCodigo(c)){
                    Historia_de_usuario h; h.setCodigo(c);
                    if(cntrServicoHistoria->ler(h)) exibirHistoria(h);
                    else std::cout << "Historia nao encontrada.\n";
                }
                break;
            }
            case 3: {
                std::cout << "Informe os dados atualizados (mesmo codigo):\n";
                Historia_de_usuario h;
                if(lerDadosHistoria(h)){
                    if(cntrServicoHistoria->atualizar(h)) std::cout << "Historia atualizada com sucesso!\n";
                    else std::cout << "Nao foi possivel atualizar (nao existe).\n";
                }
                break;
            }
            case 4: {
                Codigo c;
                if(lerCodigo(c)){
                    if(cntrServicoHistoria->excluir(c)) std::cout << "Historia excluida com sucesso!\n";
                    else std::cout << "Nao foi possivel excluir (nao existe).\n";
                }
                break;
            }
            case 0: std::cout << "Voltando...\n"; break;
            default: std::cout << "Opcao invalida.\n";
        }
    } while(opcao != 0);
}
#endif // CONTROLADORASAPRESENTACAO_HPP

