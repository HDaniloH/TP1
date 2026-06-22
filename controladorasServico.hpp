#ifndef CONTROLADORASSERVICO_HPP
#define CONTROLADORASSERVICO_HPP

#include "interfaces.hpp"

// ===================== AUTENTICACAO =====================
/// Controladora de servico para autenticacao. Delega ao banco de dados.
class CntrServicoAutenticacao : public ISAutenticacao {
private:
    IBancoDados* cntrBancoDados;
public:
    void setCntrBancoDados(IBancoDados*);
    bool autenticar(const Email&, const Senha&) override;
};

inline void CntrServicoAutenticacao::setCntrBancoDados(IBancoDados* cntr){
    cntrBancoDados = cntr;
}

inline bool CntrServicoAutenticacao::autenticar(const Email& email, const Senha& senha){
    return (cntrBancoDados->DadosAutenticacao(email, senha) == 1);
}

// ===================== GESTAO DE PESSOA =====================
/// Controladora de servico para gestao de Pessoa. Delega ao banco de dados.
class CntrServicoPessoa : public ISPessoa {
private:
    IBancoDados* cntrBancoDados;
public:
    void setCntrBancoDados(IBancoDados*);
    bool criar(const Pessoa&) override;
    bool ler(Pessoa&) override;
    bool atualizar(const Pessoa&) override;
    bool excluir(const Email&) override;
};

inline void CntrServicoPessoa::setCntrBancoDados(IBancoDados* cntr){
    cntrBancoDados = cntr;
}
inline bool CntrServicoPessoa::criar(const Pessoa& p){ return cntrBancoDados->criar(p); }
inline bool CntrServicoPessoa::ler(Pessoa& p){ return cntrBancoDados->ler(p); }
inline bool CntrServicoPessoa::atualizar(const Pessoa& p){ return cntrBancoDados->atualizar(p); }
inline bool CntrServicoPessoa::excluir(const Email& e){ return cntrBancoDados->excluir(e); }
class CntrServicoProjeto : public ISProjeto {
private:
    IBancoDados* cntrBancoDados;
public:
    void setCntrBancoDados(IBancoDados* cntr){ cntrBancoDados = cntr; }
    bool criar(const Projeto& p)    override { return cntrBancoDados->criarProjeto(p); }
    bool ler(Projeto& p)            override { return cntrBancoDados->lerProjeto(p); }
    bool atualizar(const Projeto& p)override { return cntrBancoDados->atualizarProjeto(p); }
    bool excluir(const Codigo& c)   override { return cntrBancoDados->excluirProjeto(c); }
};
// ===================== PLANO DE SPRINT =====================
/// Controladora de servico para gestao de Plano de Sprint. Delega ao banco.
class CntrServicoPlanoSprint : public ISPlanoSprint {
private:
    IBancoDados* cntrBancoDados;
public:
    void setCntrBancoDados(IBancoDados* cntr){ cntrBancoDados = cntr; }
    bool criar(const Plano_de_Sprint& s)    override { return cntrBancoDados->criarSprint(s); }
    bool ler(Plano_de_Sprint& s)            override { return cntrBancoDados->lerSprint(s); }
    bool atualizar(const Plano_de_Sprint& s)override { return cntrBancoDados->atualizarSprint(s); }
    bool excluir(const Codigo& c)           override { return cntrBancoDados->excluirSprint(c); }
};
// ===================== CADASTRO =====================
/// Controladora de servico para cadastro. Delega ao banco de dados.
class CntrServicoCadastro : public ISCadastro {
private:
    IBancoDados* cntrBancoDados;
public:
    void setCntrBancoDados(IBancoDados* cntr){ cntrBancoDados = cntr; }
    bool cadastrar(const Nome& n, const Email& e, const Senha& s, const Papel& p) override {
        return cntrBancoDados->DadosCadastro(n, e, s, p);
    }
};
// ===================== HISTORIA DE USUARIO =====================
/// Controladora de servico para gestao de Historia de Usuario. Delega ao banco.
class CntrServicoHistoria : public ISHistoria {
private:
    IBancoDados* cntrBancoDados;
public:
    void setCntrBancoDados(IBancoDados* cntr){ cntrBancoDados = cntr; }
    bool criar(const Historia_de_usuario& h)    override { return cntrBancoDados->criarHistoria(h); }
    bool ler(Historia_de_usuario& h)            override { return cntrBancoDados->lerHistoria(h); }
    bool atualizar(const Historia_de_usuario& h)override { return cntrBancoDados->atualizarHistoria(h); }
    bool excluir(const Codigo& c)               override { return cntrBancoDados->excluirHistoria(c); }
};

#endif // CONTROLADORASSERVICO_HPP
