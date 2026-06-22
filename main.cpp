#include "controladorasApresentacao.hpp"
#include "controladorasServico.hpp"
#include "controladorasPersistencia.hpp"
#include <iostream>
using namespace std;

int main(){
    // camada de persistencia (banco unico)
    CntrBancoDados bancoDados;

    // camada de servico
    CntrServicoAutenticacao servicoAutenticacao;
    CntrServicoCadastro     servicoCadastro;
    CntrServicoPessoa       servicoPessoa;
    CntrServicoProjeto      servicoProjeto;
    CntrServicoPlanoSprint  servicoSprint;

    // camada de apresentacao
    CntrApresentacaoAutenticacao apresentacaoAutenticacao;
    CntrApresentacaoCadastro     apresentacaoCadastro;
    CntrApresentacaoPessoa       apresentacaoPessoa;
    CntrApresentacaoProjeto      apresentacaoProjeto;
    CntrApresentacaoPlanoSprint  apresentacaoSprint;
    // camada de história
    CntrServicoHistoria       servicoHistoria;
    CntrApresentacaoHistoria  apresentacaoHistoria;
    servicoHistoria.setCntrBancoDados(&bancoDados);
    apresentacaoHistoria.setCntrServicoHistoria(&servicoHistoria);

    // ligacoes servico -> banco
    servicoAutenticacao.setCntrBancoDados(&bancoDados);
    servicoCadastro.setCntrBancoDados(&bancoDados);
    servicoPessoa.setCntrBancoDados(&bancoDados);
    servicoProjeto.setCntrBancoDados(&bancoDados);
    servicoSprint.setCntrBancoDados(&bancoDados);

    // ligacoes apresentacao -> servico
    apresentacaoAutenticacao.setCntrServicoAutenticacao(&servicoAutenticacao);
    apresentacaoCadastro.setCntrServicoCadastro(&servicoCadastro);
    apresentacaoPessoa.setCntrServicoPessoa(&servicoPessoa);
    apresentacaoProjeto.setCntrServicoProjeto(&servicoProjeto);
    apresentacaoSprint.setCntrServicoSprint(&servicoSprint);

    // MENU INICIAL: Login ou Cadastro
    int inicial;
    bool autenticado = false;
    Email email;

    do {
        cout << "\n========= BEM-VINDO =========\n";
        cout << "1 - Login\n";
        cout << "2 - Cadastrar\n";
        cout << "0 - Sair\n";
        cout << "Escolha: ";
        cin >> inicial;

        if(inicial == 1){
            if(apresentacaoAutenticacao.autenticar(&email)){
                cout << "\nAutenticado com sucesso!\n";
                autenticado = true;
            } else {
                cout << "\nFalha na autenticacao.\n";
            }
        }
        else if(inicial == 2){
            Nome n; Email e; Senha s; Papel p;
            if(apresentacaoCadastro.cadastrar(&n, &e, &s, &p))
                cout << "\nCadastro realizado com sucesso! Agora faca login.\n";
            else
                cout << "\nNao foi possivel cadastrar (email ja existe ou dado invalido).\n";
        }
    } while(inicial != 0 && !autenticado);

    // se autenticou, abre o menu principal
    if(autenticado){
        int op;
        do {
            cout << "\n========= MENU PRINCIPAL =========\n";
            cout << "1 - Gerir Pessoas\n";
            cout << "2 - Gerir Projetos\n";
            cout << "3 - Gerir Planos de Sprint\n";
            cout << "4 - Gerir Historias de Usuario\n";
            cout << "0 - Sair\n";
            cout << "Escolha: ";
            cin >> op;
            if(op == 1)      apresentacaoPessoa.executar(email);
            else if(op == 2) apresentacaoProjeto.executar(email);
            else if(op == 3) apresentacaoSprint.executar(email);
            else if(op == 4) apresentacaoHistoria.executar(email);
            else if(op != 0) cout << "Opcao invalida.\n";
        } while(op != 0);
    }

    return 0;
}
