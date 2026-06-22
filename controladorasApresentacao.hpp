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
#endif // CONTROLADORASAPRESENTACAO_HPP

