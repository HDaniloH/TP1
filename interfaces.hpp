#ifndef INTERFACES_HPP_INCLUDED
#define INTERFACES_HPP_INCLUDED


#include "Entidades.hpp"
#include "dominios.hpp"
#include <stdexcept>


///
/// Interface de autenticação da camada de apresentação.
///
/// Recebe os dados inseridos pelo usuário e solicita à camada de serviço que os valide.
///

class IAAutenticacao{
public:

///
/// Solicita o serviço de autenticação ao usuário.
///
///
///
/// - Retorna true caso a solicitação à camada de serviço tenha sido realizada com sucesso.
/// - Retorna false caso a solicitação à camada de serviço não tenha sido realizada com sucesso.
///

    virtual bool autenticar(Email*) = 0;

///
/// Método destrutor virtual da interface.
///

    virtual ~IAAutenticacao(){}
};


///
/// Interface de cadastro da camada de apresentação.
///
/// Recebe os dados inseridos pelo usuário e solicita à camada de serviço que o registre.
///

class IACadastro{
public:

///
/// Solicita o serviço de cadastro ao usuário.
///
///
///
///
///
///
/// @return
///
/// - Retorna true caso a solicitação à camada de serviço tenha sido realizada com sucesso.
/// - Retorna false caso a solicitação à camada de serviço não tenha sido realizada com sucesso.
///

    virtual bool cadastrar(Nome*, Email*, Senha*, Papel*) = 0;

///
/// Método destrutor virtual da interface.
///

    virtual ~IACadastro(){}
};


///
/// Interface de pessoa da camada de apresentação.
///
/// Recebe as ações feitas pelo usuário e solicita à camada de serviço que as processe.
///

class IAPessoa{
public:

///
/// Solicita o serviço de execução ao usuário.
///
///
///

    virtual void executar(const Email&) = 0;

///
/// Método destrutor virtual da interface.
///

    virtual ~IAPessoa(){}
};



///
/// Interface de autenticação da camada de serviço.
///
/// Valida os dados recebidos do usuário e concede acesso ao restante do sistema.
///

class ISAutenticacao{
public:

///
/// Realiza o serviço de autenticação do usuário.
///
///
///
///
/// @return
///
/// - Retorna true caso os dados estejam corretos.
/// - Retorna false caso os dados estejam incorretos ou não existam no banco de dados.
///

    virtual bool autenticar(const Email&, const Senha&) = 0;

///
/// Método destrutor virtual da interface.
///

    virtual ~ISAutenticacao(){}
};


///
/// Interface de cadastro da camada de serviço.
///
/// Observa se o usuário ja existe no banco de dados e, caso contrário, armazena seus dados.
///

class ISCadastro{
public:

///
/// Realiza o serviço de cadastramento do usuário.
///
///
///
///
///
///
/// @return
///
/// - Retorna true caso os dados forem registrados corretamente no banco de dados.
/// - Retorna false caso os dados ja existirem no banco de dados.
///

    virtual bool cadastrar(const Nome&, const Email&, const Senha&, const Papel&) = 0;

///
/// Método destrutor virtual da interface.
///

    virtual ~ISCadastro(){}
};


///
/// Interface de pessoa da camada de serviço.
///
/// Executa e processa as ações do usuário.
///

class ISPessoa{
public:

///
/// Executa a ação de criar do usuário.
///
///
///
/// @return
///
/// - Retorna true caso (Projeto, Plano de Sprint ou Historia de Usuário) possa e tenha sido criado com sucesso, dependendo do papel (role) do usuário.
/// - Retorna false caso (Projeto, Plano de Sprint ou Historia de Usuário) ja existir ou o papel (role) do usuário não tiver a permissão de criar.
///

    virtual bool criar(const Pessoa&) = 0;

///
/// Executa a ação de ler do usuário.
///
///
///
/// @return
///
/// - Retorna true caso (Projeto, Plano de Sprint ou Historia de Usuário) exista e possa ser lido dependendo do papel (role) do usuário.
/// - Retorna false caso (Projeto, Plano de Sprint ou Historia de Usuário) não existir ou o papel (role) do usuário não tiver a permissão de ler.
///

    virtual bool ler(Pessoa&) = 0;

///
/// Executa a ação de atualizar do usuário.
///
///
///
/// @return
///
/// - Retorna true caso (Projeto, Plano de Sprint ou Historia de Usuário) exista e possa ser atualizado dependendo do papel (role) do usuário.
/// - Retorna false caso (Projeto, Plano de Sprint ou Historia de Usuário) não existir ou caso o papel (role) do usuário não tiver a permissão de atualizar.
///

    virtual bool atualizar(const Pessoa&) = 0;

///
/// Executa a ação de excluir do usuário.
///
///
///
/// @return
///
/// - Retorna true caso (Projeto, Plano de Sprint ou Historia de Usuário) exista e possa ser excluido  dependendo do papel (role) do usuário.
/// - Retorna false caso (Projeto, Plano de Sprint ou Historia de Usuário) não existir ou caso o papel (role) do usuário não tiver a permissão de excluir.
///

    virtual bool excluir(const Email&) = 0;

///
/// Método destrutor virtual da interface.
///

    virtual ~ISPessoa(){}
};


///
/// Interface de banco de dados da camada de persistência.
///
/// Responsável por armazenar, retornar, atualizar e excluir dados no banco de dados.
///

class IBancoDados{
public:

///
/// Verifica se os dados são iguais ou se não existem no banco de dados.
///
///
///
/// @return
///
/// - Retorna 1 caso os dados existam e sejam iguais aos que o usuário inseriu.
/// - Retorna 0 caso os dados não existam.
/// - Retorna (-1) caso os dados sejam diferentes dos que o usuário inseriu.
///

    virtual int DadosAutenticacao(const Email&, const Senha&) = 0;

///
/// Verifica se os dados já existem e, caso contrário, os armazena no banco de dados.
///
///
///
/// @return
///
/// - Retorna true caso os dados não existissem e tenham sido armazenados no banco de dados.
/// - Retorna false caso os dados já existirem no banco de dados.
///

    virtual bool DadosCadastro(const Nome&, const Email&, const Senha&, const Papel&) = 0;

///
/// Realiza a ação de criar processada pela camada de serviço.
///
///
///
/// @return
///
/// - Retorna true caso tenha sido possível armazenar no banco de dados (Projeto, Plano de Sprint ou Historia de Usuário).
/// - Retorna false caso (Projeto, Plano de Sprint ou Historia de Usuário) ja exista no banco de dados.
///

    virtual bool criar(const Pessoa&) = 0;

///
/// Realiza a ação de ler processada pela camada de serviço.
///
///
///
/// @return
///
/// - Retorna true caso exista no banco de dados e tenha sido possível mostrar as informações do(a) (Projeto, Plano de Sprint ou Historia de Usuário).
/// - Retorna false caso não exista o(a) (Projeto, Plano de Sprint ou Historia de Usuário) no banco de dados.
///

    virtual bool ler(Pessoa&) = 0;

///
/// Realiza a ação de atualizar processada pela camada de serviço.
///
///
///
/// @return
///
/// - Retorna true caso exista no banco de dados e tenha sido possível atualizar os dados do(a) (Projeto, Plano de Sprint ou Historia de Usuário).
/// - Retorna false caso não exista o(a) (Projeto, Plano de Sprint ou Historia de Usuário) no banco de dados.
///

    virtual bool atualizar(const Pessoa&) = 0;

///
/// Realiza a ação de excluir processada pela camada de serviço.
///
///
///
/// @return
///
/// - Retorna true caso exista no banco de dados e tenha sido possível excluir o(a) (Projeto, Plano de Sprint ou Historia de Usuário).
/// - Retorna false caso não exista o(a) (Projeto, Plano de Sprint ou Historia de Usuário) no banco de dados.
///

    virtual bool excluir(const Email&) = 0;

    virtual bool criarProjeto(const Projeto&) = 0;
    virtual bool lerProjeto(Projeto&) = 0;
    virtual bool atualizarProjeto(const Projeto&) = 0;
    virtual bool excluirProjeto(const Codigo&) = 0;

///
/// Método destrutor virtual da interface.
///

    virtual ~IBancoDados(){}
};
///
/// Interface de projeto da camada de apresentacao.
///
class IAProjeto{
public:
    virtual void executar(const Email&) = 0;
    virtual ~IAProjeto(){}
};

///
/// Interface de projeto da camada de servico.
///
class ISProjeto{
public:
    virtual bool criar(const Projeto&) = 0;
    virtual bool ler(Projeto&) = 0;
    virtual bool atualizar(const Projeto&) = 0;
    virtual bool excluir(const Codigo&) = 0;
    virtual ~ISProjeto(){}
};
#endif // INTERFACES_HPP_INCLUDED
