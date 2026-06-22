#ifndef CONTROLADORASPERSISTENCIA_HPP
#define CONTROLADORASPERSISTENCIA_HPP

#include "interfaces.hpp"
#include "sqlite3.h"
#include <iostream>
#include <string>

/// Controladora da camada de persistencia. Implementa IBancoDados usando SQLite.
class CntrBancoDados : public IBancoDados {
private:
    sqlite3* db;

    /// Converte a string do papel de volta para o numero (1, 2 ou 3).
    int mapaPapel(const std::string& papel){
        if(papel == "DESENVOLVEDOR") return 1;
        if(papel == "MESTRE SCRUM")  return 2;
        return 3; // PROPIETARIO DE PRODUTO
    }

    /// Insere uma pessoa no banco. Retorna false se o email ja existir.
    bool inserir(const std::string& nome, const std::string& email,
                 const std::string& senha, const std::string& papel){
        const char* sql = "INSERT INTO pessoa (email, nome, senha, papel) VALUES (?, ?, ?, ?);";
        sqlite3_stmt* stmt;
        if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
        sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, nome.c_str(),  -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, senha.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, papel.c_str(), -1, SQLITE_TRANSIENT);
        int rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        return (rc == SQLITE_DONE);
    }

public:
    CntrBancoDados();
    ~CntrBancoDados();
    int  DadosAutenticacao(const Email&, const Senha&) override;
    bool DadosCadastro(const Nome&, const Email&, const Senha&, const Papel&) override;
    bool criar(const Pessoa&) override;
    bool ler(Pessoa&) override;
    bool atualizar(const Pessoa&) override;
    bool excluir(const Email&) override;
    bool criarProjeto(const Projeto&) override;
    bool lerProjeto(Projeto&) override;
    bool atualizarProjeto(const Projeto&) override;
    bool excluirProjeto(const Codigo&) override;
    bool criarSprint(const Plano_de_Sprint&) override;
    bool lerSprint(Plano_de_Sprint&) override;
    bool atualizarSprint(const Plano_de_Sprint&) override;
    bool excluirSprint(const Codigo&) override;
    bool criarHistoria(const Historia_de_usuario&) override;
    bool lerHistoria(Historia_de_usuario&) override;
    bool atualizarHistoria(const Historia_de_usuario&) override;
    bool excluirHistoria(const Codigo&) override;
};


inline CntrBancoDados::~CntrBancoDados(){
    if(db) sqlite3_close(db);
}

inline CntrBancoDados::CntrBancoDados(){
    db = nullptr;
    if(sqlite3_open("dados.db", &db) != SQLITE_OK){
        std::cout << "Erro ao abrir o banco: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    char* erro = nullptr;

    // tabela pessoa
    const char* sqlPessoa =
        "CREATE TABLE IF NOT EXISTS pessoa ("
        "email TEXT PRIMARY KEY, "
        "nome TEXT NOT NULL, "
        "senha TEXT NOT NULL, "
        "papel TEXT NOT NULL);";
    if(sqlite3_exec(db, sqlPessoa, nullptr, nullptr, &erro) != SQLITE_OK){
        std::cout << "Erro ao criar tabela pessoa: " << erro << "\n";
        sqlite3_free(erro);
    }

    // tabela projeto
    const char* sqlProjeto =
        "CREATE TABLE IF NOT EXISTS projeto ("
        "codigo TEXT PRIMARY KEY, "
        "nome TEXT NOT NULL, "
        "inicio TEXT NOT NULL, "
        "termino TEXT NOT NULL);";
    if(sqlite3_exec(db, sqlProjeto, nullptr, nullptr, &erro) != SQLITE_OK){
        std::cout << "Erro ao criar tabela projeto: " << erro << "\n";
        sqlite3_free(erro);
    }
    const char* sqlSprint =
        "CREATE TABLE IF NOT EXISTS plano_sprint ("
        "codigo TEXT PRIMARY KEY, "
        "objetivo TEXT NOT NULL, "
        "capacidade INTEGER NOT NULL);";
    if(sqlite3_exec(db, sqlSprint, nullptr, nullptr, &erro) != SQLITE_OK){
        std::cout << "Erro ao criar tabela plano_sprint: " << erro << "\n";
        sqlite3_free(erro);
    }
    const char* sqlHistoria =
        "CREATE TABLE IF NOT EXISTS historia ("
        "codigo TEXT PRIMARY KEY, "
        "titulo TEXT NOT NULL, "
        "papel TEXT NOT NULL, "
        "acao TEXT NOT NULL, "
        "valor TEXT NOT NULL, "
        "estimativa INTEGER NOT NULL, "
        "prioridade TEXT NOT NULL, "
        "estado TEXT NOT NULL);";
    if(sqlite3_exec(db, sqlHistoria, nullptr, nullptr, &erro) != SQLITE_OK){
        std::cout << "Erro ao criar tabela historia: " << erro << "\n";
        sqlite3_free(erro);
    }
}

inline bool CntrBancoDados::DadosCadastro(const Nome& nome, const Email& email,
                                          const Senha& senha, const Papel& papel){
    return inserir(nome.getNome(), email.getEmail(), senha.getSenha(), papel.getEscolha_papel());
}

inline bool CntrBancoDados::criar(const Pessoa& pessoa){
    return inserir(pessoa.getNome().getNome(), pessoa.getEmail().getEmail(),
                   pessoa.getSenha().getSenha(), pessoa.getPapel().getEscolha_papel());
}

inline bool CntrBancoDados::ler(Pessoa& pessoa){
    std::string email = pessoa.getEmail().getEmail();
    const char* sql = "SELECT nome, senha, papel FROM pessoa WHERE email = ?;";
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_TRANSIENT);
    bool encontrou = false;
    if(sqlite3_step(stmt) == SQLITE_ROW){
        std::string nomeBanco  = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string senhaBanco = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string papelBanco = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        Nome  nome;  nome.setNome(nomeBanco);
        Senha senha; senha.setSenha(senhaBanco);
        Papel papel; papel.setEscolha_papel(mapaPapel(papelBanco));
        pessoa.setNome(nome);
        pessoa.setSenha(senha);
        pessoa.setPapel(papel);
        encontrou = true;
    }
    sqlite3_finalize(stmt);
    return encontrou;
}

inline bool CntrBancoDados::criarProjeto(const Projeto& projeto){
    std::string codigo  = projeto.getCodigo().getCode();
    std::string nome    = projeto.getNome().getNome();
    std::string inicio  = projeto.getInicio().getData();
    std::string termino = projeto.getTermino().getData();
    const char* sql = "INSERT INTO projeto (codigo, nome, inicio, termino) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, codigo.c_str(),  -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, nome.c_str(),    -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, inicio.c_str(),  -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, termino.c_str(), -1, SQLITE_TRANSIENT);
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return (rc == SQLITE_DONE);
}

inline bool CntrBancoDados::lerProjeto(Projeto& projeto){
    std::string codigo = projeto.getCodigo().getCode();
    const char* sql = "SELECT nome, inicio, termino FROM projeto WHERE codigo = ?;";
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, codigo.c_str(), -1, SQLITE_TRANSIENT);
    bool encontrou = false;
    if(sqlite3_step(stmt) == SQLITE_ROW){
        std::string nomeBanco    = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string inicioBanco  = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string terminoBanco = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        Nome nome;    nome.setNome(nomeBanco);
        Data inicio;  inicio.setData(inicioBanco);
        Data termino; termino.setData(terminoBanco);
        projeto.setNome(nome);
        projeto.setData(inicio, termino);
        encontrou = true;
    }
    sqlite3_finalize(stmt);
    return encontrou;
}

inline bool CntrBancoDados::atualizarProjeto(const Projeto& projeto){
    std::string codigo  = projeto.getCodigo().getCode();
    std::string nome    = projeto.getNome().getNome();
    std::string inicio  = projeto.getInicio().getData();
    std::string termino = projeto.getTermino().getData();
    const char* sql = "UPDATE projeto SET nome = ?, inicio = ?, termino = ? WHERE codigo = ?;";
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, nome.c_str(),    -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, inicio.c_str(),  -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, termino.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, codigo.c_str(),  -1, SQLITE_TRANSIENT);
    int rc = sqlite3_step(stmt);
    int mudou = sqlite3_changes(db);
    sqlite3_finalize(stmt);
    return (rc == SQLITE_DONE && mudou > 0);
}

inline bool CntrBancoDados::excluirProjeto(const Codigo& codigo){
    std::string c = codigo.getCode();
    const char* sql = "DELETE FROM projeto WHERE codigo = ?;";
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, c.c_str(), -1, SQLITE_TRANSIENT);
    int rc = sqlite3_step(stmt);
    int mudou = sqlite3_changes(db);
    sqlite3_finalize(stmt);
    return (rc == SQLITE_DONE && mudou > 0);
}
inline int CntrBancoDados::DadosAutenticacao(const Email& email, const Senha& senha){
    std::string e = email.getEmail();
    const char* sql = "SELECT senha FROM pessoa WHERE email = ?;";
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return 0;
    sqlite3_bind_text(stmt, 1, e.c_str(), -1, SQLITE_TRANSIENT);
    int resultado;
    if(sqlite3_step(stmt) == SQLITE_ROW){
        std::string senhaBanco = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        resultado = (senhaBanco == senha.getSenha()) ? 1 : -1;
    } else {
        resultado = 0;
    }
    sqlite3_finalize(stmt);
    return resultado;
}

inline bool CntrBancoDados::atualizar(const Pessoa& pessoa){
    std::string email = pessoa.getEmail().getEmail();
    std::string nome  = pessoa.getNome().getNome();
    std::string senha = pessoa.getSenha().getSenha();
    std::string papel = pessoa.getPapel().getEscolha_papel();
    const char* sql = "UPDATE pessoa SET nome = ?, senha = ?, papel = ? WHERE email = ?;";
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, nome.c_str(),  -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, senha.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, papel.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, email.c_str(), -1, SQLITE_TRANSIENT);
    int rc = sqlite3_step(stmt);
    int mudou = sqlite3_changes(db);
    sqlite3_finalize(stmt);
    return (rc == SQLITE_DONE && mudou > 0);
}

inline bool CntrBancoDados::excluir(const Email& email){
    std::string e = email.getEmail();
    const char* sql = "DELETE FROM pessoa WHERE email = ?;";
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, e.c_str(), -1, SQLITE_TRANSIENT);
    int rc = sqlite3_step(stmt);
    int mudou = sqlite3_changes(db);
    sqlite3_finalize(stmt);
    return (rc == SQLITE_DONE && mudou > 0);
}
inline bool CntrBancoDados::criarSprint(const Plano_de_Sprint& sprint){
    std::string codigo    = sprint.getCodigo().getCode();
    std::string objetivo  = sprint.getObjetivo().getTexto();
    int capacidade        = sprint.getCapacidade().getDuracao();
    const char* sql = "INSERT INTO plano_sprint (codigo, objetivo, capacidade) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, codigo.c_str(),   -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, objetivo.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int (stmt, 3, capacidade);
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return (rc == SQLITE_DONE);
}

inline bool CntrBancoDados::lerSprint(Plano_de_Sprint& sprint){
    std::string codigo = sprint.getCodigo().getCode();
    const char* sql = "SELECT objetivo, capacidade FROM plano_sprint WHERE codigo = ?;";
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, codigo.c_str(), -1, SQLITE_TRANSIENT);
    bool encontrou = false;
    if(sqlite3_step(stmt) == SQLITE_ROW){
        std::string objetivoBanco = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        int capacidadeBanco = sqlite3_column_int(stmt, 1);
        Texto objetivo;  objetivo.setTexto(objetivoBanco);
        Tempo capacidade; capacidade.setDuracao(capacidadeBanco);
        sprint.setObjetivo(objetivo);
        sprint.setCapacidade(capacidade);
        encontrou = true;
    }
    sqlite3_finalize(stmt);
    return encontrou;
}

inline bool CntrBancoDados::atualizarSprint(const Plano_de_Sprint& sprint){
    std::string codigo    = sprint.getCodigo().getCode();
    std::string objetivo  = sprint.getObjetivo().getTexto();
    int capacidade        = sprint.getCapacidade().getDuracao();
    const char* sql = "UPDATE plano_sprint SET objetivo = ?, capacidade = ? WHERE codigo = ?;";
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, objetivo.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int (stmt, 2, capacidade);
    sqlite3_bind_text(stmt, 3, codigo.c_str(),   -1, SQLITE_TRANSIENT);
    int rc = sqlite3_step(stmt);
    int mudou = sqlite3_changes(db);
    sqlite3_finalize(stmt);
    return (rc == SQLITE_DONE && mudou > 0);
}

inline bool CntrBancoDados::excluirSprint(const Codigo& codigo){
    std::string c = codigo.getCode();
    const char* sql = "DELETE FROM plano_sprint WHERE codigo = ?;";
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, c.c_str(), -1, SQLITE_TRANSIENT);
    int rc = sqlite3_step(stmt);
    int mudou = sqlite3_changes(db);
    sqlite3_finalize(stmt);
    return (rc == SQLITE_DONE && mudou > 0);
}
// helpers para converter texto de volta para a escolha numerica
inline int mapaPrioridade(const std::string& p){
    if(p == "ALTA") return 1;
    if(p == "MEDIA") return 2;
    return 3; // BAIXA
}
inline int mapaEstado(const std::string& e){
    if(e == "A FAZER") return 1;
    if(e == "FAZENDO") return 2;
    return 3; // FEITO
}

inline bool CntrBancoDados::criarHistoria(const Historia_de_usuario& h){
    std::string codigo     = h.getCodigo().getCode();
    std::string titulo     = h.getTitulo().getTexto();
    std::string papel      = h.getPapel().getTexto();
    std::string acao       = h.getAcao().getTexto();
    std::string valor      = h.getValor().getTexto();
    int estimativa         = h.getEstimativa().getDuracao();
    std::string prioridade = h.getPrioridade().getPrio();
    std::string estado     = h.getEstado().getEstado();
    const char* sql = "INSERT INTO historia (codigo, titulo, papel, acao, valor, estimativa, prioridade, estado) "
                      "VALUES (?, ?, ?, ?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, codigo.c_str(),     -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, titulo.c_str(),     -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, papel.c_str(),      -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, acao.c_str(),       -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, valor.c_str(),      -1, SQLITE_TRANSIENT);
    sqlite3_bind_int (stmt, 6, estimativa);
    sqlite3_bind_text(stmt, 7, prioridade.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 8, estado.c_str(),     -1, SQLITE_TRANSIENT);
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return (rc == SQLITE_DONE);
}

inline bool CntrBancoDados::lerHistoria(Historia_de_usuario& h){
    std::string codigo = h.getCodigo().getCode();
    const char* sql = "SELECT titulo, papel, acao, valor, estimativa, prioridade, estado FROM historia WHERE codigo = ?;";
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, codigo.c_str(), -1, SQLITE_TRANSIENT);
    bool encontrou = false;
    if(sqlite3_step(stmt) == SQLITE_ROW){
        std::string tituloB     = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string papelB      = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string acaoB       = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        std::string valorB      = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        int estimativaB         = sqlite3_column_int(stmt, 4);
        std::string prioridadeB = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        std::string estadoB     = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        Texto titulo;  titulo.setTexto(tituloB);
        Texto papel;   papel.setTexto(papelB);
        Texto acao;    acao.setTexto(acaoB);
        Texto valor;   valor.setTexto(valorB);
        Tempo estimativa; estimativa.setDuracao(estimativaB);
        Prioridade prioridade; prioridade.setPrio(mapaPrioridade(prioridadeB));
        Estado estado; estado.setEstado(mapaEstado(estadoB));
        h.setTitulo(titulo);
        h.setPapel(papel);
        h.setAcao(acao);
        h.setValor(valor);
        h.setEstimativa(estimativa);
        h.setPrioridade(prioridade);
        h.setEstado(estado);
        encontrou = true;
    }
    sqlite3_finalize(stmt);
    return encontrou;
}

inline bool CntrBancoDados::atualizarHistoria(const Historia_de_usuario& h){
    std::string codigo     = h.getCodigo().getCode();
    std::string titulo     = h.getTitulo().getTexto();
    std::string papel      = h.getPapel().getTexto();
    std::string acao       = h.getAcao().getTexto();
    std::string valor      = h.getValor().getTexto();
    int estimativa         = h.getEstimativa().getDuracao();
    std::string prioridade = h.getPrioridade().getPrio();
    std::string estado     = h.getEstado().getEstado();
    const char* sql = "UPDATE historia SET titulo=?, papel=?, acao=?, valor=?, estimativa=?, prioridade=?, estado=? WHERE codigo=?;";
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, titulo.c_str(),     -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, papel.c_str(),      -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, acao.c_str(),       -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, valor.c_str(),      -1, SQLITE_TRANSIENT);
    sqlite3_bind_int (stmt, 5, estimativa);
    sqlite3_bind_text(stmt, 6, prioridade.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 7, estado.c_str(),     -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 8, codigo.c_str(),     -1, SQLITE_TRANSIENT);
    int rc = sqlite3_step(stmt);
    int mudou = sqlite3_changes(db);
    sqlite3_finalize(stmt);
    return (rc == SQLITE_DONE && mudou > 0);
}

inline bool CntrBancoDados::excluirHistoria(const Codigo& codigo){
    std::string c = codigo.getCode();
    const char* sql = "DELETE FROM historia WHERE codigo = ?;";
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;
    sqlite3_bind_text(stmt, 1, c.c_str(), -1, SQLITE_TRANSIENT);
    int rc = sqlite3_step(stmt);
    int mudou = sqlite3_changes(db);
    sqlite3_finalize(stmt);
    return (rc == SQLITE_DONE && mudou > 0);
}

#endif // CONTROLADORASPERSISTENCIA_HPP
